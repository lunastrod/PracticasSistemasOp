#include <stdlib.h>
#include <stdio.h>
#include "list.h"

enum{
  listSize=10
};
///*
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
//*/
/*
//main para comprobar los posibles errores
int main(int argc, char *argv[]){
  List * l = newlist();
  Stack * s= newstack();
  Queue * q= newqueue();
  Coor * c = newcoor(12,37,"test");

  //printcoor(NULL);//stderr: can't print a NULL pointer to coor

  //firstcoor(l);//stderr: empty list, no first element
  //lastcoor(l);//stderr: empty list, no last element

  //no dan error, es tu problema si metes null en un nodo
  //addstartlist(l, NULL);
  //addendlist(l, NULL);
  //push(s, NULL);
  //enqueue(q, NULL);

  //searchxy(l,1,1);//stderr: no coor in list with members (x,y)=(1,1)
  //searchtag(l,"noexiste");//stderr: no coor in list with members tag=noexiste
  //erasecoor(l,searchtag(l,"noexiste"));//stderr: no coor in list with adress= (nil)

  //pop(s);//stderr: empty stack, can't pop
  //dequeue(q);//stderr: empty queue, can't dequeue
}
*/
