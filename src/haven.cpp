#include "include.hpp"

void draw_logo() {
    std::cout << "\033[92m";
    std::cout << R"(  __    __       __  ___      ___  _______  _____  ___   )" << std::endl;
    std::cout << R"( /" |  | "\     /""\|"  \    /"  |/"     "|(\"   \|"  \  )" << std::endl;
    std::cout << R"((:  (__)  :)   /    \\   \  //  /(: ______)|.\\   \    | )" << std::endl;
    std::cout << R"( \/      \/   /' /\  \\\  \/. ./  \/    |  |: \.   \\  | )" << std::endl;
    std::cout << R"( //  __  \\  //  __'  \\.    //   // ___)_ |.  \    \. | )" << std::endl;
    std::cout << R"((:  (  )  :)/   /  \\  \\\   /   (:      "||    \    \ | )" << std::endl;
    std::cout << R"( \__|  |__/(___/    \___)\__/     \_______) \___|\____\) )" << std::endl;
    std::cout << R"(                                                         )" << std::endl;
}

int main() {
    draw_logo();

    std::cout << "\033[96m";
    std::cout << std::endl << "Welcome to Haven project!" << std::endl;
    std::cout << "This is an unofficial SCP: Containment Breach Multiplayer Mod lite server for unix-based operating systems." << std::endl;
    std::cout << "Created by lanylow." << std::endl << std::endl;
    std::cout << "\033[97m";

    std::cout << "Creating UDP server on port 50021." << std::endl;

    udp_stream* udp = create_udp_stream(50021);

    if (!udp) {
        std::cout << "\033[91mFailed to create UDP server, aborting.\033[97m" << std::endl;
        exit(0);
    }

    while (true) {
        while (udp->recieve()) {
            if (host_player == nullptr) handle_request(udp);
            else redirect_request(udp);
        }

        sleep(10);
    }
}