#include <stdio.h>
#include <stdlib.h>

typedef struct Island
{
    char *name;
    char *opens;
    char *closes;
    struct Island *next;
} Island;

int main()
{
    //#region init data
    Island amity = {"Amity", "09:00", "17:00", NULL};
    Island craggy = {"Craggy", "09:00", "17:00", NULL};
    Island isla_nublar = {"Isla Nublar", "09:00", "17:00", NULL};
    Island shutter = {"Shutter", "09:00", "17:00", NULL};

    amity.next = &craggy;
    craggy.next = &isla_nublar;
    isla_nublar.next = &shutter;
    //#endregion

    //#region loop
    Island *next = &amity;
    int index = 0;

    while (next != NULL)
    {
        printf("[%d]: name: %s, opens: %s, closes: %s\n", ++index, next->name, next->opens, next->closes);

        next = next->next;
    }
    //#endregion

    return 0;
}