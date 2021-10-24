#pragma once

namespace util {
  std::string decode_base64(const std::string& enc);
  std::string dotted_ip(int ip);
	std::string random_string(int len);
}
