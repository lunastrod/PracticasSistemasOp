#include <stdlib.h>
#include <stdio.h>
#include "list.h"

List *
newList(){
  static List * l;
  l = malloc(sizeof(List));
  //TODO: if(l==NULL){} //por si no tiene memoria
  l->size=0;
  return l;
}

void
delete(List * l){
  free(l);
}
