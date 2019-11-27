#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    printf("stdin fileno: %d\n", fileno(stdin));
    printf("stdout fileno: %d\n", fileno(stdout));
    printf("stderr fileno: %d\n", fileno(stderr));

    char path[30] = {0};
    FILE *files[10] = {NULL};
    size_t files_len = sizeof(files) / sizeof(FILE *);

    for (size_t i = 0; i < files_len; i++)
    {
        int ret = sprintf(path, "./data/fileno_%d.txt", i);

        FILE *file = fopen(path, "w");

        if (!file)
        {
            printf("create file failed: %s\n", strerror(errno));

            continue;
        }

        *(files + i) = file;
        printf("new file %s fileno: %d\n", path, fileno(file));
    }

    for (size_t i = 0; i < files_len; i++)
    {
        FILE *file = *(files + i);

        if (file)
        {
            fclose(file);
        }
    }

    return EXIT_SUCCESS;
}
