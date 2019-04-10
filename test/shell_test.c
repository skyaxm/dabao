#include<stdio.h>
#include<stdlib.h>
//#include<sys/wait.h>
//#include<sys/types.h>
int main()
{
    int ret = system("ls");
    if (ret == -1)
    {
        printf("ret = -1\n");
        return -1;
    }
    printf("ret = %d\n", ret);

    if (WIFEXITED(ret))
    {
        int status = WEXITSTATUS(ret);
        printf("exit status: %d\n", status);
    }
    int ret2 = system("");
    printf("ret2: %d\n", ret2);
exit1:
    printf("hello ");
exit2:
    printf("world\n");
    return 0;
}
#if 0
int main(int argc, char *argv[])
{
    char *buf1={"lftp -u shikuiyang, foxconn168 sftp://10.180.8.21 <<EOF"};
    char *buf2={"get helloworld.c\t"};
    int ret = system("./sleep.sh");
    printf("system() ret=%d\n", ret);
    int status = WEXITSTATUS(ret);
    printf("status = %d\n", status);
    if (WIFEXITED(ret))
        printf("very good\n");

    return 0;
}
#endif
