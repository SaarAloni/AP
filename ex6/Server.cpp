
#include "Server.h"
#include <sys/socket.h>

Server::Server(int port)throw (const char*) {
	this->port = port;
}

void Server::start(ClientHandler& ch)throw(const char*){
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
}

void Server::stop(){
	t->join(); // do not delete this!
}

Server::~Server() {
}
