#include "../include/server.h"

typedef struct {
  int sock_fd;
} ClientInfo;

<<<<<<< HEAD
void *sendMessage(void *socket){
  int sock_fd = (int)socket;
  char message[1024];
  while(fgets(message, 1024, stdin) != NULL){
    
    printf("You: %s", message);

    if ((send(sock_fd, message, strlen(message), 0) < 0)){
      perror("Send failed");
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
=======
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
>>>>>>> bugfix
}

void *handleClient(void *clientSocket) {
  int clientSock = *((int *)clientSocket);
  char receiveMessage[MAX_MESSAGE_SIZE];
  int bytesRead;

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

