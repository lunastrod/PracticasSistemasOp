#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

const char USAGE_ERROR[] = "usage: pinger secs dest [ dest ... ]";
const char PARSEINT_ERROR[] = "is not a natural value";
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

int exec_ping(const char * dest){
  int pid=fork();
  switch(pid){
    case 0:
      execl("/bin/ping","ping","-q",dest,NULL);
      fprintf(stderr, "%s\n", EXEC_ERROR);
      exit(EXIT_FAILURE);
    case -1:
      fprintf(stderr, "%s\n", FORK_ERROR);
      exit(EXIT_FAILURE);
  }
  return pid;
}

int main(int argc, char * argv[]){
  int n;
  int pids[256];
  int i;
  if(argc<=2){
    fprintf(stderr, "%s\n", USAGE_ERROR);
    exit(EXIT_FAILURE);
  }
  n = parseint(argv[1]);//calls argverror() if not parsable
  for(i=2; i<argc; i++){
    pids[i-2]=exec_ping(argv[i]);
  }
  exit(EXIT_SUCCESS);
}
