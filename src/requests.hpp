#pragma once

enum {
    REQ_DISCONNECT = 13,
    REQ_CONNECT = 26,
    REQ_SERVERLIST = 35,
    REQ_CONNECTERROR = 113
};

void handle_request(udp_stream* udp);
void redirect_request(udp_stream* udp);