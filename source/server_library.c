#include <stdlib.h>
#include "server_library.h"

#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <strings.h>

int run_server()
{   
  char buffer[MAXBUF];

  int sockfd = create_streaming_socket();
  struct sockaddr_in self = initialize_address_port_structure();
  assign_port_number_to_socket(sockfd, self);
  sockfd = make_listening_socket(sockfd);

  /* loop forever */
  while (TRUE) { 
    int clientfd;
    struct sockaddr_in client_addr;

    clientfd = accept_a_connection(sockfd, &client_addr);

    /*---Echo back anything sent---*/
    send(clientfd, buffer, recv(clientfd, buffer, MAXBUF, 0), 0);

    /*---Close data connection---*/
    close(clientfd);
  }

  /*---Clean up (should never get here!)---*/
  close(sockfd);
  return 0;
}

int accept_a_connection(int sockfd, struct sockaddr_in * client_addr) {
    int addrlen=sizeof(client_addr);
    struct sockaddr_in client_addr_copy;
    client_addr_copy = *client_addr;
    int clientfd = accept(sockfd, (struct sockaddr*)&client_addr_copy, &addrlen);
    printf("%s:%d connected\n", inet_ntoa(client_addr_copy.sin_addr), ntohs(client_addr_copy.sin_port));
    return clientfd;
}

int create_streaming_socket() {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if ( sockfd < 0 ) {
    perror("Socket");
    exit(errno);
  }
  return sockfd;
}

struct sockaddr_in initialize_address_port_structure() {
  struct sockaddr_in self;
  bzero(&self, sizeof(self));
  self.sin_family = AF_INET;
  self.sin_port = htons(MY_PORT);
  self.sin_addr.s_addr = INADDR_ANY;
  return self;
}

void assign_port_number_to_socket(int sockfd, struct sockaddr_in self) {
  int bind_result = bind(sockfd, (struct sockaddr*)&self, sizeof(self));
  if ( bind_result != 0 )
  {
    perror("socket--bind");
    exit(errno);
  }
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
