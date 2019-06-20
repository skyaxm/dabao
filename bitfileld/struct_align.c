#include<stdio.h>
#include<stdlib.h>

struct A {
    int a;
    short b;
    char c;
};//size: 8

struct B {
    char a;
    int b;
    short c;
};//size: 12

int main()
{
    printf("A: %d\n", sizeof(struct A));
    printf("B: %d\n", sizeof(struct B));

    return 0;
}
