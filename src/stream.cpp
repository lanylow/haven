#include "include.hpp"

static std::set<stream*> stream_set;

stream::stream() {
    stream_set.insert(this);
}

stream::~stream() {
    stream_set.erase(this);
}

int stream::read_available() {
    return this->available();
}

int stream::read_byte() {
    int n = 0;
    this->read((char*)&n, 1);
    return n;
}

int stream::read_short() {
    int n = 0;
    this->read((char*)&n, 2);
    return n;
}

int stream::read_int() {
    int n = 0;
    this->read((char*)&n, 4);
    return n;
}

float stream::read_float() {
    float n = 0;
    this->read((char*)&n, 4);
    return n;
}

std::string stream::read_string() {
    int length;
    std::string string;
    if (this->read((char*)&length, 4)) {
        char* buffer = new char[length];
        if (this->read(buffer, length)) {
            string = std::string(buffer, length);
        }
        delete[] buffer;
    }
    return string;
}

std::string stream::read_line() {
    unsigned char c;
    std::string string;
    while (true) {
        if (this->read((char*)&c, 1) != 1) break;
        if (c == '\n') break;
        if (c != '\r') string += c;
    }
    return string;
}

void stream::write_byte(int n) {
    this->write((char*)&n, 1);
}

void stream::write_short(int n) {
    this->write((char*)&n, 2);
}

void stream::write_int(int n) {
    this->write((char*)&n, 4);
}

void stream::write_float(float n) {
    this->write((char*)&n, 4);
}

void stream::write_string(std::string t) {
    int n = t.size();
    this->write((char*)&n, 4);
    this->write(t.data(), t.size());
}

void stream::write_line(std::string t) {
    this->write(t.data(), t.size());
    this->write("\r\n", 2);
}