#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    FILE *f = popen("cd /home/shikuiyang/dabao/sftp/ && tar -c *", "r");
    FILE *file = fopen("./log", "w+");
    char buf[256*1024];
    memset(buf, 0, sizeof(buf));
    int cnt = 0;
    cnt = fread(buf, 1, sizeof(buf), f);
    printf("cnt:%d\n", cnt);
//    printf("%s\n", buf);
    int i;
//    for (i; i<cnt; ++i) {
//        printf("%c", buf[i]);
//        if (buf[i] == '\0') {
//            printf("the %d char is null\n", i);
//            break;
//        }
//    }
    int wcnt = fwrite(buf, 1, cnt, file);
    printf("wcnt: %d\n", wcnt);
//    while((cnt = fread(buf, sizeof(buf), 1, f))&& line) {
//        puts(buf);
//        line--;
//        //        printf("%s", buf);
//        fwrite(buf, cnt, 1, file);
//    }
#if 0
    FILE *f2 = popen("tar -x /home/shikuiyang/dabao/log -C /home/shikuiyang/dabao/", "w");
    if (f2 == NULL)
        printf("oh, wan dan\n");
    fread(buf, sizeof(buf), 1, f2);
    puts(buf);
    pclose(f2);
#endif
    pclose(f);
    fclose(file);
    return 0;
}

