#include "../include.hpp"

int udp_stream::read(char* buff, int size) {
  int avail = in_buff.size() - pos;
  if (avail < size) size = avail;
  std::memcpy(buff, &in_buff[pos], size);
  pos += size;
  return size;
}

int udp_stream::write(const char* buff, int size) {
  out_buff.insert(out_buff.end(), buff, buff + size);
  return size;
}

int udp_stream::avail() {
  return in_buff.size() - pos;
}

int udp_stream::recieve() {
  pos = 0;
  return sock.recieve(in_buff);
}

int udp_stream::send(int ip, int port) {
  return sock.send(ip, port, out_buff);
}