#include "../../include.hpp"

void connect_request::invoke(udp_stream& stream, void* base_class) {
  int ip = stream.get_message_ip(), port = stream.get_message_port();
  haven* base = (haven*)base_class;

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
    base->host_player.valid = true;
    base->host_player.ip = ip;
    base->host_player.port = port;
    base->host_player.last_tick = util::get_millisecs() + 30000;

    stream.read_short();
    stream.read_short();

    stream.write_byte(haven::request_connect);
    stream.write_byte(1);
    stream.write_line(server_config.map_seed);
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