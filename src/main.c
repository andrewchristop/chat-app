#include "../include/main.h"
#include "server.c"

int main(void){
  int choice = 0;
  //int portnum = 0;
 
 do{
    choice = showMenu(choice);

    if (choice != 1 && choice != 2){
      printf("\nInput entered is invalid! Please try again!!\n");
    }

    if (choice == 1){
      serverMenu(); 
    }

  }while (choice != 1 && choice != 2);
  
  return(0);
}

int showMenu(int choice){
  printf("\nWelcome to the Chat-App!\n");
  printf("Select one of two options to execute!\n");
  printf("1. Start a server instance\n");
  printf("2. Start a client instance\n");
  printf("Input: ");
  scanf("%d", &choice);
  return(choice);
}

void serverMenu(void){
  int portnum = 0;
  printf("\nPlease enter a port number: ");
  scanf("%d", &portnum);
  printf("\nLaunching server instance...\n");
  server(portnum);
}
