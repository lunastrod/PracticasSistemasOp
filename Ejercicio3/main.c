#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/*
Escriba un programa en C llamado execargs que ejecute todos los comandos que se le pasen como argumentos.
El primer argumento debe ser el número de segundos que hay que esperar entre la ejecución de cada uno.
El resto de argumentos que se le pasan al programa serán rutas de ejecutables,
opcionalmente con argumentos para ese comando si la string contiene espacios.
Se considerará error si el programa no recibe al menos dos argumentos o el primero no es un entero.
En caso de error, se debe avisar como corresponda y acabar la ejecución (no se deben ejecutar los programas restantes).
Para esperar un número de segundos, convertir de string a entero y partir una string en trozos usando un separador, se recomienda la lectura de:

man 3 sleep
man 3 atoi
man 3 strtol
man 3 strtok_r

Un ejemplo de ejecución es el siguiente:

$> ./execargs 2 '/bin/echo hola' '/bin/echo adios'
hola
adios
$> ./execargs
usage: execargs secs command [command ...]
$> ls
execargs
execargs.c
execargs.o
$> ./execargs 1 /bin/ls 'echo ya esta'
execargs
execargs.c
execargs.o
ya esta
$>
*/

enum{
  FALSE,
  TRUE,
  ARG_MAX=255//max number of arguments
};

void argverror() {
  fprintf(stderr, "execargs secs command [command ...]\n");
  exit(EXIT_FAILURE);
}

int exec_command(char * input){
  //example: exec_command("/bin/echo a a a");
  //will exec "/bin/echo" with 3 args: "a" "a" "a"
  char * command;
  char * args[ARG_MAX];
  char * rest = input;
  int i=1;

  command = strtok_r(rest, " ", &rest);
  args[0]=command;

  //tokenizo input en args y añado un NULL al final de args
  while ((args[i] = strtok_r(rest, " ", &rest))){
    //printf("%s, i=%d\n", args[i],i);
    i++;
  }
  args[i]=NULL;
  return execv(command,args);
}

int parseint(char * str){
  char ** not_parsable_substring=malloc((strlen(str)+1)*sizeof(char));
  int n=strtol(str,not_parsable_substring,10);
  if(strlen(*not_parsable_substring)>0){//strtol hasnt finished parsing
    //str is not parsable to int
    fprintf(stderr, "not_parsable_substring=%s\n", *not_parsable_substring);
    free(not_parsable_substring);
    argverror();
  }
  free(not_parsable_substring);
  //printf("n=%d\n",n);
  return n;
}

int main(int argc, char * argv[]){
  int i;
  int secs;
  if(argc<=2){
    argverror();
  }
  secs = parseint(argv[1]);//might call argverror() if not parsable

  for(i=2; i<argc; i++){
    if(fork() == 0){
      exec_command(argv[i]);
      argverror();//TODO: si el hijo llega aquí, matar al padre también
    }
    sleep(secs);
  }
  exit(EXIT_SUCCESS);
}
