#include "../include.hpp"

udp_socket::udp_socket(int port) {
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock != -1) {
    sockaddr_in address = { AF_INET, htons(port) };
    if (!bind(sock, (sockaddr*)&address, sizeof(address))) {
      socklen_t len = sizeof(addr);
      getsockname(sock, (sockaddr*)&addr, &len);
      in_addr = out_addr = addr;
      return;
    }
    close(sock);
  }
  logger::get().log("Failed to initialize UDP stream.", logger::log_type_error);
  exit(1);
}

udp_socket::~udp_socket() {
  int opt = 1;
  setsockopt(sock, SOL_SOCKET, ~SO_LINGER, (char*)&opt, sizeof(opt));
  close(sock);
}

int udp_socket::get_ip() {
  return ntohl(addr.sin_addr.s_addr);
}

int udp_socket::get_port() {
  return ntohs(addr.sin_port);
}

int udp_socket::get_message_ip() {
  return ntohl(in_addr.sin_addr.s_addr);
}

int udp_socket::get_message_port() {
  return ntohs(in_addr.sin_port);
}

int udp_socket::recieve(std::vector<char>& buffer) {
  for (;;) {
    buffer.resize(8192);
    unsigned int len = sizeof(in_addr);
    int n = recvfrom(sock, (char*)buffer.data(), 8192, 0, (sockaddr*)&in_addr, &len);
    if (n == -1) continue;
    buffer.resize(n);
    return get_message_ip();
  }
  return 0;
}

int udp_socket::send(int ip, int port, std::vector<char>& buffer) {
  int sz = buffer.size();
  out_addr.sin_addr.s_addr = htonl(ip);
  out_addr.sin_port = htons(port ? port : addr.sin_port);
  int n = sendto(sock, (char*)buffer.data(), sz, 0, (sockaddr*)&out_addr, sizeof(out_addr));
  if (n != sz) return -1;
  buffer.clear();
  return sz;
}