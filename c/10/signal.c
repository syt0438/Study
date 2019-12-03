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
    printf("Trap SIGINT signal: %d\n", seg);

    exit(EXIT_FAILURE);
}

void sigkill_handler(int seg)
{
    printf("Trap SIGKILL signal: %d\n", seg);

    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    signal(SIGKILL, sigkill_handler);
    signal(SIGINT, sigint_handler);

    sleep(100);

    return EXIT_SUCCESS;
}
