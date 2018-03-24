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
test_calculateSize_small_happyPath ()
{
  assert (calculate_pant_size (25) == PANT_SMALL);
}

//test case
/*
 * we should see the procedure return PANT_MEDIUM when we pass in a value of 30.
 */
void
test_calculateSize_medium_happyPath ()
{
  assert (calculate_pant_size (30) == PANT_MEDIUM);
}

//test case
/*
 * we should see the procedure return PANT_LARGE when we pass in a value of 36.
 */
void
test_calculateSize_large_happyPath ()
{
  assert (calculate_pant_size (36) == PANT_LARGE);
}

//test case
/*
 * we should see the procedure return PANT_XLARGE when we pass in a value of 45.
 */
void
test_calculateSize_xlarge_happyPath ()
{
  assert (calculate_pant_size (45) == PANT_XLARGE);
}

//test case
/*
 * we should see the procedure return PANT_UNKNOWN when we pass in a value of 66
 */
void
test_calculateSize_unknown ()
{
  assert (calculate_pant_size (66) == PANT_UNKNOWN);
}

//test case
void
test_calculateSize_unknown_2 ()
{
  assert (calculate_pant_size (-5) == PANT_UNKNOWN);
}


// TESTS END
//
//
//

int
main ()
{
  test (test_calculateSize_small_happyPath);
  test (test_calculateSize_medium_happyPath);
  test (test_calculateSize_large_happyPath);
  test (test_calculateSize_xlarge_happyPath);
  test (test_calculateSize_unknown);
  test (test_calculateSize_unknown_2);
  printf ("Total tests passed: %d", tests_passed);
  printf (" of %d\n", tests_run);
  return !(tests_passed == tests_run);
}
