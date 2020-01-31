#include <stdlib.h>
#include <stdio.h>
#include "list.h"

int
main(int argc, char *argv[])
{
  Coor c = {10,11};
  printf("(%d, %d)\n",c.x,c.y);
  exit(EXIT_SUCCESS);
}
