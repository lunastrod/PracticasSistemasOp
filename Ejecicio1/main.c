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
  Coor c;
  List * l;
  l=newList();
  c.y=0;
  c.x=1;
  addRight(l,&c);
  c.x=2;
  addRight(l,&c);
  c.x=3;
  addLeft(l,&c);
  debugPrintList(l);
  erase(l,searchXY(l, 2,0));
  debugPrintList(l);
  erase(l,searchXY(l, 3,0));
  debugPrintList(l);
  erase(l,searchXY(l, 1,0));
  debugPrintList(l);

  deleteList(l);
  exit(EXIT_SUCCESS);
}
