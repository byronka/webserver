#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "business_library.h"

// redefine assert to set a boolean flag
#ifdef assert
#undef assert
#endif

#define TRUE 1
#define FALSE 0

#define assert(x) \
        tests_run++;  \
        printf("\tresult for ( %s ): ", #x); \
        if((x)) { \
          tests_passed++; \
          printf("success\n"); \
        } else {          \
          printf("failure\n"); \
          exit(123); \
        }

#define test(name) \
  printf("-- Testing %s ... \n", #name); \
  name();


// count of tests run
static int tests_run = 0;

// count of tests passed
static int tests_passed = 0;

// TESTS START
//
//
//

//test case
/*
 * we should see the procedure return PANT_SMALL when we pass in a value of 25.
 */
void
test_calculatePantSize_small_happyPath ()
{
  assert (calculate_pant_size (25) == PANT_SMALL);
}

//test case
/*
 * we should see the procedure return PANT_MEDIUM when we pass in a value of 30.
 */
void
test_calculatePantSize_medium_happyPath ()
{
  assert (calculate_pant_size (30) == PANT_MEDIUM);
}

//test case
/*
 * we should see the procedure return PANT_LARGE when we pass in a value of 36.
 */
void
test_calculatePantSize_large_happyPath ()
{
  assert (calculate_pant_size (36) == PANT_LARGE);
}

//test case
/*
 * we should see the procedure return PANT_XLARGE when we pass in a value of 45.
 */
void
test_calculatePantSize_xlarge_happyPath ()
{
  assert (calculate_pant_size (45) == PANT_XLARGE);
}

//test case
/*
 * we should see the procedure return PANT_UNKNOWN when we pass in a value of 66
 */
void
test_calculatePantSize_unknown ()
{
  assert (calculate_pant_size (66) == PANT_UNKNOWN);
}

//test case
void
test_calculatePantSize_unknown_2 ()
{
  assert (calculate_pant_size (-5) == PANT_UNKNOWN);
}

//test case
/*
 * we should see the procedure return SHIRT_SMALL when we pass in a value of 75.
 */
void
test_calculateShirtSize_small_happyPath ()
{
  assert (calculate_shirt_size (75) == SHIRT_SMALL);
}

//test case
/*
 * we should see the procedure return SHIRT_MEDIUM when we pass in a value of 95.
 */
void
test_calculateShirtSize_medium_happyPath ()
{
  assert (calculate_shirt_size (95) == SHIRT_MEDIUM);
}

//test case
/*
 * we should see the procedure return SHIRT_LARGE when we pass in a value of 110.
 */
void
test_calculateShirtSize_large_happyPath ()
{
  assert (calculate_shirt_size (110) == SHIRT_LARGE);
}

//test case
/*
 * we should see the procedure return SHIRT_XLARGE when we pass in a value of 150.
 */
void
test_calculateShirtSize_xlarge_happyPath ()
{
  assert (calculate_shirt_size (150) == SHIRT_XLARGE);
}

//test case
/*
 * we should see the procedure return SHIRT_UNKNOWN when we pass in a value of 25
 */
void
test_calculateShirtSize_unknown ()
{
  assert (calculate_shirt_size (25) == SHIRT_UNKNOWN);
}

//test case
void
test_calculateShirtSize_unknown_2 ()
{
  assert (calculate_shirt_size (-5) == SHIRT_UNKNOWN);
}

//test case
void
test_calculateShirtSize_unknown_3 ()
{
  assert (calculate_shirt_size (251) == SHIRT_UNKNOWN);
}


// TESTS END
//
//
//

int
main ()
{
  test (test_calculatePantSize_small_happyPath);
  test (test_calculatePantSize_medium_happyPath);
  test (test_calculatePantSize_large_happyPath);
  test (test_calculatePantSize_xlarge_happyPath);
  test (test_calculatePantSize_unknown);
  test (test_calculatePantSize_unknown_2);
  test (test_calculateShirtSize_small_happyPath);
  test (test_calculateShirtSize_medium_happyPath);
  test (test_calculateShirtSize_large_happyPath);
  test (test_calculateShirtSize_xlarge_happyPath);
  test (test_calculateShirtSize_unknown);
  test (test_calculateShirtSize_unknown_2);
  test (test_calculateShirtSize_unknown_3);
  printf ("Total tests passed: %d", tests_passed);
  printf (" of %d\n", tests_run);
  return !(tests_passed == tests_run);
}
