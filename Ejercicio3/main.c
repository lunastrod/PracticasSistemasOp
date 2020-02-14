#include <stdlib.h>
#include <stdio.h>

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

void exiterror()

int main(int argc, char *argv[]){
  if(argc<=2){
    fprintf(stderr, "execargs secs command [command ...]\n");
    exit(EXIT_FAILURE);
  }
  char lastchar=malloc(argv[1])
  int i=strtol(argv[1],,10);
  printf("%s")



}
