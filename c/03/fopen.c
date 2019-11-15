#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *in = NULL;

    if (!(in = fopen("./03/in", "r")))
    {
        fprintf(stderr, "无法打开文件: %s\n", "in");

        return EXIT_FAILURE;
    }

    FILE *out = fopen("out", "w");

    char line[100] = {0};

    while (fscanf(in, "%99[^\n]\n", line) == 1)
    {
        fprintf(out, "%s\n", line);
    }

    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}