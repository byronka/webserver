#include <sys/types.h>
#include <sys/socket.h>
#include "../private.h"
#include <stdio.h>
#include "../do_exit.h"

private int
create_streaming_socket ()
{
  int sockfd = socket (PF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
    {
      perror ("create_streaming_socket");
      do_exit (sys_nerr);
    }
  return sockfd;
}
