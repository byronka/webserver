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
          exit(123);  \
        }

#define test(name) \
  printf("-- Testing %s ... \n", #name); \
  name();

#define PORT_NUMBER 9999

int socket_return_value = 0;
int bind_return_value = 0;
int listen_return_value = 0;
int error_flag = FALSE;
int accept_return_value = 0;

// count of tests run
static int tests_run = 0;

// count of tests passed
static int tests_passed = 0;

// stub function - overriding the real function for testing.
int socket(int domain, int type, int protocol) {
  return socket_return_value;
}

// stub function - overriding the real function for testing.
int bind(int socket, const struct sockaddr *address, socklen_t address_len) {
  return bind_return_value;
}

// stub function - overriding the real function for testing.
int listen(int sockfd, int backlog) {
  return listen_return_value;
}


// stub function - overriding the real function for testing.
void perror(const char *s) {
  error_flag = TRUE;
}


// stub function - overriding the real function for testing.
int accept(int socket, struct sockaddr *restrict address,
                  socklen_t *restrict address_len) {
  return accept_return_value;
}




// TESTS START 
//
//

// Unit Test
void
test_create_streaming_socket() {
  socket_return_value = 42;
  int sockfd = create_streaming_socket();
  assert(sockfd == 42);
}

// Unit Test
void
test_initialize_address_port_structure() {
  struct sockaddr_in output = initialize_address_port_structure(PORT_NUMBER);

  assert(output.sin_family == AF_INET);
  assert(output.sin_port == htons(PORT_NUMBER));
  assert(output.sin_addr.s_addr == INADDR_ANY);
}

// Unit Test
void
test_assign_port_number_to_socket() {
  struct sockaddr_in self = initialize_address_port_structure(PORT_NUMBER);
  int sockfd = 42;
  assign_port_number_to_socket(sockfd, self);
  // if there were any error, we would have exited before this point.
  assert(TRUE || "passed because no error");
}

// Unit Test
void
test_assign_port_number_to_socket_negative_case() {
  struct sockaddr_in self = initialize_address_port_structure(PORT_NUMBER);
  int sockfd = 42;
  bind_return_value = 123;
  //reset the error flag
  error_flag = FALSE;
  assign_port_number_to_socket(sockfd, self);
  // there will be an error because bind will return a non-zero value (123)
  assert(error_flag);
}

// Unit Test
void test_make_listening_socket() {
  int sockfd = 42;
  listen_return_value = 0;
  make_listening_socket(sockfd);
  // if there were any error, we would have exited before this point.
  assert(TRUE || "passed because no error");
}

// Unit Test
void test_make_listening_socket_negative_case() {
  int sockfd = 42;
  listen_return_value = 123;
  //reset the error flag
  error_flag = FALSE;
  make_listening_socket(sockfd);
  // there will be an error because bind will return a non-zero value (123)
  assert(error_flag);
}

// Unit Test
void test_accept_a_connection() {
  int sockfd = 42;
  const int return_value = 123;
  accept_return_value = return_value;
  int result_clientfd = accept_a_connection(sockfd);
  assert(result_clientfd == return_value);
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
        test(test_assign_port_number_to_socket_negative_case);
        test(test_make_listening_socket);
        test(test_make_listening_socket_negative_case);
        test(test_accept_a_connection);
        printf("Total tests passed: %d", tests_passed);
        printf(" of %d\n", tests_run);
        return !(tests_passed == tests_run);
}
