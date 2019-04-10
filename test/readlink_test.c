#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>

int main(int argc,char* argv[])
{
    struct stat sb;
    char *linkname;
    ssize_t r;
    char buf[100];

    r = readlink("/usr/bin/play", buf, sizeof(buf));
#if 0
    if (argc != 2)
    {
        fprintf(stderr,"Usage: %s <pathname>\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    if (lstat(argv[1],&sb) == -1)
    {
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    linkname = malloc(sb.st_size + 1);
//    r = readlink(argv[1], linkname, sb.st_size + 1);
    if(r==-1)
    {
        perror("lstat");
        exit(EXIT_FAILURE);
    }
//    if (r>sb.st_size)
//    {
//        fprintf(stderr,"symlink incresed in size between lstat() and readlink()\n");
//        exit(EXIT_FAILURE);
//    }
#endif
    buf[r] = '\0';
    printf(" '/proc/self/exe' points to '%s' \n", buf);

    exit(EXIT_SUCCESS);
}
