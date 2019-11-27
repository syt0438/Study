#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    printf("[%d]: %s", argc, argv[argc - 1]);

    return EXIT_SUCCESS;
}
