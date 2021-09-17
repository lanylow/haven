#pragma once

class base_request {
 public:
  base_request() { }

  virtual void invoke(udp_stream& stream, void* base_class) = 0;
};