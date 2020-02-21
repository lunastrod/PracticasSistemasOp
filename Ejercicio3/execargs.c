#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>

const char USAGE_ERROR[] =    "execargs secs command [command ...]";
const char PARSEINT_ERROR[] = "is not a natural value";
const char EXEC_ERROR[] =     "command not found";
const char FORK_ERROR[] =     "can't fork";

enum{
  ARG_MAX=256//max number of arguments
};

void argverror() {
  fprintf(stderr, "%s\n", USAGE_ERROR);
  exit(EXIT_FAILURE);
}

int parseint(char * input){
  char * rest = input;
  int n =strtol(rest,&rest,10);

  if(strlen(rest)>0 || n<0){//strtol hasnt finished parsing or n is negative
    fprintf(stderr, "'%s' %s\n", input, PARSEINT_ERROR);
    argverror();
  }
  return n;
}

void exec_command(char ** input){
  //example: exec_command({"/bin/echo", "a", "a", "a"});
  //will exec "/bin/echo" with 3 args: "a" "a" "a"
  switch(fork()){
    case 0:
      execv(input[0],input);
      fprintf(stderr, "'%s' %s\n", input[0], EXEC_ERROR);
      argverror();
    case -1:
      fprintf(stderr, "%s\n", FORK_ERROR);
      argverror();
  }
}

void execute(char * input){
  //tokens input and calls exec_command()
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
  exec_command(args);
}

int main(int argc, char * argv[]){
  int i;
  int secs;
  if(argc<=2){
    argverror();
  }
  secs = parseint(argv[1]);//calls argverror() if not parsable

  for(i=2; i<argc; i++){
    execute(argv[i]);
    sleep(secs);
  }
  exit(EXIT_SUCCESS);
}
