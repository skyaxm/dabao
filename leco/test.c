#include<stdio.h>
#include<string.h>

int main()
{
#if 0
    char c='h';
    char buf[10];
    strcat(buf, "hello");
#endif
    int a = 1<<10;
    printf("1<<10 = %d\n", a);

    return 0;
}
