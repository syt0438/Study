#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "11/socket_util.h"
#include "11/signal_util.h"
#include "11/error_util.h"

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
    registe_sigaction(SIGINT, server_close);
    registe_sigaction(SIGTERM, server_close);

    //#region Create a socket descriptor
    server_d = open_server_socket();

    //#endregion

    //#region Create a socket name that represents port 30000
    bind_to_port(server_d, 30000);
    //#endregion

    //#region listen 30000 port
    if (listen(server_d, 10) == -1)
    {
        error("Can not listen socket port 30000");
    }
    //#endregion

    char buf[255] = {0};

    for (;;)
    {
        puts("Wait client connect...");

        struct sockaddr_storage client_addr = {0};
        socklen_t address_size = sizeof(client_addr);
        int client_d = accept(server_d, (struct sockaddr *)&client_addr, (socklen_t *)&address_size);

        if (client_d == -1)
        {
            fprintf(stderr, "client connet to server port 30000 failed");

            continue;
        }

        puts("Accepted client connect.");

        if (say(client_d, "Welcome to Knock-Knock Server\n") != -1)
        {
            read_in(client_d, buf, sizeof(buf));

            if (!strncmp("Who's there?", buf, 12))
            {
                if (say(client_d, "Oscar\n>") != -1)
                {
                    read_in(client_d, buf, sizeof(buf));

                    if (!strncmp("Oscar who?", buf, 10))
                    {
                        say(client_d, "Oscar silly question, you get a silly answer\n");
                    }
                    else
                    {
                        say(client_d, "You should say 'Oscar who?' !\n");
                    }
                }
            }
            else
            {
                say(client_d, "You should say 'Who's there?' !\n");
            }
        }

        puts("Close client connect.");

        close(client_d);
    }

    close(server_d);

    return EXIT_SUCCESS;
}
