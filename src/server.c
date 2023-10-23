#include "../include/server.h"

struct addrinfo hints;
struct addrinfo *res;
struct sockaddr_storage their_addr;

int server(int portnum){
  int sockfd;
  int new_fd;
  int numbytes;
  char buf[MAXDATASIZE];
  char port[6];
  socklen_t addr_size;
  

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  sprintf(port, "%d", portnum);
  getaddrinfo(NULL, port, &hints, &res);
  
  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  bind(sockfd, res->ai_addr, res->ai_addrlen);
  
  if (listen(sockfd, BACKLOG) != -1){
    printf("Success! Listening at port %s... (Ctrl-C to quit)\n", port);
  }else{
    perror("listen");
  }

  addr_size = sizeof their_addr;
  new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
  numbytes = recv(new_fd, buf, MAXDATASIZE - 1, 0);
  //printf("%d", numbytes);
  buf[numbytes] = '\0';
  printf("%s\n", buf);
  freeaddrinfo(res);
  close(new_fd);
  shutdown(sockfd, SHUT_RDWR);

  return(0);
}
