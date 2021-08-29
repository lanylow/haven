#pragma once

struct {
    int port = 50021;
    int no_cheat = 0;
    int intro_enabled = 0;
    int timeout = 30000; 
    int voice = 1;
    int max_players = 16;
    int jump_mode = 1;
    float gravity = 0.0023f;
    int difficulty = 0;
    int tickrate = 128;
    int keep_inventory = 0;
    int voice_quality = 22050;
    const char* password = "";
    const char* game_state = "In lobby";
    const char* name = "SCP Server";
    const char* description = "SCP Server running on haven.";
    const char* web_url = "https://github.com/lanylow/haven";
    const char* map_seed = "haven";
} server_config;