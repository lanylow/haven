#pragma once

class connect_request : public base_request {
 public:
  connect_request() { }

  virtual void invoke(udp_stream& stream, void* base_class) override;
};

class server_list_request : public base_request {
 public:
  server_list_request() { }

  virtual void invoke(udp_stream& stream, void* base_class) override;
};