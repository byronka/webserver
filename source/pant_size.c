#include <stdio.h>
#include <stdlib.h>
#include "business_library.h"

int
main (int argc, char **argv)
{
  int size = strtol(argv[1], NULL, 10);
  printf("%d\n", calculate_size(size));
  exit (0);
}
