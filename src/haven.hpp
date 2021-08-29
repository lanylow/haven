#pragma once

struct player {
    int ip, port, last_tick;
};

static player* host_player = nullptr;
static std::string mp_version = "1.0.4";
static int client_version = 2;