#include "include.hpp"

#define haven_logo \
  "ICBfXyAgICBfXyAgICAgICBfXyAgX19fICAgICAgX19fICBfX19fX19fICBfX19fXyAgX19fICAgCiAvIiB8ICB8ICJcICAg" \
  "ICAvIiJcfCIgIFwgICAgLyIgIHwvIiAgICAgInwoXCIgICBcfCIgIFwgIAooOiAgKF9fKSAgOikgICAvICAgIFxcICAgXCAgL" \
  "y8gIC8oOiBfX19fX18pfC5cXCAgIFwgICAgfCAKIFwvICAgICAgXC8gICAvJyAvXCAgXFxcICBcLy4gLi8gIFwvICAgIHwgIH" \
  "w6IFwuICAgXFwgIHwgCiAvLyAgX18gIFxcICAvLyAgX18nICBcXC4gICAgLy8gICAvLyBfX18pXyB8LiAgXCAgICBcLiB8IAo" \
  "oOiAgKCAgKSAgOikvICAgLyAgXFwgIFxcXCAgIC8gICAoOiAgICAgICJ8fCAgICBcICAgIFwgfCAKIFxfX3wgIHxfXy8oX19f" \
  "LyAgICBcX19fKVxfXy8gICAgIFxfX19fX19fKSBcX19ffFxfX19fXCkgCiAgICAgICAgICAgICAgICAgICAgICAgICAgICAgI" \
  "CAgICAgICAgICAgICAgICAgICAgICAgICAgIA=="

int main() {
  std::cout << "\033[97m" << util::decode_base64(haven_logo) << std::endl << std::endl;
  std::cout << "Starting haven server, created by lanylow." << std::endl << std::endl;

  udp_socket socket(server_config.port);
  udp_stream stream(socket);
  haven server(stream);

  server.run();
}