#include <stdlib.h>
#include <stdio.h>
#include "list.h"

struct Node{
  Coor * data;
  Node * next;
  Node * prev;
};

struct List{
  int size;
  Node * head;
  Node * tail;
};

List * newList(){
  static List * l;

  l = malloc(sizeof(List));
  //TODO: if(l==NULL){} //por si no tiene memoria
  l->size=0;
  return l;
}

void deleteList(List * l){
  Node * n;

  for(n = l->head; n!=NULL; n=n->next){
    free(n->data);
    free(n);
  }
  free(l);
}

char isEmpty(List * l){return l->size==0;}
int size(List * l){return l->size;}
Coor * first(List * l){return l->head->data;}
Coor * last(List * l){return l->tail->data;}

Node * newNode(Coor * c){
  static Node * n;

  n = malloc(sizeof(Node));
  n->next=NULL;
  n->prev=NULL;

  n->data = malloc(sizeof(Coor));
  *(n->data) = *c;//copio la coordenada c entera en el nuevo espacio de memoria del heap

  return n;
}

void addLeft(List * l, Coor * c){
  Node * n = newNode(c);
  switch (l->size) {
    case 0:
      l->head=n;
      l->tail=n;
      break;
    default:
      n->next=l->head;
      l->head->prev=n;
      l->head=n;
  }
  l->size++;
}
void addRight(List * l, Coor * c){
  Node * n = newNode(c);
  switch (l->size) {
    case 0:
      l->head=n;
      l->tail=n;
      break;
    default:
      n->prev=l->tail;
      l->tail->next=n;
      l->tail=n;
  }
  l->size++;
}

void debugPrintList(List * l){
  Node * n;

  printf("NULL<->");
  for(n = l->head; n!=NULL; n=n->next){
    printf(" %d <->",n->data->x);
  }
  printf("NULL\n");
}

Coor * searchXY(List * l, int x, int y){
  Node * n;

  for(n = l->head; n!=NULL; n=n->next){
  }

}
/*
Coor * searchTag(List * l, char * tag[]){


}

void erase(List * l, Coor * c){


}
*/
