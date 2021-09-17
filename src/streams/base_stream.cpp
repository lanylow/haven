#include "../include.hpp"

int base_stream::read_avail() { 
  return this->avail(); 
}

#define def_read(type, size, name) type base_stream::name() { \
  type n = 0; \
  this->read((char*)&n, size); \
  return n; \
}

def_read(int, 1, read_byte)
def_read(int, 2, read_short)
def_read(int, 4, read_int)
def_read(float, 4, read_float)

#undef def_read

std::string base_stream::read_line() {
  unsigned char c;
  std::string o;
  for (;;) {
    if (this->read((char*)&c, 1) != 1) break;
    if (c == '\n') break;
    if (c != '\r') o += c;
  }
  return o;
}

#define def_write(type, size, name) void base_stream::name(type n) { \
  this->write((char*)&n, size); \
}

def_write(int, 1, write_byte)
def_write(int, 2, write_short)
def_write(int, 4, write_int)
def_write(float, 4, write_float)

#undef def_write

void base_stream::write_line(const std::string& t) {
  this->write(t.data(), t.size());
  this->write("\r\n", 2);
}