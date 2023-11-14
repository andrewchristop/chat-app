#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define MAX_MESSAGE_SIZE 1024
#define TERM "!q"

int client(char *, int);
void *sendMessage(void *);
void *receiveMessage(void *);
