#pragma once

class base_stream {
 public:
  virtual int read(char* buff, int size) = 0;
  virtual int write(const char* buff, int size) = 0;
  virtual int avail() = 0;
  
  int read_avail();
  
  int read_byte();
  int read_short();
  int read_int();
  float read_float();
  std::string read_line();

  void write_byte(int n);
  void write_short(int n);
  void write_int(int n);
  void write_float(float n);
  void write_line(const std::string& t);
};