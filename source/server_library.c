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

int run_server(int port_number)
{   
  int sockfd = create_usable_socket(port_number);

  while (TRUE) { 
    accept_receive_send_back_data(sockfd);
  }
  close(sockfd);
  return 0;
}

void accept_receive_send_back_data(sockfd) {
    char buffer[MAXBUF];
    int clientfd = accept_a_connection(sockfd);

    /*---Echo back anything sent---*/
    ssize_t size = recv(clientfd, buffer, MAXBUF, 0); 
    printf("Received: %s", buffer);
    send(clientfd, buffer, size, 0);

    /*---Close data connection---*/
    close(clientfd);
}

int create_usable_socket(int port_number) {
  int sockfd = create_streaming_socket();
  struct sockaddr_in self = initialize_address_port_structure(port_number);
  assign_port_number_to_socket(sockfd, self);
  make_listening_socket(sockfd);
  return sockfd;
}

int accept_a_connection(int sockfd) {
    struct sockaddr_in client_addr;
    socklen_t addrlen = sizeof(client_addr);
    int clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
    printf("%s:%d connected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
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

struct sockaddr_in initialize_address_port_structure(int port_number) {
  struct sockaddr_in self;
  bzero(&self, sizeof(self));
  self.sin_family = AF_INET;
  self.sin_port = htons(port_number);
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

void make_listening_socket(int sockfd) {
  if ( listen(sockfd, 20) != 0 )
  {
    perror("socket--listen");
    exit(errno);
  }
}






// vim: ai:tw=70
