// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <pthread.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void * con(void * args) {
  std::cout << "/* message */" << '\n';
  int* sockfd, newsockfd, portno;
      socklen_t clilen;
      char buffer[256];
      struct sockaddr_in serv_addr, cli_addr;
      int n;
  while(true) {
    clilen = sizeof(cli_addr);
    sockfd = static_cast<int *>(args);
    newsockfd = accept(*sockfd,
                (struct sockaddr *) &cli_addr,
                &clilen);
               printf("%d\n",clilen);
    if (newsockfd < 0)
         error("ERROR on accept");
    }
}

int main(int argc, char const *argv[])
{
	int sockfd, newsockfd, portno;
      socklen_t clilen;
      char buffer[256];
      struct sockaddr_in serv_addr, cli_addr;
      int n;
      sockfd = socket(AF_INET, SOCK_STREAM, 0);
      if (sockfd < 0)
         error("ERROR opening socket");
      bzero((char *) &serv_addr, sizeof(serv_addr));
			std::cout << "here" << '\n';
      serv_addr.sin_family = AF_INET;
      serv_addr.sin_addr.s_addr = INADDR_ANY;
      int po = 8080;
      serv_addr.sin_port = htons(po);
      if (bind(sockfd, (struct sockaddr *) &serv_addr,
               sizeof(serv_addr)) < 0)
               error("ERROR on binding");
      listen(sockfd,5);
      printf("%d\n",sockfd);
      pthread_t t;
      pthread_attr_t attr;

      int rc;

      rc = pthread_attr_init(&attr);

      printf("attr_init: %d\n",rc);
      rc = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
      int * r =(int *) malloc(sizeof(int)) ;
      *r = sockfd;
      //(void)pthread_create(NULL, &attr_baseb, &con,  &po);
      pthread_create(&t,&attr, con, r);
      


}
