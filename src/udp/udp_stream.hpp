#pragma once

class udp_stream : public base_stream {
 public:
  udp_stream(udp_socket& socket) : sock(socket) { }

  int read(char* buff, int size);
  int write(const char* buff, int size);
  int avail();

  int recieve();
  int send(int ip, int port);

  int get_ip() { return sock.get_ip(); }
  int get_port() { return sock.get_port(); }
  int get_message_ip() { return sock.get_message_ip(); }
  int get_message_port() { return sock.get_message_port(); }

 private:
  udp_socket& sock;
  std::vector<char> in_buff, out_buff;
  int pos;
};