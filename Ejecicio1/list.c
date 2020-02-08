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

Coor * newcoor(int x, int y, char * tag){
  static Coor * c;
  c = malloc(sizeof(Coor));
  c->x=x;
  c->y=y;
  snprintf(c->tag,tagSize,"%s",tag);
  return c;
}

void deletecoor(Coor * c){
  free(c);
}
void printcoor(Coor * c){
  printf("%s(%d,%d) ",c->tag,c->x,c->y);
}

Node * newnode(Coor * c){
  static Node * n;

  n = malloc(sizeof(Node));
  n->next=NULL;
  n->prev=NULL;
  n->data =c;

  return n;
}
void deletenode(List * l, Node * n){
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
  free(n);
}







List * newlist(){
  static List * l;

  l = malloc(sizeof(List));
  l->size=0;
  return l;
}
void deletelist(List * l){
  Node * n;
  Node * next;

  for(n = l->head; n!=NULL; n=next){
    next=n->next;
    deletecoor(n->data);
    deletenode(l, n);
  }
  free(l);
}
void printlist(List *l){
  Node * n;
  if(isempty(l)){
    printf("*EMPTY*\n");
    return;
  }
  for(n = l->head; n!=NULL; n=n->next){
    printcoor(n->data);
  }
  printf("\n");
}

int isempty(List * l){return l->size==0;}
int size(List * l){return l->size;}
Coor * first(List * l){return l->head->data;}
Coor * last(List * l){return l->tail->data;}

void addstartlist(List * l, Coor * c){
  Node * n = newnode(c);
  if(isempty(l)){
    l->head=n;
    l->tail=n;
  }
  else{
    n->next=l->head;
    l->head->prev=n;
    l->head=n;
  }
  l->size++;
}
void addendlist(List * l, Coor * c){
  Node * n = newnode(c);
  if(isempty(l)){
    l->head=n;
    l->tail=n;
  }
  else{
    n->prev=l->tail;
    l->tail->next=n;
    l->tail=n;
  }
  l->size++;
}

Coor * searchxy(List * l, int x, int y){
  Node * n;

  for(n = l->head; n!=NULL; n=n->next){
    if(n->data->x==x && n->data->y==y)
      return n->data;
  }
  return NULL;
}
Coor * searchtag(List * l, char tag[]){
  Node * n;

  for(n = l->head; n!=NULL; n=n->next){
    if(strcmp(tag,(n->data->tag))==0)//si son iguales
      return n->data;
  }
  return NULL;
}

void erasecoor(List * l, Coor * c){
  Node * n;
  //busco el nodo en el que está c
  for(n = l->head; n!=NULL; n=n->next){
    if(n->data==c)
      break;//cuando lo encuentres deja de buscar
  }
  //ahora n es el nodo que contiene c
  if(n!=NULL){
    deletecoor(n->data);
    deletenode(l, n);
  }
}







Stack * newstack(){
  static Stack * s;
  s = malloc(sizeof(Stack));
  s->list=newlist();
  return s;
}
void deletestack(Stack * s){
  deletelist(s->list);
  free(s);
}

void printstack(Stack * s){
  printlist(s->list);
}

void push(Stack * s, Coor * c){
  addendlist(s->list,c);
}
Coor * pop(Stack * s){
  Coor * c;
  c=s->list->tail->data;
  deletenode(s->list, s->list->tail);
  return c;
}







Queue * newqueue(){
  static Queue * q;
  q = malloc(sizeof(Queue));
  q->list=newlist();
  return q;
}
void deletequeue(Queue * q){
  deletelist(q->list);
  free(q);
}

void printqueue(Queue * q){
  printlist(q->list);
}

void enqueue(Queue * q, Coor * c){
  addendlist(q->list,c);
}
Coor * dequeue(Queue * q){
  Coor * c;
  c=q->list->head->data;
  deletenode(q->list, q->list->head);
  return c;
}
