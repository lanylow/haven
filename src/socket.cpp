#include "include.hpp"

udp_stream::udp_stream(unsigned int socket) : socket(socket), position(0), e(0) {
  socklen_t length = sizeof(address);
  getsockname(socket, (sockaddr*)&address, &length);
  input_address = output_address = address;
}

udp_stream::~udp_stream() {
  close_socket(socket, e);
}

int udp_stream::read(char* buffer, int size) {
  if (e) return 0;
  int available = input_buffer.size() - position;
  if (available < size) size = available;
  memcpy(buffer, &input_buffer[position], size);
  position += size;
  return size;
}

int udp_stream::write(const char* buffer, int size) {
  if (e) return 0;
  output_buffer.insert(output_buffer.end(), buffer, buffer + size);
  return size;
}

int udp_stream::available() {
  if (e) return 0;
  return input_buffer.size() - position;
}

int udp_stream::eof() {
  return e ? e : position == input_buffer.size();
}

int udp_stream::recieve() {
  if (e) return 0;

  static char buffer[512];
  memset(buffer, 0, 512);
  unsigned int length = sizeof(input_address);
  int size = recvfrom(socket, buffer, sizeof(buffer), 0, (sockaddr*)&input_address, &length);
  if (size == -1) return 0;
  input_buffer.resize(size);
  position = 0;
  memcpy(input_buffer.data(), buffer, size);
  return get_message_ip();
}

int udp_stream::send(int ip, int port) {
  if (e) return 0;
  int sz = output_buffer.size();
  output_address.sin_addr.s_addr = htonl(ip);
  output_address.sin_port = htons(port ? port : address.sin_port);
  int n = sendto(socket, (char*)output_buffer.data(), sz, 0, (sockaddr*)&output_address, sizeof(output_address));
  if (n != sz) return e = -1;
  output_buffer.clear();
  return sz;
}

int udp_stream::get_ip() {
  return ntohl(address.sin_addr.s_addr);
}

int udp_stream::get_port() {
  return ntohs(address.sin_port);
}

int udp_stream::get_message_ip() {
  return ntohl(input_address.sin_addr.s_addr);
}

int udp_stream::get_message_port() {
  return ntohs(input_address.sin_port);
}

void close_socket(unsigned int socket, int e) {
  if (e < 0) {
    int opt = 1;
    setsockopt(socket, SOL_SOCKET, ~SO_LINGER, (char*)&opt, sizeof(opt));
  }

  close(socket);
}

udp_stream* create_udp_stream(int port) {
  unsigned int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock != -1) {
    sockaddr_in address = {AF_INET, htons(port)};
    if (!bind(sock, (sockaddr*)&address, sizeof(address))) {
      udp_stream* stream = new udp_stream(sock);
      return stream;
    }
    close(sock);
  }
  return 0;
}

std::string dotted_ip(int ip) {
  return std::string(std::to_string((ip >> 24) & 255) + "." + std::to_string((ip >> 16) & 255) + "." + std::to_string((ip >> 8) & 255) + "." + std::to_string(ip & 255));
}