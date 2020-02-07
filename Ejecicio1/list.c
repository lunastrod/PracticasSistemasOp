#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include <string.h>

typedef struct Node Node;
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

struct Stack{
  List * list;
};

struct Queue{
  List * list;
};

Node * newNode(Coor c){
  static Node * n;

  n = malloc(sizeof(Node));
  n->next=NULL;
  n->prev=NULL;

  n->data = malloc(sizeof(Coor));
  *(n->data) = c;//copio la coordenada c en el nuevo espacio de memoria del heap

  return n;
}
void deleteNode(List * l, Node * n){
  //me aseguro de que la lista sigue conectada antes de borrar un nodo
  if(n!=l->head && n!=l->tail){//eliminar un nodo central
    n->prev->next=n->next;
    n->next->prev=n->prev;
  }
  else if( l->size > 1){
    if(n==l->head){//eliminar la cabeza
      l->head=n->next;
      n->next->prev=NULL;
    }
    if(n==l->tail){//eliminar la cola
      l->tail=n->prev;
      n->prev->next=NULL;
    }
  }
  else{//eliminar el unico elemento de la lista
    l->head=NULL;
    l->tail=NULL;
  }
  l->size--;
  free(n->data);
  free(n);
}







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
    deleteNode(l, n);//TODO: estoy haciendo un free y despues accediendo a n en n=n->next
  }
  free(l);
}
void printList(List *l){
  Node * n;

  for(n = l->head; n!=NULL; n=n->next){
    printf("%s(%d,%d) ",n->data->tag,n->data->x,n->data->y);
  }
  printf("\n");
}

int isEmpty(List * l){return l->size==0;}
int size(List * l){return l->size;}
Coor * first(List * l){return l->head->data;}
Coor * last(List * l){return l->tail->data;}

void addStart(List * l, Coor c){
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
void addEnd(List * l, Coor c){
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

Coor * searchXY(List * l, int x, int y){
  Node * n;

  for(n = l->head; n!=NULL; n=n->next){
    //fprintf(stderr, "%d-%d, %d-%d\n", n->data->y,x,n->data->x,y);
    if(n->data->x==x && n->data->y==y)
      return n->data;
  }
  return NULL;
}
Coor * searchTag(List * l, char tag[]){
  Node * n;

  for(n = l->head; n!=NULL; n=n->next){
    if(strcmp(tag,(n->data->tag))==0)//si son iguales
      return n->data;
  }
  return NULL;
}

void erase(List * l, Coor * c){
  Node * n;
  //busco el nodo en el que está c
  for(n = l->head; n!=NULL; n=n->next){
    if(n->data==c)
      break;//cuando lo encuentres deja de buscar
  }
  //ahora n es el nodo que contiene c
  if(n!=NULL) deleteNode(l, n);
}







Stack * newStack(){
  static Stack * s;
  s = malloc(sizeof(Stack));
  s->list=newList();
  return s;
}
void deleteStack(Stack * s){
  deleteList(s->list);
  free(s);
}

void printStack(Stack * s){
  printList(s->list);
}

void push(Stack * s, Coor c){
  addEnd(s->list,c);
}
Coor pop(Stack * s){
  Coor c;
  c=*s->list->tail->data;
  deleteNode(s->list, s->list->tail);
  return c;
}







Queue * newQueue(){
  static Queue * q;
  q = malloc(sizeof(Queue));
  q->list=newList();
  return q;
}
void deleteQueue(Queue * q){
  deleteList(q->list);
  free(q);
}

void printQueue(Queue * q){
  printList(q->list);
}

void enqueue(Queue * q, Coor c){
  addEnd(q->list,c);
}
Coor dequeue(Queue * q){
  Coor c;
  c=*q->list->head->data;
  deleteNode(q->list, q->list->head);
  return c;
}
