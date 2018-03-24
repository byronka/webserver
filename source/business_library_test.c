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
 * we should see the procedure return SMALL when we pass in a value of 25.
 */
void
test_calculateSize_small_happyPath ()
{
  assert (calculate_pant_size (25) == SMALL);
}

//test case
/*
 * we should see the procedure return MEDIUM when we pass in a value of 30.
 */
void
test_calculateSize_medium_happyPath ()
{
  assert (calculate_pant_size (30) == MEDIUM);
}

//test case
/*
 * we should see the procedure return LARGE when we pass in a value of 36.
 */
void
test_calculateSize_large_happyPath ()
{
  assert (calculate_pant_size (36) == LARGE);
}

//test case
/*
 * we should see the procedure return XLARGE when we pass in a value of 45.
 */
void
test_calculateSize_xlarge_happyPath ()
{
  assert (calculate_pant_size (45) == XLARGE);
}

//test case
/*
 * we should see the procedure return UNKNOWN when we pass in a value of 66
 */
void
test_calculateSize_unknown ()
{
  assert (calculate_pant_size (66) == UNKNOWN);
}

//test case
void
test_calculateSize_unknown_2 ()
{
  assert (calculate_pant_size (-5) == UNKNOWN);
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
