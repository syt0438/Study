#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
    option_parameters: -a -e fuck ok -b shit -v && echo OK
*/
int main(int argc, char *argv[])
{
    printf("argc: %d\n", argc);

    int v = EOF;

    while ((v = getopt(argc, argv, "ae:")) != EOF)
    {
        switch (v)
        {
        case 'e':
            printf("option: %c -> %s\n", v, optarg);
            break;
        case 'a':
            printf("option: %c -> %s\n", v, optarg);
            break;
        default:
            printf("invalid option: %c ->%s \n", v, optarg);
            break;
        }
    }

    printf("argc: %d, optind: %d\n", argc, optind);

    argc -= optind;
    argv += optind;

    printf("argc: %d, optind: %d\n", argc, optind);

    for (size_t i = 0; i < argc; i++)
    {
        printf("剩余参数: i: %d, v: %p:%s\n", i, argv + i, *(argv + i));
    }

    return EXIT_SUCCESS;
}