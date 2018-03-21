#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <strings.h>

#include "server_library.h"

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
          exit(1); \
        }

#define test(name) \
  printf("-- Testing %s ... \n", #name); \
  name();

#define PORT_NUMBER 9999


// count of tests run
static int tests_run = 0;

// count of tests passed
static int tests_passed = 0;

// TESTS START 
//
//

// Unit Test
void test_create_usable_socket() {
  int sockfd = create_usable_socket(PORT_NUMBER);
  assert(sockfd > 0);

}

// TESTS END
//
//

int 
main()
{
        test(test_create_usable_socket);
        printf("Total tests passed: %d", tests_passed);
        printf(" of %d\n", tests_run);
        return !(tests_passed == tests_run);
}
