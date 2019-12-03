#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", strerror(errno), msg);

    exit(EXIT_FAILURE);
}

void sigint_handler(int seg)
{
    printf("trap signal [%d]\n", seg);

    sleep(3);

    raise(SIGTERM);
}

void sigterm_handler(int seg)
{
    printf("trap signal [%d]\n", seg);

    sleep(3);

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

int main(int argc, char *argv[])
{
    if (registe_sigaction(SIGINT, sigint_handler) == -1)
    {
        error("register SIGINT signal handler failed\n");
    }

        if (registe_sigaction(SIGTERM, sigterm_handler) == -1)
    {
        error("register SIGINT signal handler failed\n");
    }

    sleep(10000);

    return EXIT_SUCCESS;
}
