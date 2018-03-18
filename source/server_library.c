#include <stdlib.h>
#include "server_library.h"

int my_div(int x, int y)
{
    if (y==0) exit(2);
    return x/y;
}

pant_size calculate_size(int waist_size) {
    if (waist_size >= 10 && waist_size <= 20) {
      return SMALL;
    }

    if (waist_size >= 21 && waist_size <= 30) {
      return MEDIUM;
    }
    
    if (waist_size >= 31  && waist_size < 40) {
      return LARGE;
    }

    return UNKNOWN;
}
