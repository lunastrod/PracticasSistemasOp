#include <stdlib.h>
#include <stdio.h>
#include "list.h"
/*
int
main(int argc, char *argv[])
{
  Coor c = {10,11};
  c.tag[0]='h';
  c.tag[1]='o';
  c.tag[2]='l';
  c.tag[3]='a';
  printf("%s:(%d, %d)\n",c.tag,c.x,c.y);
  exit(EXIT_SUCCESS);
}
*/

int
main(int argc, char *argv[])
{
  Coor c={0,0,"hola"};
  List * l;
  l=newList();
  addRight(l,&c);
  c.x=1;
  c.tag[0]='a';
  addRight(l,&c);
  debugPrintList(l);

  Coor pff={0,0,"aola"};
  erase(l,searchTag(l,&pff.tag));
  debugPrintList(l);

  deleteList(l);
  exit(EXIT_SUCCESS);
}
