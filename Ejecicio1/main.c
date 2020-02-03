#include <stdlib.h>
#include <stdio.h>
#include "list.h"

enum{
  listSize=10
};

int main(int argc, char *argv[]){
  Coor c={0,0,""};
  int a;
  List * l = newList();//creo lista, pila y cola
  Stack * s= newStack();
  Queue * q= newQueue();

  for(a=0; a<=listSize; a++){//las lleno de coordenadas ascendentes
    c.x=a;
    c.y=a;
    addRight(l,c);
    push(s,c);
    enqueue(q,c);
  }
  printf("list:  ");
  printList(l);
  printf("stack: ");
  printStack(s);
  printf("queue: ");
  printQueue(q);

  for(a=0; a<=listSize; a+=2){//quito los impares de la lista
    erase(l,searchXY(l,a,a));
  }
  printf("\nodds:      ");
  printList(l);
  printf("reverse:   ");
  for(a=0; a<=listSize; a++){//imprimo en sentido inverso la pila
    c=pop(s);
    printf("%s(%d,%d) ",c.tag,c.x,c.y);
  }
  printf("\nascending: ");
  for(a=0; a<=listSize; a++){//imprimo en orden ascendente la cola
    c=dequeue(q);
    printf("%s(%d,%d) ",c.tag,c.x,c.y);
  }
  printf("\n\n");

  printf("list:  ");
  printList(l);
  printf("stack: ");
  printStack(s);
  printf("queue: ");
  printQueue(q);

  deleteList(l);//destruyo la lista, pila y cola
  deleteStack(s);
  deleteQueue(q);
  
  exit(EXIT_SUCCESS);
}
