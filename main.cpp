
#include "server.hpp"
#include "command.hpp"
#include <iostream>




int main() {
    server_class server;
    command cmd;
    std::string buffer;

    if (!server.server_init()) {
        std::cerr << "Server initialization failed" << std::endl;
        return -1;
    }
    if (!server.server_lisen()) {
        std::cerr << "Server listening failed" << std::endl;
        return -2;
    }

    while (true) {
        std::cout << "Waiting for client connection..." << std::endl;
        if (server.server_accept_client()) {
            std::cout << "Client connected." << std::endl;
            server.server_send_msg("/--------------------/\n");
            server.server_send_msg("menu\n");
            server.server_send_msg("Enter a command or type 'exit' to quit\n");

            while (true) {
                buffer = server.server_read();
               

                if (buffer == "exit") {
                    server.server_send_msg("Exiting the server...\n");
                    server.server_close();
                    std::cout << "Program finished." << std::endl;
                    return 0;
                }

                if (buffer == "terminal") {
                    buffer = cmd.open_terminal();
                    server.server_send_msg(buffer);
                    buffer = "nothing"; // Reset buffer for next read
                }

                else if (buffer == "firefox") {
                    buffer = cmd.open_firefox();
                    server.server_send_msg(buffer);
                    buffer = "nothing"; // Reset buffer for next read
                }

                else if (buffer == "calculator") {
                    buffer = cmd.open_calculator();
                    server.server_send_msg(buffer);
                    buffer = "nothing"; // Reset buffer for next read
                }
                
                
            }
        }
    }
}