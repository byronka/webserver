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
        }

#define test(name) \
  printf("-- Testing %s ... \n", #name); \
  name();

// count of tests run
static int tests_run = 0;

// count of tests passed
static int tests_passed = 0;

// stub function - overriding the real function for testing.
int socket(int domain, int type, int protocol) {
  return 42;
}

// stub function - overriding the real function for testing.
int bind(int socket, const struct sockaddr *address, socklen_t address_len) {
  return 0;
}

// stub function - overriding the real function for testing.
void perror(const char *s) {
  printf("failure: error: %s\n", s);
  exit(1);
}

// TESTS START 
//
//

// Unit Test
void
test_create_streaming_socket() {
  int sockfd = create_streaming_socket();
  assert(sockfd == 42);
}

// Unit Test
void
test_initialize_address_port_structure() {
  struct sockaddr_in output = initialize_address_port_structure();

  assert(output.sin_family == AF_INET);
  assert(output.sin_port == htons(MY_PORT));
  assert(output.sin_addr.s_addr == INADDR_ANY);
}

// Unit Test
void
test_assign_port_number_to_socket() {
  struct sockaddr_in self = initialize_address_port_structure();
  int sockfd = 42;
  assign_port_number_to_socket(sockfd, self);
  // if there were any error, we would have exited before this point.
  assert("no error" == "no error");
}


// TESTS END
//
//

int 
main()
{
        test(test_create_streaming_socket);
        test(test_initialize_address_port_structure);
        test(test_assign_port_number_to_socket);
        printf("Total tests passed: %d", tests_passed);
        printf(" of %d\n", tests_run);
        return !(tests_passed == tests_run);
}
