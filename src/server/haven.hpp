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
  int ip, port;
  long long last_tick, send_tick;
  bool valid = false;
	const char* seed;

	void invalidate() {
		valid = false;
		if (server_config.random_seed)
			seed = util::random_string(6).c_str();
		else 
			seed = server_config.map_seed;
	}
};
