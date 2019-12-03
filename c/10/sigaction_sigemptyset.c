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

/*
 * 注册信号量处理器
 */
int register_sigaction(int seg, void (*handler)(int))
{
    struct sigaction action = {0};
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    return sigaction(seg, &action, NULL);
}

int main(int argc, char *argv[])
{
    if (register_sigaction(SIGINT, sigint_handler) == -1)
    {
        error("register SIGINT sigaction handler failed");
    }

    if (register_sigaction(SIGKILL, sigkill_handler) == -1)
    {
        error("register SIGKILL sigaction handler failed");
    }

    sleep(100);

    return EXIT_SUCCESS;
}
