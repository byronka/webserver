#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
#include "server_library.h"

// redefine assert to set a boolean flag
#ifdef assert
#undef assert
#endif

#define assert(x) (rslt = rslt && (x))
#define TRUE 1
#define FALSE 0


// main result return code used by redefined assert
static int rslt;

// variables controling stub functions
static int expected_code;
static int should_exit;
static jmp_buf jump_env;

// test suite main variables
static int done;
static int num_tests;
static int tests_passed;

//  utility function
void TestStart(char *name)
{
    num_tests++;
    rslt = 1;
    printf("-- Testing %s ... ",name);
}

//  utility function
void TestEnd()
{
    if (rslt) tests_passed++;
    printf("%s\n", rslt ? "success" : "fail");
}

// stub function
void exit(int code)
{
    if (!done)
    {
        assert(should_exit==TRUE);
        assert(expected_code==code);
        longjmp(jump_env, 1);
    }
    else
    {
        _exit(code);
    }
}

// test case
/* what happens if we divide 12 by 3?  Should return 4. */
void test_mydiv_normal()
{
    int jmp_rval;
    int r;

    TestStart("test_mydiv_normal");
    should_exit = FALSE;
    if (!(jmp_rval=setjmp(jump_env)))
    {
        r = my_div(12,3);
    }

    assert(jmp_rval==0);
    assert(r==4);
    TestEnd();
}

// test case
/* if we divide by 0, the code should exit with a value of 2 */
void test_mydiv_div0()
{
    int jmp_rval;
    int r;

    TestStart("test_mydiv_div0");
    should_exit = TRUE;
    expected_code = 2;
    if (!(jmp_rval=setjmp(jump_env)))
    {
        r = my_div(2,0);
    }

    assert(jmp_rval==1);
    TestEnd();
}

// test case
/* 
   we should see the procedure return SMALL
   when we pass in a value of 15.
 */
void test_calculateSize_small_happyPath()
{
    TestStart("test_calculateSize_small_happyPath");
    assert(calculate_size(15) == SMALL);
    TestEnd();
}

// test case
/* 
   we should see the procedure return MEDIUM
   when we pass in a value of 25.
 */
void test_calculateSize_medium_happyPath()
{
    TestStart("test_calculateSize_medium_happyPath");
    assert(calculate_size(25) == MEDIUM);
    TestEnd();
}

// test case
/* 
   we should see the procedure return LARGE
   when we pass in a value of 35.
 */
void test_calculateSize_large_happyPath()
{
    TestStart("test_calculateSize_large_happyPath");
    assert(calculate_size(35) == LARGE);
    TestEnd();
}

// test case
/* 
   we should see the procedure return UNKNOWN
   when we pass in a value of 45 or -5
 */
void test_calculateSize_unknown()
{
    TestStart("test_calculateSize_unknown");
    assert(calculate_size(45) == UNKNOWN);
    assert(calculate_size(-5) == UNKNOWN);
    TestEnd();
}

int main()
{
    num_tests = 0;
    tests_passed = 0;
    done = FALSE;
    test_mydiv_normal();
    test_mydiv_div0();
    test_calculateSize_small_happyPath();
    test_calculateSize_medium_happyPath();
    test_calculateSize_large_happyPath();
    test_calculateSize_unknown();
    printf("Total tests passed: %d", tests_passed);
    printf(" of %d\n", num_tests);
    done = TRUE;
    return !(tests_passed == num_tests);
}
