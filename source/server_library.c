#include <stdlib.h>
#include "server_library.h"

#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <strings.h>
#include <unistd.h>

// purpose of this define:
// if we are in DEBUG mode, remove the static keyword so
// we can access the method from the test code.
#ifdef DEBUG
#define private
#else
#define private static
#endif

// declare the "private" functions for this file.
private void make_listening_socket (int sockfd);
private int accept_a_connection (int sockfd);
private void do_exit (int error_number);
private int create_usable_socket (int port_number);
private int create_streaming_socket ();
private struct sockaddr_in initialize_address_port_structure (int
							      port_number);
private void bind_address_to_socket (int sockfd, struct sockaddr_in self);
private void accept_receive_send_back_data (int sockfd);

/*
 * This is the only function that is exposed to
 * external callers. See details in server_library.h
 */
void
run_server (int port_number)
{
  int sockfd = create_usable_socket (port_number);

  while (TRUE)
    {
      accept_receive_send_back_data (sockfd);
    }
  close (sockfd);
}

/*
 * Simply receive any data sent and echo it back to the user
 */
private void
accept_receive_send_back_data (int sockfd)
{
  char buffer[MAXBUF];
  int clientfd = accept_a_connection (sockfd);

  ssize_t size = recv (clientfd, buffer, MAXBUF, 0);
  printf ("Received: %s", buffer);

  send (clientfd, buffer, size, 0);

  close (clientfd);
}

/*
 * go through all the steps to produce a socket ready for
 * sending and receiving
 */
private int
create_usable_socket (int port_number)
{
  int sockfd = create_streaming_socket ();
  struct sockaddr_in self = initialize_address_port_structure (port_number);
  bind_address_to_socket (sockfd, self);
  make_listening_socket (sockfd);
  return sockfd;
}

private int
accept_a_connection (int sockfd)
{
  struct sockaddr_in client_addr;
  socklen_t addrlen = sizeof (client_addr);
  int clientfd = accept (sockfd, (struct sockaddr *) &client_addr, &addrlen);
  printf ("%s:%d connected\n", inet_ntoa (client_addr.sin_addr),
	  ntohs (client_addr.sin_port));
  return clientfd;
}

private int
create_streaming_socket ()
{
  int sockfd = socket (AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
    {
      perror ("create_streaming_socket");
      do_exit (errno);
    }
  return sockfd;
}

private struct sockaddr_in
initialize_address_port_structure (int port_number)
{
  struct sockaddr_in self;
  bzero (&self, sizeof (self));
  self.sin_family = AF_INET;
  self.sin_port = htons (port_number);
  self.sin_addr.s_addr = INADDR_ANY;
  return self;
}

private void
bind_address_to_socket (int sockfd, struct sockaddr_in self)
{
  int bind_result = bind (sockfd, (struct sockaddr *) &self, sizeof (self));
  if (bind_result != 0)
    {
      perror ("bind_address_to_socket");
      do_exit (errno);
    }
}

private void
make_listening_socket (int sockfd)
{
  if (listen (sockfd, 20) != 0)
    {
      perror ("make_listening_socket");
      do_exit (errno);
    }
}

/**
 * wrapping exit so it doesn't actually exit while debugging and
 * testing.
 */
private void
do_exit (int error_number)
{
#ifndef DEBUG
  exit (errno);
#endif
}






// vim: ai:tw=70
