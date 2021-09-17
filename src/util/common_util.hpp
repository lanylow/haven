#pragma once

namespace util {
  std::string decode_base64(const std::string& enc);
  std::string dotted_ip(int ip);
  int get_millisecs();
}