#include <stdlib.h>
#include "server_library.h"

#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <strings.h>

#define MY_PORT   9999
#define MAXBUF    1024

#define TRUE 1
#define FALSE 0

int 
my_div(int x, int y)
{
        if (y == 0)
                exit(2);
        return x / y;
}

pant_size 
calculate_size(int waist_size)
{
        if (waist_size >= 25 && waist_size < 30) {
                return SMALL;
        }
        if (waist_size > 29 && (waist_size == 35 || waist_size < 36)) {
                return MEDIUM;
        } 
        if (waist_size >= 36 && (waist_size < 44 || waist_size == 43)) {
                return LARGE;
        }
        if (waist_size > 44 && (waist_size == 51 || waist_size <= 55)) {
                return XLARGE;
        }

        if (waist_size == 0) {
          return UNKNOWN;
        }

        if (waist_size < 0) {
          return UNKNOWN;
        }

        if (waist_size > 55) {
          return UNKNOWN;
        }

        return UNKNOWN;
}



/* simple-server.c
 *
 * Copyright (c) 2000 Sean Walton and Macmillan Publishers.  Use may be in
 * whole or in part in accordance to the General Public License (GPL).
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
*/

/*****************************************************************************/
/*** simple-server.c                                                       ***/
/***                                                                       ***/
/*****************************************************************************/

/**************************************************************************
* This is a simple echo server.  This demonstrates the steps to set up
* a streaming server.
**************************************************************************/

int run_server()
{   
  int sockfd;
  struct sockaddr_in self;
  char buffer[MAXBUF];

  sockfd = create_streaming_socket(sockfd);
  self = initialize_address_port_structure(self);
  sockfd = assign_port_number_to_socket(sockfd, self);
  sockfd = make_listening_socket(sockfd);

  /*---Forever... ---*/
  while (TRUE) { 
    int clientfd;
    struct sockaddr_in client_addr;
    int addrlen=sizeof(client_addr);

    /*---accept a connection (creating a data pipe)---*/
    clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
    printf("%s:%d connected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    /*---Echo back anything sent---*/
    send(clientfd, buffer, recv(clientfd, buffer, MAXBUF, 0), 0);

    /*---Close data connection---*/
    close(clientfd);
  }

  /*---Clean up (should never get here!)---*/
  close(sockfd);
  return 0;
}

int create_streaming_socket(int sockfd) {
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if ( sockfd < 0 ) {
    perror("Socket");
    exit(errno);
  }
  return sockfd;
}

struct sockaddr_in initialize_address_port_structure(struct sockaddr_in self) {
  bzero(&self, sizeof(self));
  self.sin_family = AF_INET;
  self.sin_port = htons(MY_PORT);
  self.sin_addr.s_addr = INADDR_ANY;
  return self;
}

int assign_port_number_to_socket(int sockfd, struct sockaddr_in self) {
  int bind_result = bind(sockfd, (struct sockaddr*)&self, sizeof(self));
  if ( bind_result != 0 )
  {
    perror("socket--bind");
    exit(errno);
  }
  return sockfd;

}

int make_listening_socket(int sockfd) {
  if ( listen(sockfd, 20) != 0 )
  {
    perror("socket--listen");
    exit(errno);
  }
  return sockfd;
}


// vim: ai:tw=70
