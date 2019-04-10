#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
    int ret=system("./test.sh 1 2");
    if(ret == -1)
        printf("holy shit\n");

    if(WIFEXITED(ret))
    {
        int status = WEXITSTATUS(ret);
        printf("status: %d\n", status);
    }
    return 0;
}
