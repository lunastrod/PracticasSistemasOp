#include <stdlib.h>
#include <stdio.h>
#include "list.h"

struct Coor{
  int x;
  int y;
  char tag[tagSize];
};

struct Node{
  Coor data;
  Node * next;
  Node * prev;
};

struct List{
  int size;//no estoy seguro de si ponerlo
  Node * head;
  Node * tail;
};


List *
newList(){
  static List * l;
  l = malloc(sizeof(List));
  //TODO: if(l==NULL){} //por si no tiene memoria
  l->size=0;
  return l;
}

void
deleteList(List * l){
  free(l);
}
