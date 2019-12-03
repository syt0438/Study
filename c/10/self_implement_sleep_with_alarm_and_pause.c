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

int registe_sigaction(int seg, void (*handler)(int))
{
    struct sigaction action = {0};
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    return sigaction(seg, &action, NULL);
}

void sigalrm_handler(int seg)
{
    printf("Custom alarm clock: %d\n", seg);
}

void custom_sleep(int s)
{
    alarm(s);

    puts("suspend current process: start");
    pause();
    puts("suspend current process: end");
}

int main(int argc, char *argv[])
{
    if (registe_sigaction(SIGALRM, sigalrm_handler) == -1)
    {
        error("SIGALRM signel handler register failed.");
    }

    custom_sleep(10);

    return EXIT_SUCCESS;
}
