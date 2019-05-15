#include<stdio.h>
#include<stdlib.h>

int main()
{
    int a=58,b=64;
    printf("%c %c\n", a, b);
    return 0;
}
#if 0
int main()
{
    int a[5][5]={0};
    printf("&a[0][0]=%x\n",&a[0][0]);
    printf("&a[0][0]+1=%x\n",&a[0][0]+1);
    printf("&a[0]+1=%x\n",&a[0]+1);

    int b[5]={0};
    printf("&b[0]=%x\n",&b[0]);
    printf("&b[0]+1=%x\n",&b[0]+1);
    printf("&b+1=%x\n",&b+1);
    return 0;
}
#endif
