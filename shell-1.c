#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "shell.h"

/***
 * Finds a pipe in the command
 */int countPipeOcurrence(char comando[]){
  if(strchr(comando, '|')!=NULL){
    return 1;
  }
  return 0;
}
/***
 * Finds '>' in the command
 */int countFluxOcurrence(char comando[]){
  if(strchr(comando, '>')!=NULL){
    return 1;
  }
  return 0;
}

/***
 * Separates the command when it finds 
 * the pipe o the '>'
 */void split(char comando[], char *slicedCommand[], char c[]){
   char *puntero;
   int i = 0;
   puntero = strtok(comando, c);

   while(puntero != NULL){
     slicedCommand[i] = puntero;
     puntero = strtok(NULL, c);
     i++;
   }
}

/***
 * Llena cada posicion del arreglo finalTokens con cada token presente en el comando
 */void finalCommandTokens(char *finalTokens[], char comando[]){
   char *puntero;
   int i = 0;
   puntero = strtok(comando, " ");

   while(puntero != NULL){
     finalTokens[i] = puntero;
     puntero = strtok(NULL, " ");
     i++;
   }
   finalTokens[i]=NULL;
}

//---- Ejecucion de comando----//
void executeBasicCommand(char *tokens[], char comando[]){
  execvp(tokens[0], tokens);
  printf("%s: No se encontró la orden\n", comando);
}

void executeCommandWithPipes(char *args1[], char *args2[]){
  pid_t pid1, pid2;
  int pipefd[2], status1, status2;

  pipe(pipefd);
  pid1 = fork();

  if(pid1 == 0){
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[0]);
    execvp(args1[0], args1);
    printf("No se encontró la orden\n");
  }

  pid2 = fork();
  if(pid2 == 0){
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[1]);
    execvp(args2[0], args2);
    printf("No se encontró la orden\n");
  }

  close(pipefd[0]);
  close(pipefd[1]);
  wait(NULL);
}

/***
 * Redirecciona salida estndar a un archiv
 */ void executeOutputFileCommand(char args[], char fileName[]){
   close(STDOUT_FILENO);
   open(fileName, O_EXCL|O_CREAT|O_WRONLY, S_IRWXU);
   execute(args);
}

//----Funion de control---//

// Recibe el comando dependiendo del tipo
// 1- Sin pipes sin flujo
// 2- Con pipes sin flujo
// 3- Con flujo y pipes

void execute(char comando[]){
  int commandSize = strlen(comando);
  int cantPipes = countPipeOcurrence(comando);
  int cantFluxCommand = countFluxOcurrence(comando);
  char copy[commandSize];
  strcpy(copy, comando);

  if(cantPipes == 0 && cantFluxCommand == 0){
    int cantTokens = countBySpace(copy);
    char *finalTokens[cantTokens+1];
    finalCommandTokens(finalTokens, comando);
    executeBasicCommand(finalTokens, comando);
  } else if(cantPipes != 0 && cantFluxCommand == 0){
    char *slicedCommand[2];
    split(copy, slicedCommand, "|");

    //spearar tokens del 1er arreglo
    char cpy1[strlen(slicedCommand[0])];
    strcpy(copy1, slicedCommand[0]);
    int sizeSecondArray = countBySpace(copy2);
    char *tokensSecondArray[sizeSecondArray+1];
    finalCommandTokens(tokensSecondArray, slicedCommand[1]);

    //separar tokens del 2ndo arreglo
    executeCommandWithPipes(tokensFirstArray, tokensSecondArray);
  } else if(cantFluxCommand == 1){
    char *slicedCommand[2];
    split(copy, slicedCommand, ">");
    slicedCommand[1] = strtok(slicedCommand[1], " ");
    executeOutputFileCommand(slicedCommand[0], slicedCommand[1]);
  }
}
