#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
  int i;
  for(i=0; i<argc; i++){//de momento imprimo los argumentos
    printf("%s\n",argv[i]);
  }
}
