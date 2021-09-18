#include "../include.hpp"

std::chrono::time_point<std::chrono::high_resolution_clock> internal_clock::get_current() {
  return std::chrono::high_resolution_clock::now();
}

long long internal_clock::get_current_time() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(get_current().time_since_epoch()).count();
}