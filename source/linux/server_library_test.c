#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

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

// declare the private methods we want to test
void make_listening_socket (int sockfd);
int accept_a_connection (int sockfd);
void do_exit (int errno);
int create_streaming_socket ();
struct sockaddr_in initialize_address_port_structure (int port_number);
void bind_address_to_socket (int sockfd, struct sockaddr_in self);

// define some global variables we'll use to help mocking
int socket_return_value = 0;
int bind_return_value = 0;
int listen_return_value = 0;
int error_occurred = false;
int accept_return_value = 0;

// count of tests run
static int tests_run = 0;

// count of tests passed
static int tests_passed = 0;

// stub function - overriding the real function for testing.
int
socket (int domain, int type, int protocol)
{
  return socket_return_value;
}

// stub function - overriding the real function for testing.
int
bind (int socket, const struct sockaddr *address, socklen_t address_len)
{
  return bind_return_value;
}

// stub function - overriding the real function for testing.
int
listen (int sockfd, int backlog)
{
  return listen_return_value;
}

// stub function - overriding the real function for testing.
void
perror (const char *s)
{
  error_occurred = true;
}

// stub function - overriding the real function for testing.
int
accept (int socket, struct sockaddr *restrict address,
	socklen_t * restrict address_len)
{
  return accept_return_value;
}




// TESTS START 
//
//

// Unit Test
// the "create_streaming_socket" function should simply return us
// a sockfd type value - basically an int, that will represent
// the socket file descriptor. look up file descriptor online for more help.
void
test_create_streaming_socket ()
{
  socket_return_value = 42;
  int sockfd = create_streaming_socket ();
  assert (sockfd == 42);
}

// Unit Test
// testing initialization of the address to which we are
// attaching our socket.  In this case, the local address.
// A socket is basically comprised of two addresses - the server
// and the client.  Here's where we initialize for the server.
void
test_initialize_address_port_structure ()
{
  struct sockaddr_in output = initialize_address_port_structure (PORT_NUMBER);

  assert (output.sin_family == AF_INET);
  assert (output.sin_port == htons (PORT_NUMBER));
  assert (output.sin_addr.s_addr == INADDR_ANY);
}

// Unit Test
// Here we take the sockaddr structure (which holds the address and 
// port) and bind it to the socket.  There should be no error here
// because our mocked bind will return 0.
void
test_bind_address_to_socket ()
{
  struct sockaddr_in self = initialize_address_port_structure (PORT_NUMBER);
  int sockfd = 42;
  bind_return_value = 0;
  error_occurred = false;

  bind_address_to_socket (sockfd, self);

  // there should be no error because we return 0 from bind.
  assert (!error_occurred);
}

// Unit Test
// when we bind the address to the socket, if bind returns non-zero
// it's an error condition.
void
test_bind_address_to_socket_negative_case ()
{
  struct sockaddr_in self = initialize_address_port_structure (PORT_NUMBER);
  int sockfd = 42;
  bind_return_value = 123;
  //reset the error flag
  error_occurred = false;

  bind_address_to_socket (sockfd, self);

  // there will be an error because bind will return a non-zero value (123)
  assert (error_occurred);
}

// Unit Test
// Here we set up the socket to listen - as is needed when
// creating a server-type socket.  listen should return zero.
void
test_make_listening_socket ()
{
  int sockfd = 42;
  listen_return_value = 0;
  //reset the error flag
  error_occurred = false;

  make_listening_socket (sockfd);

  // there should be no error because listen should return 0.
  assert (!error_occurred);
}

// Unit Test
// Here we set up the socket to listen - as is needed when
// creating a server-type socket.  If listen returns non-zero,
// it's an error condition.
void
test_make_listening_socket_negative_case ()
{
  int sockfd = 42;
  listen_return_value = 123;
  //reset the error flag
  error_occurred = false;

  make_listening_socket (sockfd);

  // there will be an error because bind will return a non-zero value (123)
  assert (error_occurred);
}

// Unit Test
// this is what we run when a client contacts our listening
// server.  Once the socket has accepted a client, it's
// in a different state, and will need to be closed before
// it can be used again.
void
test_accept_a_connection ()
{
  int sockfd = 42;
  const int return_value = 123;
  accept_return_value = return_value;
  int result_clientfd = accept_a_connection (sockfd);
  assert (result_clientfd == return_value);
}


// TESTS END
//
//

int
main ()
{
  test (test_create_streaming_socket);
  test (test_initialize_address_port_structure);
  test (test_bind_address_to_socket);
  test (test_bind_address_to_socket_negative_case);
  test (test_make_listening_socket);
  test (test_make_listening_socket_negative_case);
  test (test_accept_a_connection);
  printf ("Total tests passed: %d", tests_passed);
  printf (" of %d\n", tests_run);
  return !(tests_passed == tests_run);
}
