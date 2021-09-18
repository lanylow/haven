#pragma once

class bank {
 public:
  bank(int sz);

  void resize(int n);
  int get_size();

  int peek_byte(int offset);
  int peek_short(int offset);
  int peek_int(int offset);
  float peek_float(int offset);

  void poke_byte(int offset, int value);
  void poke_short(int offset, int value);
  void poke_int(int offset, int value);
  void poke_float(int offset, float value);

  int read_bytes(base_stream& s, int offset, int count);
  int write_bytes(base_stream& s, int offset, int count);

 private:
  std::unique_ptr<std::vector<char>> data;
};