#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>

const char USAGE_ERROR[] =    "execargs secs command [command ...]";
const char PARSEINT_ERROR[] = "is not an integer value";
const char EXEC_ERROR[] =     "command not found";
const char FORK_ERROR[] =     "can't fork";

enum{
  ARG_MAX=256//max number of arguments
};

void argverror() {
  fprintf(stderr, "%s\n", USAGE_ERROR);
  exit(EXIT_FAILURE);
}

void exec_command(char * input){
  //example: exec_command("/bin/echo a a a");
  //will exec "/bin/echo" with 3 args: "a" "a" "a"
  char * rest = input;
  char * command;
  char * args[ARG_MAX];
  int i=1;

  command = strtok_r(rest, " ", &rest);
  args[0]=command;
  //tokens input in args and adds a NULL at the end
  while ((args[i] = strtok_r(rest, " ", &rest))){
    i++;
  }
  args[i]=NULL;
  execv(command,args);
  fprintf(stderr, "'%s' %s\n", command, EXEC_ERROR);
  argverror();
}

int parseint(char * input){
  char * rest = input;
  int n =strtol(rest,&rest,10);

  if(strlen(rest)>0){//strtol hasnt finished parsing
    fprintf(stderr, "'%s' %s\n", input, PARSEINT_ERROR);
    argverror();
  }
  return n;
}

int main(int argc, char * argv[]){
  int i;
  int secs;
  if(argc<=2){
    argverror();
  }
  secs = parseint(argv[1]);//calls argverror() if not parsable

  for(i=2; i<argc; i++){
    switch(fork()){
      case 0:
        exec_command(argv[i]);//calls argverror() if error
      case -1:
        fprintf(stderr, "%s\n", FORK_ERROR);
        argverror();
    }
    sleep(secs);
  }
  exit(EXIT_SUCCESS);
}
