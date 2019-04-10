#include<stdio.h>
#include<stdlib.h>
//#include<sys/types.h>
#include<sys/wait.h>

int main(int argc, char *argv[])
{
    int ret=system("./sftp_download.sh shikuiyang 10.180.8.21 foxconn168 /home/shikuiyang/helloworld.c");
    if (ret == -1)
    {
        printf("can't run the shell script\n");
        return -1;
    }
    if (WIFEXITED(ret))
    {
        int status = WEXITSTATUS(ret);
        printf("status: %d\n", status);
    }
    return 0;
}
