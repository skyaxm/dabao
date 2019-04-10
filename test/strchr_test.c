#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{
    char *str="hello:world";
    char *colonchar=strchr(str,':');
    int len=colonchar-str;
    printf("%d\n",len);
    return 0;
}
