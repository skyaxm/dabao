#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

int main()
{
    printf("abc\n123");
    printf("abc");
//    *(int*)0 = 0;
    int a = 123;
    printf("%p\n", &a);
    while(1)
    {

    }

//    return 0;
}
#if 0
int main()
{
    char *cmd = NULL;
    int ret = system(cmd);
    printf("status: %d\n", WEXITSTATUS(ret));
    const char *status = NULL;
    status = "ha ha ha ~";
    puts(status);
    status = "mei xiang da ba!";
    puts(status);

    return 0;
}
#endif

#if 0
int main(int argc, char *argv[])
{
    char cmd[256];
    char file[64] = "myslot.tgz";
    extern int errno;
    char buf[1024];

//    sprintf(cmd, "tar -xvzf %s", argv[1]);
    sprintf(cmd, "md5sum %s 2>&1 | cut -f1", argv[1]);

    FILE *f;
    f = popen(cmd, "r");
    while(fgets(buf, sizeof(buf), f)) {
        printf("buf:%s\n", buf);
//        system("")
    }
//    puts(buf);
    int status =pclose(f);
    status = WEXITSTATUS(status);
    printf("status = %d\n", status);
    system("rm -rf myslot");
    return 0;
}
#endif

#if 0
    int ret = system(cmd);
    if (ret !=0) {
        printf("errno = %d\n", errno);

        char *mesg = strerror(errno);
        printf("errno:%s\n", mesg);
    }
    printf("ret = %d\n", ret);
    int status = WEXITSTATUS(ret);
    printf("status = %d\n", status);
#endif

#if 0
int main()
{
//    int ret = ispunct('a');
    int ret = iscntrl('/');
    printf("ret = %d\n",ret);
    return 0;
}
#endif
# if 0
char * itoa(int i);
int main(int argc,char *argv[])
{
    int loglevel[4];
	FILE *fp=fopen("/proc/sys/kernel/printk","r");
    fscanf(fp,"%d%d%d%d",&loglevel[0],&loglevel[1],&loglevel[2],&loglevel[3]);
    printf("%c %c %c %c\n",loglevel[0]+48,loglevel[1]+48,loglevel[2]+48,loglevel[3]+48);

    return 0;
#endif
#if 0
    char str[64];
    fgets(str,sizeof(str),fp);
    puts(str);

    fprintf(fp,"%d",7);
	return 0;
}
#endif
