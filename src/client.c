#include "../include/client.h"

struct addrinfo hints;
struct addrinfo *res;
int client(char *host, int portnum){
  int status;
  int sockfd;
  int val; 
  int len;
  int bytes_sent;
  char port[6];
  char msg[1000];

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  
  sprintf(port, "%d", portnum); 

  status = getaddrinfo(host, port, &hints, &res);

  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (connect(sockfd, res->ai_addr, res->ai_addrlen) != -1){
    printf("\nConnection successful!\n");
  }

  do {
    printf("\nclient:");
    scanf(" %[^\n]s", msg);
    if (strcmp(msg, TERM) == 0){
      break;
    }
    len = strlen(msg);
    bytes_sent = send(sockfd, msg, len, 0);
  }while(1);


  close(sockfd);
  

  return(0);
}
