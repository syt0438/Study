#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Island
{
    char *name;
    char *opens;
    char *closes;
    struct Island *next;
} Island;

Island *create(char *name)
{
    Island *i = malloc(sizeof(Island));

    i->name = strdup(name);
    i->opens = "09:00";
    i->closes = "17:00";
    i->next = NULL;

    return i;
}

int main()
{
    //#region init data
    Island *amity = create("Amity");
    Island *craggy = create("Craggy");
    Island *isla_nublar = create("Isla nublar");
    Island *shutter = create("Shutter");

    amity->next = craggy;
    craggy->next = isla_nublar;
    isla_nublar->next = shutter;
    //#endregion

    //#region loop
    Island *next = amity;
    int index = 0;

    Island *current = NULL;
    while (next != NULL)
    {
        printf("[%d]: name: %s, opens: %s, closes: %s\n", ++index, next->name, next->opens, next->closes);

        current = next;
        next = next->next;

        free((void *)current->name);
        free((void *)current);
    }
    //#endregion

    return 0;
}