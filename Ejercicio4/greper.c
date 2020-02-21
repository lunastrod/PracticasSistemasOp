#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


const char USAGE_ERROR[] = "usage: greper regexp path [regexp path ...]";
const char EXEC_ERROR[]  = "exec error: grep command not found";
const char FORK_ERROR[]  = "fork error";

void printresult(int status, const char * regexp, const char * file){
  switch (status) {
    case 0:
      printf("%s matches '%s'\n", file, regexp);
      break;
    case 1://TODO: por la salida de error?
      printf("%s does not match '%s'\n", file, regexp);
      break;
    case 2://TODO: por la salida de error?
      printf("%s: ERROR\n", file);
      break;
  }
}

int exec_grep(const char * regexp, const char * file){
  int pid=fork();
  switch(pid){
    case 0:
      //grep -E(use regexp) -s(supress some stderr) -q(no stdout)
      //TODO: ./greper a[] greper.c saca mensajes de grep (no está mal del todo)
      execl("/bin/grep","grep","-Esq",regexp,file,NULL);
      fprintf(stderr, "%s\n", EXEC_ERROR);
      exit(EXIT_FAILURE);
    case -1:
      fprintf(stderr, "%s\n", FORK_ERROR);
      exit(EXIT_FAILURE);
  }
  return pid;
}

int main(int argc, char * argv[]){
  int i;
  int pids[(argc/2)];//the pids of all the future grep commands
  int status;
  int exitstatus=EXIT_SUCCESS;
  if(argc<3 || argc%2==0){//argc can be:{3,5,7,9...}
    fprintf(stderr, "%s\n", USAGE_ERROR);
    exit(EXIT_FAILURE);
  }
  for(i=0;i<argc/2;i++){
    pids[i]=exec_grep(argv[i*2+1],argv[i*2+2]);
  }
  for(i=0;i<argc/2;i++){
    waitpid(pids[i],&status,0);
    printresult(WEXITSTATUS(status),argv[i*2+1],argv[i*2+2]);
    if(WEXITSTATUS(status)!=EXIT_SUCCESS){
      exitstatus=EXIT_FAILURE;
    }
  }
  exit(exitstatus);
}
