#include <stdio.h>
#include <stdlib.h>
#include "server_library.h"

int main(int argc, char** argv) {
  printf("Running program ... \n");
  pant_size ps = calculate_size(25);
  static char* sizes[] = {"Small", "Medium", "Large", "Unknown" }; 
  printf("Pant size is %s\n", sizes[ps]);
  exit(0);
}
