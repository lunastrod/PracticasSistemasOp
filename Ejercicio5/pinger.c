#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

enum{
  INT_MAX_DIGITS=20,
  MAX_ARGS=512
};

const char USAGE_ERROR[] = "usage: pinger secs dest [ dest ... ]";
const char PARSEINT_ERROR[] = "is not a valid number";
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

int exec_ping(int n, const char * dest){
  char * pinginterval;
  int pid=fork();
  switch(pid){
    case 0:
      pinginterval = malloc(INT_MAX_DIGITS*sizeof(char));
      snprintf(pinginterval,INT_MAX_DIGITS,"%d",n);
      execl("/bin/ping","ping","-i",pinginterval,"-c","2",dest,NULL);
      fprintf(stderr, "%s\n", EXEC_ERROR);
      exit(EXIT_FAILURE);
    case -1:
      fprintf(stderr, "%s\n", FORK_ERROR);
      exit(EXIT_FAILURE);
  }
  return pid;
}

int main(int argc, char * argv[]){
  if(argc<=2||argc>MAX_ARGS+2){
    fprintf(stderr, "%s\n", USAGE_ERROR);
    exit(EXIT_FAILURE);
  }
  int n = parseint(argv[1]);
  int pids[MAX_ARGS];
  int i;
  for(i=0; i<argc-2; i++){
    pids[i]=exec_ping(n,argv[i+2]);
  }
  int childstatus;
  int exitstatus=EXIT_SUCCESS;
  for(i=0; i<argc-2; i++){
    waitpid(pids[i],&childstatus,0);
    if(WEXITSTATUS(childstatus)!=EXIT_SUCCESS){
      fprintf(stderr, "error: no se puede acceder a '%s'\n", argv[i+2]);
      exitstatus=EXIT_FAILURE;
    }
  }
  exit(exitstatus);
}
