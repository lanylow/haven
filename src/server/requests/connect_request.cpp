#include "../../include.hpp"

void requests::connect_request(udp_stream& stream) {
  int ip = stream.get_message_ip(), port = stream.get_message_port();

  stream.read_byte();
  std::string name = stream.read_line();
  std::string version = stream.read_line();
  std::string password = stream.read_line();
  int cl_version = stream.read_byte();

  std::string message;

  if (password != server_config.password) message = "Incorrect password.";
  if (name.empty()) message = "Your nickname cannot be empty.";
  if (MP_VER != version || cl_version != CL_VER) message = "Your version doesn't match the server version.";

  if (!message.empty()) {
    stream.write_byte(haven::request_connecterror);
    stream.write_line(message);
    stream.send(ip, port);
  } else {
    host_player& host = host_player::get();

    host.valid = true;
    host.ip = ip;
    host.port = port;
    host.last_tick = internal_clock::get_current_time() + 20000;

    stream.read_short();
    stream.read_short();

    stream.write_byte(haven::request_connect);
    stream.write_byte(1);
    stream.write_line(host.seed);
    stream.write_byte(server_config.intro_enabled);
    stream.write_byte(server_config.no_cheat);
    stream.write_byte(server_config.voice);
    stream.write_float(1.f);
    stream.write_int(server_config.timeout);
    stream.write_float(server_config.gravity);
    stream.write_byte(server_config.jump_mode);
    stream.write_byte(server_config.max_players);
    stream.write_byte(server_config.tickrate);
    stream.write_byte(0);
    stream.write_byte(server_config.keep_inventory);
    stream.write_byte(3);
    stream.write_int(0);
    stream.write_int(0);
    stream.write_byte(0);
    stream.write_int(0);
    stream.write_byte(server_config.difficulty);
    stream.write_byte(0);
    stream.write_int(server_config.voice_quality);
    stream.write_line("");
    stream.write_byte(128);
    stream.send(ip, port);

    logger::get().log("Host player joined from " + util::dotted_ip(ip) + ":" + std::to_string(port) + ".", logger::log_type_info);
  }
}
