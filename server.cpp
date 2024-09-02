
#include "server.hpp"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>



server_class::server_class(){}
//In many systems, -1 is used to indicate an invalid or uninitialized file descriptor.
server_class::~server_class(){
    if( socket_info != -1 ){
        close(socket_info);
    }
    if( client_info != -1 ){
        close(client_info);
    }
}

void server_class::close_listening_server(){
    close(socket_info);
}
void server_class::close_listening_client(){
    close(client_info);
}

// first create socket
bool server_class::server_init() {
    sockaddr_in socket_address;

    socket_info = socket(AF_INET, SOCK_STREAM, 0); // AF_INET Address family for IPv4. SOCK_STREAM --> TCP
    if (socket_info < 0) {
        std::cerr << "cannot create socket" << std::endl;
        return false;
    }

    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(4444 );
    socket_address.sin_addr.s_addr = INADDR_ANY; // Bind to any available network interface

    if (bind(socket_info, (sockaddr*)&socket_address, sizeof(socket_address)) < 0) {
        std::cerr << "cannot bind" << std::endl;
        return false;
    }

    return true;
}
/*bool server_class::server_init(){
    sockaddr_in socket_address;

    socket_info = socket(AF_INET,SOCK_STREAM,0); //AF_INET Address family for IPv4.---- SOCK_STREAM -->TCP
    if(socket_info < 0){
        std::cerr<<"can not create socket"<<std::endl;
        return -1;
    }
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(4444);
    inet_pton(AF_INET,"192.168.1.5",&socket_address.sin_addr);
    if(bind(socket_info, (sockaddr*)&socket_address,sizeof(socket_address)) < 0){
        std::cerr<<"can not bind"<<std::endl;
        return -2;
    }
    return true;
}*/

bool server_class::server_lisen(){
    if(listen(socket_info,2)<0){
        std::cout<<"cannot listen "<<std::endl;
    }
    return 1;
}

bool server_class::server_accept_client() {
    sockaddr_in client;
    socklen_t client_size = sizeof(client);
    client_info = accept(socket_info, (sockaddr*)&client, &client_size);

    if (client_info < 0) {
        std::cout << "Problem with client connection" << std::endl;
        return false; 
    }
    return true; 
}



bool server_class::server_send_msg(const std::string& massaage){
    send(client_info,massaage.c_str(),massaage.size(),0);
    return true;
}

std::string server_class::server_read() {
    ssize_t byteread = recv(client_info, static_cast<void*>(buffer.data()), buffer.size() -1, 0);

    if (byteread < 0) {
        std::cerr << "Error receiving data" << std::endl;
        return "Error receiving data";
    } else if (byteread == 0) {

        return "Client closed connection";
    } else {
        std::string buffer_str(buffer.data(), byteread);
        std::cout << "Received message: " << buffer_str << std::endl;
        return buffer_str;
    }
}

void server_class::server_close(){
    client_info = -1;
    if(client_info != -1){
        close(client_info);
    }
}

