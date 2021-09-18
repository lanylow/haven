#pragma once

namespace internal_clock {
  std::chrono::time_point<std::chrono::high_resolution_clock> get_current();
  long long get_current_time();
}