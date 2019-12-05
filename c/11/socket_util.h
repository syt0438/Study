#include <sys/socket.h>
#include <arpa/inet.h>

int open_server_socket();

void bind_to_port(int fd, int port);

int say(int fd, char *msg);

int read_in(int fd, char *buf, int len);
