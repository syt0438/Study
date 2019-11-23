#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Response_type
{
    DUMP,
    SECOND_CHANCE,
    MARRIAGE,
    FAILURE
};

typedef struct
{
    char *name;
    enum Response_type type;
} Response;

typedef struct
{
    enum Response_type type;
    void (*handleMethod)(Response);
} HandlerMapping;

//#region business method
void dump(Response r)
{
    printf("Dear %s,\n", r.name);
}
void second_chance(Response r)
{
    printf("Dear %s,\n", r.name);
}
void marriage(Response r)
{
    printf("Dear %s,\n", r.name);
}
//#endregion

int handle(Response *item)
{
    HandlerMapping handlerMappings[] = {{DUMP, dump}, {SECOND_CHANCE, second_chance}, {MARRIAGE, marriage}};
    size_t len = sizeof(handlerMappings) / sizeof(HandlerMapping);

    for (size_t i = 0; i < len; i++)
    {
        HandlerMapping handlerMapping = handlerMappings[i];

        if (handlerMapping.type == item->type)
        {
            handlerMapping.handleMethod(*item);

            return 1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    Response list[] = {{"Mike", DUMP}, {"Luis", SECOND_CHANCE}, {"Bob", FAILURE}, {"Matt", SECOND_CHANCE}, {"William", MARRIAGE}};
    size_t len = sizeof(list) / sizeof(Response);

    for (size_t i = 0; i < len; i++)
    {
        Response item = list[i];

        int ret = handle(&item);

        printf("[%s, %d] 👉  Handle %s \n", item.name, item.type, ret ? "Success" : "Failure");
    }

    return EXIT_SUCCESS;
}
