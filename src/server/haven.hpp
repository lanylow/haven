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

 private:
  udp_stream& stream;
  std::map<int, std::function<void(udp_stream&)>> requests = {
    { request_connect, requests::connect_request },
    { request_serverlist, requests::server_list_request }
  };
};

class host_player : public singleton<host_player> {
 public:
  int ip, port, last_tick, send_tick;
  bool valid = false;
};