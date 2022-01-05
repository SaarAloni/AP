
#include "Server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

Server::Server(int port)throw (const char*) {
	this->port = port;
}

void Server::connect(int soc)throw(const char*){
	int newsoc;
	socklen_t clilen, cli_addr;
	while(true) {
		clilen = sizeof(cli_addr);
		newsoc = accept(soc, (struct sockaddr *) &cli_addr, &clilen);
		if (newsoc < 0) {
			perror("ERROR on accept");
			exit(1);
		}
		SocketIO df(newsoc);
		CLI cli(&df);
		cli.start();
		close(newsoc);
	}
}

void Server::start(ClientHandler& ch)throw(const char*){
	struct sockaddr_in serv_addr;
	int soc, newsoc;
	socklen_t clilen;
	soc =  socket(AF_INET, SOCK_STREAM, 0);
	if (soc < 0){
			perror("ERROR opening socket");
			exit(1);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(this->port);
	if (bind(soc, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
								  perror("ERROR on binding");
									exit(1);
							}
	listen(soc,5);
	std::thread first (&Server::connect,this ,soc);
	this->t = &first;
	close(soc);
}



void Server::stop(){
	t->join(); // do not delete this!
}

Server::~Server() {
}
