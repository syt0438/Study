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

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *action(void *__arg)
{
    int *arg = (int *)__arg;

    for (size_t i = 0; i < 100; i++)
    {
        pthread_mutex_lock(&lock);

        *arg = *arg - 1;

        pthread_mutex_unlock(&lock);
    }

    return arg;
}

int main(int argc, char *argv[])
{
    int count = 10000;
    pthread_t tasks[100] = {0};
    int task_count = sizeof(tasks) / sizeof(tasks[0]);

    for (size_t i = 0; i < task_count; i++)
    {
        if (pthread_create(tasks + i, NULL, action, &count) == -1)
        {
            error("create pthread failed");
        }
    }

    void *result;
    for (size_t i = 0; i < task_count; i++)
    {
        if (pthread_join(*(tasks + i), &result) == -1)
        {
            error("join pthread failed");
        }
    }

    printf("result: %d\n", count);

    return EXIT_SUCCESS;
}
