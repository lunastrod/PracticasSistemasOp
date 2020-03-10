#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

const char USAGE_ERROR[] = "usage: copybytes source dest [bytes]";
const char PARSEINT_ERROR[] = "is not a valid natural number";
const char EXEC_ERROR[] =     "command not found";
const char FORK_ERROR[] =     "can't fork";

int parseint(char * input){
  char * rest = input;
  int n =strtol(rest,&rest,10);

  if(strlen(rest)>0 || n<0){//strtol hasnt finished parsing or n is negative
    fprintf(stderr, "'%s' %s\n", input, PARSEINT_ERROR);
    exit(EXIT_FAILURE);
  }
  return n;
}

int main(int argc, char * argv[]){
  if(argc<3 || argc>4){
    fprintf(stderr, "%s\n", USAGE_ERROR);
    exit(EXIT_FAILURE);
  }
  

  exit(EXIT_SUCCESS);
}
