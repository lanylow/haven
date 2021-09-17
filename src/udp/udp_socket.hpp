#pragma once

class udp_socket {
 public:
  udp_socket(int port);
  ~udp_socket();

  int get_ip();
  int get_port();
  int get_message_ip();
  int get_message_port();

  int recieve(std::vector<char>& buffer);
  int send(int ip, int port, std::vector<char>& buffer);

 private:
  unsigned int sock;
  sockaddr_in addr, in_addr, out_addr;
};