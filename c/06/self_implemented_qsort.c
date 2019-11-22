#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 通过异或交换两个元素中每个字节的值，以完成两个元素的值交换
void swap(void *a, void *b, size_t ele_size)
{
    while (ele_size > 0)
    {
        ele_size--;

        *((char *)a + ele_size) ^= *((char *)b + ele_size);
        *((char *)b + ele_size) ^= *((char *)a + ele_size);
        *((char *)a + ele_size) ^= *((char *)b + ele_size);
    }
}

void sort(void *list, size_t len, size_t ele_size, int (*compareFn)(const void *, const void *))
{
    for (size_t i = 0; i < len - 1; i++)
    {
        for (size_t j = 0; j < len - 1 - i; j++)
        {
            void *a = (char *)list + (j * ele_size);
            void *b = (char *)list + ((j + 1) * ele_size);

            if (compareFn(a, b) > 0)
            {
                swap(a, b, ele_size);
            }
        }
    }
}

typedef struct
{
    long id;
    char *username;
    char *nickname;
} User;

int compareInt(const void *ao, const void *bo)
{
    int *a = (int *)ao;
    int *b = (int *)bo;

    return *a - *b;
}

int compareString(const void *ao, const void *bo)
{
    char **a = (char **)ao;
    char **b = (char **)bo;

    return strcmp(*a, *b);
}

int compareUsername(const void *ao, const void *bo)
{
    User *a = (User *)ao;
    User *b = (User *)bo;

    return strcmp(a->username, b->username);
}

int main(int argc, char *argv[])
{
    int number_list[] = {543, 323, 32, 554, 11, 1, 21};
    int number_list_len = sizeof(number_list) / sizeof(int);

    char *msg_list[] = {
        "William: SBM GSOH likes sports, TV, dining",
        "Matt: SWM NS likes art, movies, theater",
        "Luis: SLM ND likes books, theater, art",
        "Mike: DWM DS likes trucks, sports and bieber",
        "Peter: SAM likes chess, working out and art",
        "Aosh: SJM likes sports, movies and theater",
        "Jed: DBM likes theater, books and dining"};
    int msg_list_len = sizeof(msg_list) / sizeof(char *);

    User data_list[] = {{.username = "William"}, {.username = "Matt"}, {.username = "Luis"}, {.username = "Mike"}, {.username = "Peter"}, {.username = "Aosh"}, {.username = "Jed"}};
    int data_list_len = sizeof(data_list) / sizeof(User);

    sort(number_list, number_list_len, sizeof(int), compareInt);
    sort(msg_list, msg_list_len, sizeof(char *), compareString);
    sort(data_list, data_list_len, sizeof(User), compareUsername);

    printf("Test number sort start 👉\n");

    for (size_t i = 0; i < number_list_len; i++)
    {
        printf("[%d]: %d\n", i + 1, number_list[i]);
    }

    printf("Test number sort end 👈\n");

    printf("\n");

    printf("Test string sort start 👉\n");

    for (size_t i = 0; i < msg_list_len; i++)
    {
        printf("[%d]: %s\n", i + 1, msg_list[i]);
    }

    printf("Test string sort end 👈\n");

    printf("\n");

    printf("Test username sort start 👉\n");

    for (size_t i = 0; i < data_list_len; i++)
    {
        printf("[%d]: %s\n", i + 1, data_list[i].username);
    }

    printf("Test username sort end 👈\n");

    return EXIT_SUCCESS;
}
