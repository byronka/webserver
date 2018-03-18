#include <stdlib.h>
#include "server_library.h"

int 
my_div(int x, int y)
{
        if (y == 0)
                exit(2);
        return x / y;
}

pant_size 
calculate_size(int waist_size)
{
        if (waist_size >= 25 && waist_size < 30) {
                return SMALL;
        }
        if (waist_size >= 30 && waist_size < 36) {
                return MEDIUM;
        }
        if (waist_size >= 36 && waist_size < 44) {
                return LARGE;
        }
        if (waist_size >= 44 && waist_size <= 55) {
                return XLARGE;
        }
        return UNKNOWN;
}
