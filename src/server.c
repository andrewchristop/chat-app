#include "../include/server.h"


#define MAX_CLIENTS 10
#define MAX_MESSAGE_SIZE 1024

int clients[MAX_CLIENTS]; // Array to store client sockets
pthread_t sendThreads[MAX_CLIENTS];
pthread_t receiveThreads[MAX_CLIENTS];

void *handleClient(void *clientSocket) {
  int clientSock = *((int *)clientSocket);
  char message[MAX_MESSAGE_SIZE];
  int bytesRead;

  while (1) {
    bytesRead = recv(clientSock, message, MAX_MESSAGE_SIZE, 0);
    if (bytesRead <= 0) {
      // Handle client disconnect or error
      close(clientSock);
      pthread_exit(NULL);
    } else {
      // Process the received message (you can modify this part)
      message[bytesRead] = '\0';
      printf("%s\n", message);
    }
  }
  return NULL;
}

void *sendMessages(void *clientSocket) {
  int sock_fd = *((int *)clientSocket);
  char message[MAX_MESSAGE_SIZE];

  while (1) {
    fgets(message, MAX_MESSAGE_SIZE, stdin);

    // Display the message locally
    printf("You: %s", message);

    // Send the message to the specific client
    send(sock_fd, message, strlen(message), 0);
  }

  return NULL;
}

int server(int portnum) {
  int sockfd, new_fd;
  struct sockaddr_in serverAddr, clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("Socket creation failed");
    return 1;
  }

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(portnum);
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    perror("Binding failed");
    return 1;
  }

  if (listen(sockfd, MAX_CLIENTS) < 0) {
    perror("Listen failed");
    return 1;
  }

  printf("Listening for clients on port %d... (Ctrl-C to quit)\n", portnum);

  int clientCount = 0;
  while (1) {
    new_fd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (new_fd < 0) {
      perror("Accept failed");
      continue;
    }

    if (clientCount < MAX_CLIENTS) {
      clients[clientCount] = new_fd; 
      pthread_create(&receiveThreads[clientCount], NULL, handleClient, &clients[clientCount]);
      clientCount++;
    } else {
      printf("Too many clients. Connection rejected.\n");
      close(new_fd);
    }
  }
  // Cleanup and close server socket
  close(sockfd);
  return 0;
}

