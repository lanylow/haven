#pragma once

class haven {
 public:
  haven(udp_stream& stream) : stream(stream) { }

  void run();
  void redirect_request();

  enum request {
    request_disconnect = 13,
    request_connect = 26,
    request_serverlist = 35,
    request_connecterror = 113
  };

  struct {
    int ip, port, last_tick, send_tick;
    bool valid = false;
  } host_player;

 private:
  udp_stream& stream;
  std::vector<std::pair<int, std::shared_ptr<base_request>>> requests = {
    { request_connect, std::shared_ptr<base_request>(new connect_request()) },
    { request_serverlist, std::shared_ptr<base_request>(new server_list_request()) }
  };
};