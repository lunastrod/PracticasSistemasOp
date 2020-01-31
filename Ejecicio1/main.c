#include <stdlib.h>
#include <stdio.h>
#include "list.h"

int
main(int argc, char *argv[])
{
  Coor c = {10,11};
  c.tag="hola";
  printf("%s :(%d, %d)\n",c.tag,c.x,c.y);
  exit(EXIT_SUCCESS);
}
