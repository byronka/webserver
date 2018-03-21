#define MAXBUF    1024
#define TRUE 1
#define FALSE 0

int run_server();
int create_streaming_socket();
struct sockaddr_in initialize_address_port_structure(int port_number);
void assign_port_number_to_socket(int sockfd, struct sockaddr_in self);
void make_listening_socket(int sockfd);
int accept_a_connection(int sockfd);
int create_usable_socket(int port_number);
void accept_receive_send_back_data(int sockfd);

