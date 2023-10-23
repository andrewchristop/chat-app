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

int checkPort(int portnum){
  if (portnum <= 1025){
    return(0);
  }else{
    return(1);
  }
}

void serverMenu(void){
  int portnum = 0;
  char response = 'a';
  int ctl = 0;

  do {
    printf("\nPlease enter a port number: ");
    scanf("%d", &portnum);
    ctl = checkPort(portnum);

    if (ctl == 0){
      int control = 0;
      
      do{
        printf("\nPort numbers below 1025 are reserved. Make sure you have super-user privileges!!");
        printf("ARe you sure you want to continue (y/n): ");
        scanf(" %c", &response);

        if (response == 'y' || response == 'Y'){
          ctl = 1;
          control = 1;
        }else if (response == 'n' || response == 'N'){
          ctl = 0;
          control = 1;
        }else{
          printf("\nInvalid input! What is wrong with you :(\n");
          control = 0;
        }
      }while(!control);
    }

  }while(!ctl);

  printf("\nLaunching server instance...\n");
  server(portnum);
}
