#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX_CLIENTS 10
#define MAX_MESSAGE_SIZE 1024

int server(int);
void *handleClient(void *);
void sendMessages(char *, int);
