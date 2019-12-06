#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", strerror(errno), msg);

    exit(EXIT_FAILURE);
}

void *does_not(void *a)
{
    for (size_t i = 0; i < 5; i++)
    {
        if (i % 2 == 0)
        {
            sleep(1);
        }

        printf("[%d]: Does not!\n", i);
    }

    return NULL;
}

void *does_too(void *a)
{
    for (size_t i = 0; i < 5; i++)
    {
        sleep(1);

        printf("[%d]: Does too!\n", i);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t t0;
    pthread_t t1;

    if (pthread_create(&t0, NULL, does_not, NULL) == -1)
    {
        error("Can't create thread t0 does_not.");
    }

    if (pthread_create(&t1, NULL, does_too, NULL) == -1)
    {
        error("Can't create thread t1 does_too.");
    }

    void *result = NULL;

    if (pthread_join(t0, &result) == -1)
    {
        error("join pthread t0 failed");
    }

    if (pthread_join(t1, &result) == -1)
    {
        error("join pthread t1 failed");
    }

    return EXIT_SUCCESS;
}
