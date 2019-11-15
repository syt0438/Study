#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *findValue(char *list[], size_t len, const char *str)
{
    for (size_t i = 0; i < len; i++)
    {
        char *item = list[i];

        char *ret = strstr(item, str);

        if (ret != NULL)
        {
            return item;
        }
    }
}

int main()
{
    char *list[] = {
        "I left my heart in Harvard Med School",
        "Newark, Newark - a wonderful town",
        "Dancing with a Dork",
        "From here to maternity",
        "The girl from Iwo Jima",
    };

    char *ret = findValue(list, sizeof(list), "with");

    printf("result: %s\n", ret);

    return EXIT_SUCCESS;
}