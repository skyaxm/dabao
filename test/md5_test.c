#include<unistd.h>
#include<openssl/md5.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    char cmd[256];
    sprintf(cmd, "md5sum ./%s 2>&1", argv[1]);
    FILE *f = popen(cmd, "w");
    if (f == NULL) {
        perror("popen()");
    }
    char buf[256];
    while(fgets(buf, sizeof(buf), f)) {
        printf("buf:%s\n", buf);
    }
    pclose(f);
    return 0;
}
#if 0
int main()
{
    int n;
    MD5_CTX c;
    char buf[512];
    ssize_t bytes;
    unsigned char out[MD5_DIGEST_LENGTH];

    MD5_Init(&c);
    bytes = read(STDIN_FILENO, buf, 512);
    while (bytes >0) {
        MD5_Update(&c, buf, bytes);
        bytes = read(STDIN_FILENO, buf, 512);
    }

    MD5_Final(out, &c);
    for (n = 0; n<MD5_DIGEST_LENGTH; n++)
        printf("%02x", out[n]);
    printf("\n");

    return 0;
}
#endif
