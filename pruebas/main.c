#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>



int parseint(char * input){
  char * rest = input;
  int n =strtol(rest,&rest,10);

  if(strlen(rest)>0 || n<0){//strtol hasnt finished parsing or n is negative
    fprintf(stderr, "'%s' %s\n", input, PARSEINT_ERROR);
    exit(EXIT_FAILURE);
  }
  return n;
}

int main(int argc, char *argv[])
{

	exit(EXIT_SUCCESS);
}
