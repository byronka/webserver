typedef enum {SMALL, MEDIUM, LARGE, XLARGE, UNKNOWN} pant_size;
int my_div(int x, int y);
pant_size calculate_size(int waist_size);
int run_server();
int create_streaming_socket(int sockfd);
struct sockaddr_in initialize_address_port_structure(struct sockaddr_in self);
int assign_port_number_to_socket(int sockfd, struct sockaddr_in self);
int make_listening_socket(int sockfd);
int accept_a_connection(int sockfd, struct sockaddr_in * client_addr);
