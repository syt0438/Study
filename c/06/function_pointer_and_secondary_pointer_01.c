#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 函数指针类型由返回值类型和形参列表决定
// 函数指针类型变量声明格式 👉 返回类型 (*指针变量名)(参数列表)
void find(int argc, char **argv, int (*predicateFn)(char *))
{
    puts("Search results:");
    puts("------------------------------------");

    for (int i = 0; i < argc; i++)
    {
        if (predicateFn(*(argv + i)))
        {
            printf("%s\n", *(argv + i));
        }
    }

    puts("------------------------------------");
}

int sports_no_bieber(char *str)
{
    return strstr(str, "sports") && !strstr(str, "bieber");
}

int main(int argc, char *argv[])
{
    char *ADS[] = {
        "William: SBM GSOH lkes sports, TV, dining",
        "Matt: SWM NS likes art, movies, theater",
        "Luis: SLM ND likes books, theater, art",
        "Mike: DWM DS likes trucks, sports and bieber",
        "Peter: SAM likes chess, working out and art",
        "Josh: SJM likes sports, movies and theater",
        "Jed: DBM likes theater, books and dining"};
    int NUM_ADS = sizeof(ADS) / sizeof(char *);

    find(NUM_ADS, ADS, sports_no_bieber);

    return EXIT_SUCCESS;
}