#include "../include.hpp"

void haven::run() {
  for (;;) {
    while (stream.recieve()) {
      if (!host_player.valid) {
        int code = stream.read_byte();
        for (auto& req : requests) if (req.first == code) req.second->invoke(stream, this);
      } else {
        redirect_request();
      }
    }

    if (host_player.valid) {
      if (host_player.send_tick < util::get_millisecs()) {
        stream.write_byte(-1);
        stream.send(host_player.ip, host_player.port);
        host_player.send_tick = util::get_millisecs() + 1000;
      }

      if (host_player.last_tick < util::get_millisecs()) {
        logger::get().log("Host player timed out.", logger::log_type_info);
        host_player.valid = false;
      }
    }
    
    sleep(10);
  }
}

void haven::redirect_request() {
  std::unique_ptr<bank> recv_bank = std::make_unique<bank>(8192);
  int ip = stream.get_message_ip(), port = stream.get_message_port();

  if (ip == host_player.ip && port == host_player.port) {
    host_player.last_tick = util::get_millisecs() + 30000;
    recv_bank->resize(stream.read_avail());

    if (recv_bank->get_size() != 0) {
      recv_bank->read_bytes((base_stream*)&stream, 0, recv_bank->get_size());

      if (recv_bank->get_size() - 9 >= 0) {
        if (recv_bank->peek_byte(0) == request_disconnect && recv_bank->peek_byte(recv_bank->get_size() - 9) != 254) {
          logger::get().log("Host player disconnected.", logger::log_type_info);
          host_player.valid = false;
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
        recv_bank->write_bytes((base_stream*)&stream, 0, recv_bank->get_size());
        stream.send(ip, port);
      } else {
        stream.write_int(host_player.ip);
        stream.write_int(host_player.port);
        recv_bank->write_bytes((base_stream*)&stream, 0, recv_bank->get_size());
        stream.send(host_player.ip, host_player.port);
      }
    }
  } else {
    recv_bank->resize(stream.read_avail());

    if (recv_bank->get_size() != 0) {
      recv_bank->read_bytes((base_stream*)&stream, 0, recv_bank->get_size());
      stream.write_int(ip);
      stream.write_int(port);
      recv_bank->write_bytes((base_stream*)&stream, 0, recv_bank->get_size());
      stream.send(host_player.ip, host_player.port);
    }
  }
}