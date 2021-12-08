#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"

int main(){
  while (1){
    char comand[100];
    printf("$ ");
    scanf(" %99[^\n]", comando);
    if(!strcmp("exit", comando)){
      break;
    }

    pid_t pid = fork();
    if(!pid){
      execute(comando);
      break;
    }else{
      wait(NULL);
    }
  }
  return 0;
}
