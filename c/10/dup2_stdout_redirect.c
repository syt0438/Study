#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    FILE *out = fopen("out", "w");

    if (!out)
    {
        printf("Open file failed: %s\n", strerror(errno));

        return EXIT_FAILURE;
    }

    // 将标准输出 stdout 所对应的描述符重定向到 out 描述符所指向的数据流
    dup2(fileno(out), fileno(stdout));

    fprintf(out, "%s，%s", "有志者事竟成", "苦心人天不负");

    fclose(out);
    out = NULL;

    return EXIT_SUCCESS;
}
