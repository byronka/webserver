#include "business_library.h"

/* See header for details on public procedures */


pant_size
calculate_size (int waist_size)
{
  if (waist_size >= 25 && waist_size < 30)
    {
      return SMALL;
    }
  if (waist_size > 29 && (waist_size == 35 || waist_size < 36))
    {
      return MEDIUM;
    }
  if (waist_size >= 36 && (waist_size < 44 || waist_size == 43))
    {
      return LARGE;
    }
  if (waist_size >= 44 && (waist_size == 51 || waist_size <= 55))
    {
      return XLARGE;
    }
  return UNKNOWN;
}
