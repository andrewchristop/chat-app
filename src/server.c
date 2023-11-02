#include "../include/server.h"

struct addrinfo hints;
struct addrinfo *res;
struct sockaddr_storage their_addr;

void *sendMessage(void *socket){
  int sock_fd = (int)socket;
  char message[1024] = "";
  while(fgets(message, 1024, stdin) != NULL){
    
    if ((send(sock_fd, message, strlen(message), 0) < 0)){
      perror("Send failed no clients in the room");
      exit(1);
    }
  }
  return(NULL);
}

void *receive(void *socket){
  int sock_fd = (int)socket;
  int numbytes;
  char buf[1024];
  
  memset(buf, 0, 1024);

  while (1){
    if ((numbytes = recv(sock_fd, buf, MAXDATASIZE - 1, 0)) > 0){
     buf[numbytes] = '\0';
     printf("%s\n", buf);
    } 
  }
  return(NULL);
}

int server(int portnum){
  int sockfd;
  int new_fd;
  int numbytes;
  char buf[MAXDATASIZE];
  char port[6];
  socklen_t addr_size;
  pthread_t thread1;
  pthread_t thread2;  

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
  pthread_create(&thread1, NULL, receive, (void *)new_fd);
  pthread_create(&thread2, NULL, sendMessage, (void *)new_fd);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  freeaddrinfo(res);
  //close(new_fd);
  //shutdown(sockfd, SHUT_RDWR);
  //pthread_exit(NULL);

  return(0);
}
