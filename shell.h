#ifndef _MAIN_
#define _MAIN_

#include <stdio.h>
#include <stdlib.h>

int countBySpace(char comando[]);
int countPipeOcurrence(char comando[]);
int countFluxOcurrence(char comando[]);
void split(char comando[], char *slicedCommand[], char c[]);
void finalCommandTokens(char *finalTokens[], char comando[]);
void executeBasicCommand(char *tokens[], char comando[]);
void executeCommandWithPipes(char *args1[], char *args2[]);
void executeOutputFileCommand(char args[], char fileName[]);
void execute(char comando[]);

#endif
