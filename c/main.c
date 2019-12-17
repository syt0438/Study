#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("%d\n", sizeof(char));
    printf("%d\n", sizeof('a'));
    printf("%d\n", sizeof("志有"));

    return EXIT_SUCCESS;
}
