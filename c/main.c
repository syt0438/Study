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
    

    return EXIT_SUCCESS;
}
