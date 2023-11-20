#include "../include/server.h"
typedef struct {
  int sock_fd;
  char uname[50];
} ClientInfo;

int clientCount = 0;
pthread_mutex_t mutex;
ClientInfo clients[MAX_CLIENTS];

void sendMessages(char *msg, int curr) {
  int i;
  pthread_mutex_lock(&mutex);
  for (i = 0; i < clientCount; i++) {
    if (clients[i].sock_fd != curr) {
      if ((send(clients[i].sock_fd, msg, strlen(msg), 0) < 0)) {
        printf("Sending failed \n");
        continue;
      }
    }
  }
  pthread_mutex_unlock(&mutex);
}

void *handleClient(void *clientSocket) {
  int clientSock = *((int *)clientSocket);
  char receiveMessage[MAX_MESSAGE_SIZE];
  int bytesRead;
  char unameLoc[50];
  
  bytesRead = recv(clientSock, unameLoc, sizeof(unameLoc), 0);

  for(int i = 0; i < clientCount; i++){
    if(clients[i].uname == unameLoc){
      printf("No two users can have the same username. Please pick a new one\n");
      close(clientSock);
    }
  }

 strcpy(clients[clientCount].uname, unameLoc); 
  while (1) {
    bytesRead = recv(clientSock, receiveMessage, MAX_MESSAGE_SIZE, 0);
    if (bytesRead <= 0) {
      // Handle client disconnect or error
      close(clientSock);
      pthread_exit(NULL);
    } else {
      // Process the received message (you can modify this part)
      receiveMessage[bytesRead] = '\0';
      sendMessages(receiveMessage, clientSock);
    }
  }
  return NULL;
}

int server(int portnum) {
  int sockfd, new_fd;
  struct sockaddr_in serverAddr, clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);

  pthread_t receiveThread;

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

  while (1) {
    new_fd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (new_fd < 0) {
      perror("Accept failed");
      continue;
    }

    if (clientCount < MAX_CLIENTS) {
      pthread_mutex_lock(&mutex);
      clients[clientCount].sock_fd = new_fd;
      clientCount++;
      pthread_create(&receiveThread, NULL, (void *)handleClient, &new_fd);
      pthread_mutex_unlock(&mutex);
    } else {
      printf("Too many clients. Connection rejected.\n");
      close(new_fd);
    }
  }
  // Cleanup and close server socket
  close(sockfd);
  return 0;
}

