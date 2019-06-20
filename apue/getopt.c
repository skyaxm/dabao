#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    char opt;
    while((opt = getopt(argc, argv, "nb:o::t"))!= -1) {
        printf("opt = %c, optarg = %s, optind = %d, argv[%d] = %s\n",
                opt, optarg, optind, optind, argv[optind] );
    }

    return 0;
}
