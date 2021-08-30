#pragma once

class udp_stream : public stream {
public:
    udp_stream(unsigned int socket);
    ~udp_stream();

    int read(char* buffer, int size);
    int write(const char* buffer, int size);
    int available();
    int eof();

    int recieve();
    int send(int ip, int port);
    int get_ip();
    int get_port();
    int get_message_ip();
    int get_message_port();

private:
    unsigned int socket;
    std::vector<char> input_buffer, output_buffer;
    sockaddr_in address, input_address, output_address;
    int position, e;
};

void close_socket(unsigned int socket, int e);
udp_stream* create_udp_stream(int port);
std::string dotted_ip(int ip);