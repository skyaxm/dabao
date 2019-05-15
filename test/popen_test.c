#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main()
{
//    char *md5sum_cmd = "md5sum /media/BOOT/slot2/uImage 2>&1 | cut -d' ' -f1 | cut -b1-6";
    char *md5sum_cmd = "md5sum /media/BOOT/slot2/uImage 2>&1";
    FILE *f = popen(md5sum_cmd, "r");
    if (f == NULL) {
        perror("popen()");
    }
    char buf[512];
    fgets(buf, 7, f);
    printf("buf: %s\n", buf);
    int ret = pclose(f);
    int status = WEXITSTATUS(ret);
    printf("exit status: %d\n", status);

    return 0;
}
#if 0
int main()
{
    char cmd[] = "/home/shikuiyang/projects/shell/sftp_download.sh shikuiyang 10.180.8.21 foxconn168 /home/samba/cran_bbu_rru/rru4t4r_zc706adrv9009/FH-20190124-RU4T4R-0D10-122M2018r2/FH-20190124-RU4T4R-0D10.tgz /media/BOOT/DOWN/";
    FILE *f = popen(cmd, "r");
    if (f == NULL) {
        perror("popen()");
        return 1;
    }
    char buf[1024];
    while(fgets(buf, sizeof(buf), f)) {
        printf("buf:%s", buf);
    }
    int ret = pclose(f);
    printf("ret: %d\n", ret);
    int status = WEXITSTATUS(ret);
    printf("status: %d\n", status);

    return 0;
}
#endif
