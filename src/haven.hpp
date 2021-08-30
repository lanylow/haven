#pragma once

struct player {
  int ip, port, last_tick, send_tick;
  bool valid = false;
};

static player* host_player = new player();
static std::string mp_version = "1.0.4";
static int client_version = 2;

static int get_millisecs() {
  return std::chrono::high_resolution_clock::now().time_since_epoch().count();
}