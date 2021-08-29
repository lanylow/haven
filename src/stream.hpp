#pragma once

class stream {
public:
    stream();
    virtual ~stream();

    virtual int read(char* buffer, int size) = 0;
    virtual int write(const char* buffer, int size) = 0;
    virtual int available() = 0;
    virtual int eof() = 0;

    int read_available();
    int read_byte();
    int read_short();
    int read_int();
    float read_float();
    std::string read_string();
    std::string read_line();

    void write_byte(int n);
    void write_short(int n);
    void write_int(int n);
    void write_float(float n);
    void write_string(std::string t);
    void write_line(std::string t);
};