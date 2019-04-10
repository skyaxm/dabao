#include<stdio.h>
#include<stdlib.h>

int main()
{
    int ret = system("./sleep.sh");
    printf("ret= %d\n", ret);
    return 0;
}
