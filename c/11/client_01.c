#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "socket_util.h"
#include "signal_util.h"
#include "error_util.h"

int main()
{
    int client_d = open_client_socket();
    connect_to_server(client_d, "211.159.216.48", 30000);

    puts("connected to server");

    char buf[255] = {0};
    int recv_count = read_in(client_d, buf, sizeof(buf));

    while (recv_count > 0)
    {
        printf("recv meg: %s\n", buf);

        char *read_ret = fgets(buf, sizeof(buf), stdin);
        while (read_ret == NULL)
        {
            read_ret = fgets(buf, sizeof(buf), stdin);
        }

        if (send(client_d, buf, strlen(buf), 0) == -1)
        {
            error("client send data error");
        }

        recv_count = read_in(client_d, buf, sizeof(buf));
    }

    printf("before closed recv count: %d\n", recv_count);

    close(client_d);

    puts("Closed client connect.");

    return EXIT_SUCCESS;
}