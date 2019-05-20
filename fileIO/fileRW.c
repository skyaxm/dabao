#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

//#define S
int main()
{
    char buf[1024];
    int rnt = 0;
    memset(buf, 0, sizeof(buf));
#ifdef S
    printf("alala: %c: %c: %c\n", buf[256], buf[512], buf[1023]);
    int fd = open("./test.txt", O_RDWR);

/*
    while (rnt = read(fd, buf, 9)) {
        printf("rnt: %d\n", rnt);
        printf("%s\n", buf);
        int ret = strlen(buf);
        printf("ret: %d\n", ret);
    }
    */
    rnt = read(fd, buf, 9);
    printf("%s\n", buf);
    int ret = strlen(buf);
    printf("buf len: %d\n", ret);
    printf("alala: %c: %c: %c\n", buf[256], buf[512], buf[1023]);
    close(fd);
#else
    FILE *f = fopen("/home/shikuiyang/dabao/fileIO/test2.txt", "r+");
    if (f == NULL)
        printf("open the file falied\n");

    rnt = fread(buf, 1, sizeof(buf), f);
    if (rnt == 0) {
        printf("fread() failed!\n");
    }
    printf("rnt:%d\n", rnt);
    int len = strlen(buf);
    printf("buf len:%d\n", len);
    printf("%s", buf);
//    while (rnt = fread(buf, sizeof(buf), 1, f)) {
//        printf("rnt: %d\n", rnt);
//        printf("%s\n", buf);
//    }
//    fwrite("hello", 5, 1, f);
//    fflush(f);
    fclose(f);
//    printf("%s", buf);
#endif
    return 0;
}
