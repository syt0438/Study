#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", strerror(errno), msg);

    exit(EXIT_FAILURE);
}

int registe_sigaction(int seg, void (*handler)(int))
{
    struct sigaction action = {0};
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    return sigaction(seg, &action, NULL);
}

int server_d = -1;

void server_close(int seg)
{
    if (server_d != -1)
    {
        close(server_d);
    }

    puts("\nClosed server success.\n");

    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    if (registe_sigaction(SIGINT, server_close) == -1)
    {
        error("registe SIGINT signal handler failed.");
    }

    if (registe_sigaction(SIGTERM, server_close) == -1)
    {
        error("registe SIGTERM signal handler failed.");
    }

    //#region Create a socket descriptor
    server_d = socket(PF_INET, SOCK_STREAM, 0);

    if (server_d == -1)
    {
        error("Can not open socket");
    }

    int reuse = 1;
    if (setsockopt(server_d, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1)
    {
        error("set socket option failed");
    }

    //#endregion

    //#region Create a socket name that represents port 30000
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(30000);
    name.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_d, (struct sockaddr *)&name, sizeof(name)) == -1)
    {
        error("Can not bind port: 30000");
    }
    //#endregion

    //#region listen 30000 port
    if (listen(server_d, 2) == -1)
    {
        error("Can not listen socket port 30000");
    }
    //#endregion

    for (;;)
    {
        puts("Wait client connect...");

        struct sockaddr_storage client_addr = {0};
        socklen_t address_size = sizeof(client_addr);
        int client_d = accept(server_d, (struct sockaddr *)&client_addr, (socklen_t *)&address_size);

        if (client_d == -1)
        {
            error("client connet to server port 30000 failed");
        }

        puts("Accepted client connect.");

        char *banner = "Welcome to Knock-Knock Server\n";

        if (send(client_d, banner, strlen(banner), 0) == -1)
        {
            error("Send banner failed.");
        }

        puts("Close client connect.");

        close(client_d);
    }

    close(server_d);

    return EXIT_SUCCESS;
}
