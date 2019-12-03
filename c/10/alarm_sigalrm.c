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

    for (size_t i = 0; i < 10; i++)
    {
        printf("Alarm clock loop: %d\n", i);
    }

    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int ret = alarm(10);
    printf("alarm return: %d\n", ret);

    ret = alarm(5);
    printf("alarm return: %d\n", ret);

    if (registe_sigaction(SIGALRM, sigalrm_handler) == -1)
    {
        error("SIGALRM signel handler register failed.");
    }

    puts("loop start");
    for (size_t i = 1; i <= 50; i++)
    {
        printf("loop: %d\n", i);

        sleep(1);
    }
    puts("loop end");

    return EXIT_SUCCESS;
}
