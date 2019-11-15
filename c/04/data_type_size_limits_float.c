#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>

/*
    limits.h: 含有表示整型（比如 int 和 char）大小的值
    float.h: 含有表示 float 和 double 类型大小的值
*/
int main(int argc, char *argv[])
{
    printf("The value of CHAR_MAX is %i\n", CHAR_MAX);
    printf("The value of CHAR_MIN is %i\n", CHAR_MIN);
    printf("An char takes %d bytes\n", sizeof(char));

    printf("The value of SHRT_MAX is %i\n", SHRT_MAX);
    printf("The value of SHRT_MIN is %i\n", SHRT_MIN);
    printf("An short takes %d bytes\n", sizeof(short));

    printf("The value of INT_MAX is %i\n", INT_MAX);
    printf("The value of INT_MIN is %i\n", INT_MIN);
    printf("An int takes %d bytes\n", sizeof(int));

    printf("The value of LONG_MAX is %li\n", LONG_MAX);
    printf("The value of LONG_MIN is %li\n", LONG_MIN);
    printf("An long takes %d bytes\n", sizeof(long));

    printf("The value of FLT_MAX is %f\n", FLT_MAX);
    printf("The value of FLT_MIN is %.50f\n", FLT_MIN);
    printf("A float takes %d bytes\n", sizeof(float));

   printf("The value of DBL_MAX is %f\n", DBL_MAX);
    printf("The value of DBL_MIN is %.50f\n", DBL_MIN);
    printf("A double takes %d bytes\n", sizeof(double));

    return EXIT_SUCCESS;
}