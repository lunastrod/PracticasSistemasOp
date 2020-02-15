#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
  for(int i=0;i<5;i++){
    printf("padre crea un hijo\n");
    if(fork() == 0){
        printf("exit hijo\n");
        exit(0);
    }
  }
  printf("exit padre\n");
  exit(0);
}
