#include<stdio.h>
#include<stdlib.h>

int main()
{
    char cmd[] = "/home/shikuiyang/projects/shell/sftp_download.sh shikuiyang 10.180.8.21 foxconn168 /home/samba/cran_bbu_rru/rru4t4r_zc706adrv9009/FH-20190124-RU4T4R-0D10-122M2018r2/FH-20190124-RU4T4R-0D10.tgz /media/BOOT/DOWN/ 2>&1";
    FILE *f = popen(cmd, "w");
    if (f == NULL) {
        perror("popen()");
        return 1;
    }
    char buf[1024];
    if(fgets(buf, sizeof(buf), f)) {
        printf("buf:%s\n", buf);
    }
    int ret = pclose(f);
    printf("ret: %d\n", ret);
    int status = WEXITSTATUS(ret);
    printf("status: %d\n", status);

    return 0;
}
