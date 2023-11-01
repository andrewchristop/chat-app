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

#define BACKLOG 10
#define MAXDATASIZE 1024

int server(int);
void *receive(void *);
void *sendMessage(void *);
