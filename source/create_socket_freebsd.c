#include <sys/types.h>
#include <sys/socket.h>

private int
create_streaming_socket ()
{
  int sockfd = socket (PF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
    {
      perror ("create_streaming_socket");
      do_exit (errno);
    }
  return sockfd;
}
