#include "../../include.hpp"

void server_list_request::invoke(udp_stream& stream, void* base_class) {
  int ip = stream.get_message_ip(), port = stream.get_message_port();

  stream.write_line(server_config.name);
  stream.write_line("0 / " + std::to_string(server_config.max_players));
  stream.write_byte(server_config.no_cheat);
  stream.write_byte(0);
  stream.write_line(strlen(server_config.password) <= 1 ? "" : "PS");
  stream.write_byte(0);
  stream.write_byte(server_config.voice);
  stream.write_line(server_config.map_seed);
  stream.write_line(server_config.description);
  stream.write_line(server_config.game_state);
  stream.write_line(MP_VER);
  stream.write_line(server_config.web_url);

  stream.send(ip, port);
}