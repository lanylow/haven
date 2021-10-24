#include "../include.hpp"

const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string util::decode_base64(const std::string& enc) {
  std::string o; std::vector<int> t(256, -1);
  unsigned int val = 0; int valb = -8;
  for (int i = 0; i < 64; i++) t[base64_chars[i]] = i;
  for (unsigned char c : enc) {
    if (t[c] == -1) break;
    val = (val << 6) + t[c];
    valb += 6;
    if (valb >= 0) {
      o.push_back(char((val >> valb) & 0xFF));
      valb -= 8;
    }
  }
  return o;
}

std::string util::dotted_ip(int ip) {
  std::stringstream ip_stream;
  ip_stream << ((ip >> 24) & 255) << "."
            << ((ip >> 16) & 255) << "."
            << ((ip >> 8) & 255) << "."
            << ((ip) & 255);
  return ip_stream.str();
}

std::string util::random_string(int len) {
	static auto& chars = "0123456789abcdefghijklmnopqrstuwxyzABCDEFGHIJKLMNOPQRSTUWXYZ";
	static std::mt19937 random{ std::random_device{ }() };
	static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chars) - 2);
 	std::string temp;
	temp.reserve(len);
	while (len--)
		temp += chars[pick(random)];
	return temp;
}
