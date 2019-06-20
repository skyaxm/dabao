#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct A {
    int a:5;
    int b:3;
};

int main()
{
    struct A test;
    char str[]="013455674ahdeyuqwwbf";
    memcpy(&test, str, sizeof(test));
    printf("test.a:%d\n", test.a);
    printf("test.b:%d\n", test.b);

    return 0;
}
