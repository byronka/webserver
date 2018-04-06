#include <stdlib.h>

/**
 * wrapping exit so it doesn't actually exit while debugging and
 * testing.
 */
void do_exit (int error_number)
{
  exit (error_number);
}
