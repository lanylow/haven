#include "include.hpp"

void handle_request(udp_stream* udp) {
    int ip = udp->get_message_ip(), port = udp->get_message_port();

    switch (udp->read_byte()) {
        case REQ_SERVERLIST: {
            std::cout << "REQ_SERVERLIST" << std::endl;

            udp->write_line("haven server");
            udp->write_line("0 / 16");
            udp->write_byte(1);
            udp->write_byte(0);
            udp->write_line("");
            udp->write_byte(0);
            udp->write_byte(1);
            udp->write_line("seed");
            udp->write_line("cool description");
            udp->write_line("in lobby");
            udp->write_line(mp_version);
            udp->write_line("none");
            udp->send(ip, port);

            break;
        }
    }
}

void redirect_request(udp_stream* udp) {

}