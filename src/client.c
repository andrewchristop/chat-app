#include "../include/client.h"

#define MAX_MESSAGE_SIZE 1024

void *receiveMessage(void *clientSocket) {
  int sock_fd = *((int *)clientSocket);
  char message[MAX_MESSAGE_SIZE];
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

int client(char *host, int portnum) {
  int sockfd;
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

  pthread_t thread;
  pthread_create(&thread, NULL, receiveMessage, &sockfd);

  char message[MAX_MESSAGE_SIZE];
  while (1) {
    fgets(message, MAX_MESSAGE_SIZE, stdin);
    send(sockfd, message, strlen(message), 0);
  }

  // Cleanup and close client socket
  close(sockfd);
  return 0;
}

