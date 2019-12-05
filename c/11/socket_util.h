#include <sys/socket.h>
#include <arpa/inet.h>

int open_server_socket();

void bind_to_port(int fd, int port);

int say(int fd, char *msg);

/*
 * 字符串不以 \ 0 结尾。
 * 
 * 当用户在 telnet 输入文本时，字符串以 \r\n 结尾。
 * 
 * recv() 将返回字符个数，如果发生错误就返回 - 1，如果客户端关闭了连接，就返回 0。
 * 
 * recv() 调用不一定能一次接收到所有字符。
 */
int read_in(int fd, char *buf, int len);
