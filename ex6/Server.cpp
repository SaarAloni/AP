
#include "Server.h"

Server::Server(int port)throw (const char*) {
	this->port = port;
}
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void* con(void *args){
	int* sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	while(true) {
		std::cout << "start" << '\n';
		clilen = sizeof(cli_addr);
		sockfd = static_cast<int *>(args);
		newsockfd = accept(*sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0)
				 error("ERROR on accept");
	 SocketIO df(newsockfd);
	 CLI cli(&df);
	 cli.start();
	 close(newsockfd);
	}
}

void Server::start(ClientHandler& ch)throw(const char*){
			int sockfd, newsockfd, portno;
			socklen_t clilen;
			char buffer[256];
			struct sockaddr_in serv_addr, cli_addr;
			int n;
			sockfd = socket(AF_INET, SOCK_STREAM, 0);
			if (sockfd < 0)
				 error("ERROR opening socket");
			bzero((char *) &serv_addr, sizeof(serv_addr));
			serv_addr.sin_family = AF_INET;
			serv_addr.sin_addr.s_addr = INADDR_ANY;
			int po = this->port;
			serv_addr.sin_port = htons(po);
			if (bind(sockfd, (struct sockaddr *) &serv_addr,
							 sizeof(serv_addr)) < 0)
							 error("ERROR on binding");
			listen(sockfd,5);
			pthread_t t;
			pthread_attr_t attr;
			int rc;
			rc = pthread_attr_init(&attr);
			rc = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
			int * r =(int *) malloc(sizeof(int)) ;
			*r = sockfd;
			//(void)pthread_create(NULL, &attr_baseb, &con,  &po);
			pthread_create(&t,&attr, con, r);

		// // pthread_attr_t attr_baseb;
	 // // (void)pthread_attr_init(&attr_baseb);
	 // // (void)pthread_attr_setdetachstate(&attr_baseb, PTHREAD_CREATE_DETACHED);
	 // pthread_t t;
	 // int * po = ( int *) malloc(sizeof(int));
	 // //(void)pthread_create(NULL, &attr_baseb, &con,  &po);
	 // pthread_create(&t,0, con, po);

}



void Server::stop(){
	t->join(); // do not delete this!
}

Server::~Server() {
}
