#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    __pid_t pid = getpid();

    printf("Main process PID: %d\n", pid);

    char *params[] = {"/usr/bin/printenv", "TEST1", "TEST2", NULL};
    char *envParams[] = {"TEST1=test1", "TEST2=test2", NULL};

    execle("/usr/bin/printenv", "/usr/bin/printenv", "TEST1", "TEST2", NULL, envParams);
    // execve("/usr/bin/printenv", params, envParams);

    return EXIT_SUCCESS;
}
