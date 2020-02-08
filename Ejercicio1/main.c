#include <stdlib.h>
#include <stdio.h>
#include "list.h"

enum{
  listSize=10
};

int main(int argc, char *argv[]){
  Coor * c;
  int a;
  List * l = newlist();//creo lista, pila y cola
  Stack * s= newstack();
  Queue * q= newqueue();

  for(a=0; a<=listSize; a++){//las lleno de coordenadas ascendentes
    addendlist(l,newcoor(a,a,""));
    push(s,newcoor(a,a,""));
    enqueue(q,newcoor(a,a,""));
  }
  printf("list:  ");
  printlist(l);
  printf("stack: ");
  printstack(s);
  printf("queue: ");
  printqueue(q);

  for(a=0; a<=listSize; a+=2){//quito los pares de la lista
    erasecoor(l,searchxy(l,a,a));
  }
  printf("\nodds:      ");
  printlist(l);
  printf("reverse:   ");
  for(a=0; a<=listSize; a++){//imprimo en sentido inverso la pila
    c=pop(s);
    printcoor(c);
    deletecoor(c);
  }
  printf("\nascending: ");
  for(a=0; a<=listSize; a++){//imprimo en orden ascendente la cola
    c=dequeue(q);
    printcoor(c);
    deletecoor(c);
  }
  printf("\n\n");

  printf("list:  ");
  printlist(l);
  printf("stack: ");
  printstack(s);
  printf("queue: ");
  printqueue(q);

  deletelist(l);//destruyo la lista, pila y cola
  deletestack(s);
  deletequeue(q);
  exit(EXIT_SUCCESS);
}
