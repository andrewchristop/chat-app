#include "../include/client.h"

#define MAX_MESSAGE_SIZE 1024

typedef struct{
  int socket;
}thread_data;

void *receiveMessage(void *threadData) {
  int sock_fd;
  char message[MAX_MESSAGE_SIZE];
  thread_data *pData = (thread_data*)threadData;
  sock_fd = pData->socket;
  int bytesRead;

  while (1) {
    bytesRead = recv(sock_fd, message, MAX_MESSAGE_SIZE, 0);
    if (bytesRead <= 0) {
      // Handle server disconnect or error
      printf("Server disconnected. Exiting.\n");
      close(sock_fd);
      exit(1);
    } else {
      // Process the received message (you can modify this part)
      message[bytesRead] = '\0';
      printf("Server: %s\n", message);
    }
  }
  return NULL;
}

void *sendMessage(void *clientSocket){
  char message[MAX_MESSAGE_SIZE];
  int sock_fd = *((int *)clientSocket);
  
  while (1) {
    fgets(message, MAX_MESSAGE_SIZE, stdin);
    send(sock_fd, message, strlen(message), 0);
  }
}

int client(char *host, int portnum) {
  int sockfd;
  char message[1024];
  struct sockaddr_in serverAddr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("Socket creation failed");
    return 1;
  }

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(portnum);
  serverAddr.sin_addr.s_addr = inet_addr(host);

  if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    perror("Connection failed");
    return 1;
  }

  while (1){
    scanf("%s", &message[0]);
    send(sockfd, message, strlen(message), 0);
    if (recv(sockfd, message, 1024, 0) < 0){
      printf("Error\n");
    }else{
      printf("Server: \t%s\n", message);
    }
  }

 // pthread_t thread;
 // pthread_t thread_send;
 // thread_data data;
 // data.socket = sockfd;
 // pthread_create(&thread, NULL, receiveMessage, (void *) &data);
 // pthread_create(&thread_send, NULL, sendMessage, &sockfd);
 // 
 // pthread_join(thread, NULL);
 // pthread_join(thread_send, NULL);

  // Cleanup and close client socket
  close(sockfd);
  return 0;
}

