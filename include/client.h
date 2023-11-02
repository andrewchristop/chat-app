#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define TERM "!q"

int client(char *, int);
void *sendMessageClient(void *);
void *receiveMessageClient(void *);
