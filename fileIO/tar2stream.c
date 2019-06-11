#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
//    FILE *f = popen("cd /home/shikuiyang/dabao/ && tar -c ./sftp/", "r");
    FILE *f = popen("tar -c /home/shikuiyang/dabao/sftp/", "r");
    FILE *file = fopen("./log", "w+");
    char buf[256*1024];
    memset(buf, 0, sizeof(buf));
    int cnt = 0;
    cnt = fread(buf, 1, sizeof(buf), f);
    printf("cnt:%d\n", cnt);
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

    pclose(f);
    fclose(file);
    return 0;
}

