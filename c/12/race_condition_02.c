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

int count = 10000;

void *action(void *__arg)
{
    pthread_t tid = pthread_self();

    for (size_t i = 0; i < 100; i++)
    {
        count = count - 1;

        printf("[%ld]: count: %d\n", tid, count);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tasks[100] = {0};
    int task_count = sizeof(tasks) / sizeof(tasks[0]);

    for (size_t i = 0; i < task_count; i++)
    {
        if (pthread_create(tasks + i, NULL, action, NULL) == -1)
        {
            error("create pthread failed");
        }
    }

    for (size_t i = 0; i < task_count; i++)
    {
        if (pthread_join(*(tasks + i), NULL) == -1)
        {
            error("join pthread failed");
        }
    }

    printf("result: %d\n", count);

    return EXIT_SUCCESS;
}
