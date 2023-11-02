#include "../include/client.h"

struct addrinfo hints;
struct addrinfo *res;

void *sendMessageClient(void *socket){
  int sock_fd = (int)socket;
  int bytes_sent;
  int len;
  char message[1024] = "";  
  while(fgets(message, 1024, stdin) != NULL){ 
    if ((send(sock_fd, message, strlen(message), 0) < 0)){
      perror("Send failed");
      exit(1);
    }
  }

  return(NULL);
}

void *receiveMessageClient(void *socket){
  int sock_fd = (int)socket;
  int numbytes;
  char buf[1024];

  memset(buf, 0, 1024);
  while(1){
    if ((numbytes = recv(sock_fd, buf, 1023, 0)) > 0){
      buf[numbytes] = '\0';
      if (buf[0] != '\0'){
        printf("Server: %s\n", buf);
      }
    }
  }
  return(NULL);
}

int client(char *host, int portnum){
  int status;
  int sockfd;
  int val; 
  int len;
  int bytes_sent;
  char port[6];
  char msg[1000];
  pthread_t thread1;
  pthread_t thread2;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  
  sprintf(port, "%d", portnum); 

  status = getaddrinfo(host, port, &hints, &res);

  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (connect(sockfd, res->ai_addr, res->ai_addrlen) != -1){
    printf("\nConnection successful!\n");
  }
  
  pthread_create(&thread1, NULL, sendMessageClient, (void *)sockfd);
  pthread_create(&thread1, NULL, receiveMessageClient, (void*)sockfd);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);


  close(sockfd);
  

  return(0);
}
