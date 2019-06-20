#include<setjmp.h>
#include<stdio.h>

jmp_buf jbuf;

void second()
{
    printf("second\n");
    longjmp(jbuf, 1);
}

void first()
{
    second();
    printf("first\n");
}

int main()
{
    if (!setjmp(jbuf)) {
        first();
    } else {
        printf("main\n");
    }
    return 0;
}
