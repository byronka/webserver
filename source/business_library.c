#include "business_library.h"

/* See header for details on public procedures */


pant_size
calculate_pant_size (int waist_size)
{
  if (waist_size >= 25 && waist_size < 30) {
      return PANT_SMALL;
  }
  if (waist_size >= 30 && waist_size < 36) {
      return PANT_MEDIUM;
  }
  if (waist_size >= 36 && waist_size < 44) {
      return PANT_LARGE;
  }
  if (waist_size > 44 && waist_size < 65) {
      return PANT_XLARGE;
  }

  return PANT_UNKNOWN;
}

shirt_size
calculate_shirt_size (int body_size) {
  if (body_size >= 75 && body_size < 95) {
      return SHIRT_SMALL;
  }
  if (body_size >= 95 && body_size < 110) {
      return SHIRT_MEDIUM;
  }
  if (body_size >= 110 && body_size < 150) {
      return SHIRT_LARGE;
  }
  if (body_size > 150 && body_size < 250) {
      return SHIRT_XLARGE;
  }

  return SHIRT_UNKNOWN;

}
