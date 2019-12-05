#include "socket_util.h"
#include "error_util.h"

int open_server_socket()
{
    int fd = socket(PF_INET, SOCK_STREAM, 0);

    if (fd == -1)
    {
        error("Can't open socket.");
    }

    return fd;
}

void bind_to_port(int fd, int port)
{
    int reuse = 1;

    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1)
    {
        error("Can't set the reuse option on the socket.");
    }

    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(fd, (struct sockaddr *)&name, sizeof(name)) == -1)
    {
        error("Can't bind port to socket");
    }
}

int say(int fd, char *msg)
{
    int ret = send(fd, msg, strlen(msg), 0);

    if (ret == -1)
    {
        fprintf(stderr, "%s: %s\n", "与客户端通信发生了错误", strerror(errno));
    }

    return ret;
}

/*
 * 字符串不以 \ 0 结尾。
 * 
 * 当用户在 telnet 输入文本时，字符串以 \ r\n 结尾。
 * 
 * recv() 将返回字符个数，如果发生错误就返回 - 1，如果客户端关闭了连接，就返回 0。
 * 
 * recv() 调用不一定能一次接收到所有字符。
 */
int read_in(int fd, char *buf, int len)
{
    char *s = buf;
    int slen = len;

    int c = recv(fd, s, slen, 0);
    while ((c > 0) && s[c - 1] != '\n')
    {
        s += c;
        slen -= c;

        c = recv(fd, s, slen, 0);
    }

    if (c < 0)
    {
        return c;
    }
    else if (c == 0)
    {
        buf[0] = '\0';
    }
    else
    {
        s[c - 1] = '\0';
    }

    return len - slen;
}