#pragma once

class logger : public singleton<logger> {
 private:
  std::array<std::string, 3> prefixes {
    "\033[92m[info] \033[0m",
    "\033[93m[warn] \033[0m",
    "\033[91m[err] \033[0m"
  };

 public:
  enum log_type {
    log_type_info,
    log_type_warning,
    log_type_error
  };

  void log(const std::string& text, log_type type) {
    std::cout << prefixes[type] << text << std::endl;
  }
};