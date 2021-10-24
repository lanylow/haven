#include "../include.hpp"

void haven::run() {
	host_player& host = host_player::get();
	host.invalidate();
  for (;;) {
    while (stream.recieve()) {
      if (!host.valid) {
        int code = stream.read_byte();
        if (requests.count(code)) {
          requests[code](stream);
        }
      } else {
        redirect_request();
      }

      if (host.valid) {
        if (host.send_tick < internal_clock::get_current_time()) {
          stream.write_byte(-1);
          stream.send(host.ip, host.port);
          host.send_tick = internal_clock::get_current_time() + 1000;
        }

        if (host.last_tick < internal_clock::get_current_time()) {
          logger::get().log("Host player timed out.", logger::log_type_info);
          host.invalidate();
        }
      }
    }

    sleep(10);
  }
}

void haven::redirect_request() {
  std::unique_ptr<bank> recv_bank = std::make_unique<bank>(8192);
  int ip = stream.get_message_ip(), port = stream.get_message_port();
  host_player& host = host_player::get();

  if (ip == host.ip && port == host.port) {
    host.last_tick = internal_clock::get_current_time() + 20000;
    recv_bank->resize(stream.read_avail());

    if (recv_bank->get_size() != 0) {
      recv_bank->read_bytes(stream, 0, recv_bank->get_size());

      if (recv_bank->get_size() - 9 >= 0) {
        if (recv_bank->peek_byte(0) == request_disconnect && recv_bank->peek_byte(recv_bank->get_size() - 9) != 254) {
          logger::get().log("Host player disconnected.", logger::log_type_info);
          host.invalidate();
          return;
        }
      }

      if (recv_bank->get_size() - 8 >= 0) {
        ip = recv_bank->peek_int(recv_bank->get_size() - 8);
        port = recv_bank->peek_int(recv_bank->get_size() - 4);
        recv_bank->resize(recv_bank->get_size() - 8);
      } else {
        ip = port = 0;
      }

      if (ip != 0 && port != 0) {
        recv_bank->write_bytes(stream, 0, recv_bank->get_size());
        stream.send(ip, port);
      } else {
        stream.write_int(host.ip);
        stream.write_int(host.port);
        recv_bank->write_bytes(stream, 0, recv_bank->get_size());
        stream.send(host.ip, host.port);
      }
    }
  } else {
    recv_bank->resize(stream.read_avail());

    if (recv_bank->get_size() != 0) {
      recv_bank->read_bytes(stream, 0, recv_bank->get_size());
      stream.write_int(ip);
      stream.write_int(port);
      recv_bank->write_bytes(stream, 0, recv_bank->get_size());
      stream.send(host.ip, host.port);
    }
  }
}
