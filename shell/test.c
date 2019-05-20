#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
    int ret = system("la -l");
    printf("ret:%d\n", ret);
    int status = WEXITSTATUS(ret);
    printf("status:%d\n", status);

    return 0;
}
#if 0
int main(int argc, char *argv[])
{
    char cmd[128];
    char buf[128];
    printf("argv[1]:%s\n", argv[1]);
    sprintf(cmd, "find ./ -name \"%s\"", argv[1]);
    FILE *f = popen(cmd, "r");
    if (f == NULL) {
        perror("popen()");
    }
    while (fgets(buf, sizeof(buf), f)) {
        printf("buf: %s\n", buf);
    }
    pclose(f);
    return 0;
}
#endif

#if 0
int main()
{
//    FILE *f = popen("./test.sh", "r");
    char buf[128];
//    fgets(buf, sizeof(buf), f);
//    printf("%s",buf);
//    pclose(f);
    int ret = system(NULL);
    printf("ret: %d\n", ret);
    if (WIFEXITED(ret)) {
        int status = WEXITSTATUS(ret);
        printf("status: %d\n", status);
    }
    return 0;
}
#endif

#if 0
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
#endif
