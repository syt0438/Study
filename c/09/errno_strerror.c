#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    puts(strerror(errno));
    int ret = execl("diner_info", "diner_info", "4", NULL);
    printf("ret = %d, errno = %d\n", ret, errno);
    puts(strerror(errno));

    return EXIT_SUCCESS;
}
