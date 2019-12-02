#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

void error(char *msg)
{
    fprintf(stderr, "%s: %s", strerror(errno), msg);

    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int pipe_fd[2] = {0};
    int len = sizeof(pipe_fd) / sizeof(pipe_fd[0]);

    if (pipe(pipe_fd) == -1)
    {
        error("Can't create the pipe.");
    }

    int pid = fork();
    int pid_status = 0;

    if (pid == 0)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], fileno(stdout));

        puts("This is child process output data.");
    }

    close(pipe_fd[1]);
    dup2(pipe_fd[0], fileno(stdin));

    char msg[100] = {0};

    fgets(msg, sizeof(msg), stdin);

    printf("This is parent process input data: %s\n", msg);

    return EXIT_SUCCESS;
}
