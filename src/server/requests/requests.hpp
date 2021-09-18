#pragma once

namespace requests {
  void connect_request(udp_stream& stream);
  void server_list_request(udp_stream& stream);
}