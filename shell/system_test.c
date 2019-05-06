#include<stdio.h>

int main(int argc, char *argv[])
{
    int ret = system("sleep 5");
    printf("ret=%d\n",ret);
    return 0;
}
