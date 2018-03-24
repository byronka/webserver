#include <stdio.h>
#include <stdlib.h>
#include "business_library.h"

int
main (int argc, char **argv)
{
  int size_input = strtol(argv[1], NULL, 10);
  static const char* pant_sizes[] = {"SMALL", "MEDIUM", "LARGE", "X-LARGE", "UNKNOWN"};
  
  int size_output = calculate_pant_size(size_input);
  printf("%s\n", pant_sizes[size_output]);
  exit (0);
}
