#define MY_PORT   9999
#define MAXBUF    1024
#define TRUE 1
#define FALSE 0

int run_server();
int create_streaming_socket();
struct sockaddr_in initialize_address_port_structure();
void assign_port_number_to_socket(int sockfd, struct sockaddr_in self);
void make_listening_socket(int sockfd);
int accept_a_connection(int sockfd, struct sockaddr_in * client_addr);

