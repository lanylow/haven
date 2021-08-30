#include "include.hpp"

void handle_request(udp_stream* udp) {
  if (host_player->valid) return redirect_request(udp);

  int ip = udp->get_message_ip(), port = udp->get_message_port();

  switch (udp->read_byte()) {
    case REQ_SERVERLIST: {
      udp->write_line(server_config.name);
      udp->write_line("0 / " + std::to_string(server_config.max_players));
      udp->write_byte(server_config.no_cheat);
      udp->write_byte(0);
      udp->write_line(strlen(server_config.password) <= 1 ? "" : "PS");
      udp->write_byte(0);
      udp->write_byte(server_config.voice);
      udp->write_line(server_config.map_seed);
      udp->write_line(server_config.description);
      udp->write_line(server_config.game_state);
      udp->write_line(mp_version);
      udp->write_line(server_config.web_url);
      udp->send(ip, port);

      break;
    }

    case REQ_CONNECT: {
      udp->read_byte();
      std::string name = udp->read_line();
      std::string version = udp->read_line();
      std::string password = udp->read_line();
      int cl_version = udp->read_byte();

      std::string message;

      if (password != server_config.password) message = "Incorrect password.";
      if (name.empty()) message = "Your nickname cannot be empty.";
      if (mp_version != version || cl_version != client_version) message = "Your version doesn't match the server version.";

      if (!message.empty()) {
        udp->write_byte(REQ_CONNECTERROR);
        udp->write_line(message);
        udp->send(ip, port);
      } else {
        host_player->valid = true;
        host_player->ip = ip;
        host_player->port = port;
        host_player->last_tick = get_millisecs() + 30000;

        udp->read_short();
        udp->read_short();

        udp->write_byte(REQ_CONNECT);
        udp->write_byte(1);
        udp->write_line(server_config.map_seed);
        udp->write_byte(server_config.intro_enabled);
        udp->write_byte(server_config.no_cheat);
        udp->write_byte(server_config.voice);
        udp->write_float(1.f);
        udp->write_int(server_config.timeout);
        udp->write_float(server_config.gravity);
        udp->write_byte(server_config.jump_mode);
        udp->write_byte(server_config.max_players);
        udp->write_byte(server_config.tickrate);
        udp->write_byte(0);
        udp->write_byte(server_config.keep_inventory);
        udp->write_byte(3);
        udp->write_int(0);
        udp->write_int(0);
        udp->write_byte(0);
        udp->write_int(0);
        udp->write_byte(server_config.difficulty);
        udp->write_byte(0);
        udp->write_int(server_config.voice_quality);
        udp->write_line("");
        udp->write_byte(128);
        udp->send(ip, port);

        std::cout << "Host player joined from " << dotted_ip(ip) << ":" << port << "." << std::endl;
      }

      break;
    }
  }
}

void redirect_request(udp_stream* udp) {
  int ip = udp->get_message_ip(), port = udp->get_message_port();

  static bank* recv_bank;
  if (!recv_bank) recv_bank = create_bank(8192);

  if (ip == host_player->ip && port == host_player->port) {
    host_player->last_tick = get_millisecs() + 30000;
    recv_bank->resize(udp->read_available());

    if (recv_bank->get_size() != 0) {
      recv_bank->read_bytes(udp, 0, recv_bank->get_size());

      if (recv_bank->get_size() - 9 >= 0) {
        if (recv_bank->peek_byte(0) == REQ_DISCONNECT && recv_bank->peek_byte(recv_bank->get_size() - 9) != 254) {
          std::cout << "Host player disconnected." << std::endl;
          host_player->valid = false;
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
        recv_bank->write_bytes(udp, 0, recv_bank->get_size());
        udp->send(ip, port);
      } else {
        udp->write_int(host_player->ip);
        udp->write_int(host_player->port);
        recv_bank->write_bytes(udp, 0, recv_bank->get_size());
        udp->send(host_player->ip, host_player->port);
      }
    }
  } else {
    recv_bank->resize(udp->read_available());

    if (recv_bank->get_size() != 0) {
      recv_bank->read_bytes(udp, 0, recv_bank->get_size());
      udp->write_int(ip);
      udp->write_int(port);
      recv_bank->write_bytes(udp, 0, recv_bank->get_size());
      udp->send(host_player->ip, host_player->port);
    }
  }
}