#ifndef SERVER_HPP
#define SERVER_HPP


#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <array>

#include <cerrno>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


class server_class{
    private:
        int socket_info;
        int client_info;
     std::array<char,60000> buffer;
    public:
        server_class();
        ~server_class();

        bool server_init();
        bool server_lisen();
        bool server_accept_client();
        bool server_send_msg(const std::string& message);
        std::string server_read();
        void close_listening_server();
        void close_listening_client();
        void server_close();


};

#endif 