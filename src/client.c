#include "../include/client.h"
#include "../include/crypto.h"

char message[MAX_MESSAGE_SIZE];
char decrypt[MAX_MESSAGE_SIZE];

void *receiveMessage(void *socket) {
  int sock_fd = *((int *)socket);
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
      //decryptMessage(message, decrypt);
      message[bytesRead] = '\0';
      fputs(message, stdout);
    }
  }
  return NULL;
}


int client(char *host, int portnum, char uname[50]) {
  int sockfd;
  int len;
  int count = 0;
  char send_msg[MAX_MESSAGE_SIZE];
  char cipher[MAX_MESSAGE_SIZE];
  struct sockaddr_in serverAddr;
  pthread_t receiveThread;

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
  }else{
    write(sockfd, uname, strlen(uname));
    pthread_create(&receiveThread, NULL, (void *)receiveMessage, &sockfd);
    while(fgets(message,MAX_MESSAGE_SIZE,stdin) > 0){
      if (count == 0){
        count++;
      }else{
        strcpy(send_msg, uname);
        strcat(send_msg, ":");
        strcat(send_msg, message);
        //processBlocks(send_msg, cipher);
        len = write(send_msg, cipher, strlen(send_msg));
        //fflush(stdout);
      }
      if (len < 0){
        printf("\n message not sent \n");
      }
    }
    pthread_join(receiveThread, NULL);
    // Cleanup and close client socket
    close(sockfd);
  }
  
  return 0;
}

