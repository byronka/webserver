#include <stdio.h>
#include <stdlib.h>
#include "server_library.h"

int main(int argc, char** argv) {
  printf("Running program ... \n");
  char* waist_size_string = argv[1];
  int waist_size_int = (int)strtol(waist_size_string, NULL, 10);
  pant_size ps = calculate_size(waist_size_int);
  static char* sizes[] = {"Small", "Medium", "Large", "X-large", "Unknown" }; 
  printf("Pant size is %s\n", sizes[ps]);
  exit(0);
}
