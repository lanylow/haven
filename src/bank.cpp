#include "include.hpp"

bank::bank(int sz) : size(sz) {
    capacity = (size + 15) &~ 15;
    data = new char[capacity];
    memset(data, 0, size);
}

bank::~bank() {
    delete[] data;
}

void bank::resize(int n) {
    if (n > size) {
        if (n > capacity) {
            capacity = capacity * 3 / 2;
            if (n > capacity) capacity = n;
            capacity = (capacity + 15) &~ 15;
            char* p = new char[capacity];
            memcpy(p, data, size);
            delete[] data;
            data = p;
        } else {
            memset(data + size, 0, n - size);
        }
    }
    size = n;
}

int bank::get_size() {
    return this->size;
}

int bank::peek_byte(int offset) {
    return *(unsigned char*)(this->data + offset);
}

int bank::peek_short(int offset) {
    return *(unsigned short*)(this->data + offset);
}

int bank::peek_int(int offset) {
    return *(int*)(this->data + offset);
}

float bank::peek_float(int offset) {
    return *(float*)(this->data + offset);
}

void bank::poke_byte(int offset, int value) {
    *(char*)(this->data + offset) = value;
}

void bank::poke_short(int offset, int value) {
    *(unsigned short*)(this->data + offset) = value;
}

void bank::poke_int(int offset, int value) {
    *(int*)(this->data + offset) = value;
}

void bank::poke_float(int offset, float value) {
    *(float*)(this->data + offset) = value;
}

int bank::read_bytes(stream* s, int offset, int count) {
    return s->read(this->data + offset, count);
}

int bank::write_bytes(stream* s, int offset, int count) {
    return s->write(this->data + offset, count);
}

bank* create_bank(int size) {
    bank* b = new bank(size);
    return b;
}

void free_bank(bank* b) {
    delete b;
}