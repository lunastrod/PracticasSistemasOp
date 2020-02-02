#include <stdlib.h>
#include <stdio.h>
#include "list.h"

enum{
  listSize=6
};

int main(int argc, char *argv[]){
  Coor c={0,0,""};
  int a;
  List * l = newList();
  Stack * s= newStack();
  Queue * q= newQueue();

  for(a=0; a<=listSize; a++){
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

  for(a=0; a<=listSize; a+=2){
    erase(l,searchXY(l,a,a));
  }
  printf("\nodds:      ");
  printList(l);
  printf("reverse:   ");
  for(a=0; a<=listSize; a++){
    c=pop(s);
    printf("%s(%d,%d) ",c.tag,c.x,c.y);
  }
  printf("\nascending: ");
  for(a=0; a<=listSize; a++){
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

  deleteList(l);
  deleteStack(s);
  deleteQueue(q);
}
