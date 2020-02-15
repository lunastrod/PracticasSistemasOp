#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <string.h>

/*
TODO: rutas??? El resto de argumentos que se le pasan al programa serán rutas de ejecutables,

TODO: no sería /bin/echo???
$> ./execargs 1 /bin/ls 'echo ya esta'
execargs
execargs.c
execargs.o
ya esta
*/

enum{
  ARG_MAX=255//max number of arguments
};

void argverror() {
  fprintf(stderr, "execargs secs command [command ...]\n");
  exit(EXIT_FAILURE);
}

int exec_command(char * input){
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
    //printf("%s, i=%d\n", args[i],i);
    i++;
  }
  args[i]=NULL;
  return execv(command,args);
}

int parseint(char * input){
  char * rest = input;
  int n =strtol(rest,&rest,10);

  if(strlen(rest)>0){//strtol hasnt finished parsing
    //fprintf(stderr, "not_parsable_substring=%s\n", rest);
    argverror();
  }
  return n;
}

int main(int argc, char * argv[]){
  int i;
  int secs;
  int exit_code;
  if(argc<=2){
    argverror();
  }
  secs = parseint(argv[1]);//might call argverror() if not parsable

  for(i=2; i<argc; i++){
    if(fork() == 0){
      exec_command(argv[i]);
      argverror();//TODO: si el hijo llega aquí, matar al padre también
    }
    if(wait(&exit_code)!=-1 && WEXITSTATUS(exit_code)==EXIT_FAILURE){
      exit(EXIT_FAILURE);
    }
    sleep(secs);
  }
  exit(EXIT_SUCCESS);
}
