#include "../include.hpp"

bank::bank(int sz) {
  data = std::make_unique<std::vector<char>>(sz);
}

void bank::resize(int n) {
  data->resize(n);
}

int bank::get_size() {
  return data->size();
}

#define def_peek(ret_type, read_type, name) ret_type bank::name(int offset) { \
  return *(read_type*)(this->data->data() + offset); \
}

def_peek(int, unsigned char, peek_byte)
def_peek(int, unsigned short, peek_short)
def_peek(int, int, peek_int)
def_peek(float, float, peek_float)

#undef def_peek

#define def_poke(val_type, write_type, name) void bank::name(int offset, val_type value) { \
  *(write_type*)(this->data->data() + offset) = value; \
}

def_poke(int, char, poke_byte)
def_poke(int, unsigned short, poke_short)
def_poke(int, int, poke_int)
def_poke(float, float, poke_float)

#undef def_poke

int bank::read_bytes(base_stream& s, int offset, int count) {
  return s.read(this->data->data() + offset, count);
}

int bank::write_bytes(base_stream& s, int offset, int count) {
  return s.write(this->data->data() + offset, count);
}