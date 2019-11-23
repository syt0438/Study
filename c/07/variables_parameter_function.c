#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

int total(int test, int argc, ...)
{
    int total = 0;

    va_list args;
    va_start(args, argc);

    for (size_t i = 0; i < argc; i++)
    {
        int val = va_arg(args, int);

        total += val;

        printf("argument: %i\n", val);
    }

    va_end(args);

    return total;
}

int main(int argc, char *argv[])
{
    int ret = total(10, 3, 30, 60, 110);

    printf("total: %d\n", ret);

    return EXIT_SUCCESS;
}
