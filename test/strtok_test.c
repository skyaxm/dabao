#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define R
int main(int argc, char *argv[])
{
    char str[] = "a/bbb///bb;xxx:yyy:";
    char *token;
    token = strtok(str, ":;");
    if (token != NULL)
        printf("token:%s\n", token);
    while (token) {
        printf("token:%s\n", token);
        token = strtok(NULL, ":;");
    }
#if 0
    char *saveptr;
    char *token = strtok_r(str, ":/", &saveptr);
    while(token) {
        printf("str:%s \ntoken:%s\n saveptr:%s\n", str, token, saveptr);
        token = strtok_r(NULL, ":/", &saveptr);
    }
#endif
    return 0;
}

#if 0
int main(int argc, char *argv[])
{
#ifdef R
    char *str1, *str2, *token, *subtoken;
    char *saveptr1, *saveptr2;
    int j;
    if (argc !=4) {
        fprintf(stderr, "Usage: %s string delim subdelim\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (j=1, str1 = argv[1]; ; j++, str1 = NULL) {
        token = strtok_r(str1, argv[2], &saveptr1);
        if (token == NULL)
            break;
        printf("%d: %s\n", j, token);

        for (str2 = token; ; str2 = NULL) {
            subtoken = strtok_r(str2, argv[3], &saveptr2);
            if (subtoken == NULL)
                break;
            printf(" ---> %s\n", subtoken);
        }
    }
    exit(EXIT_SUCCESS);
#else
    char buf[] = "mo de liang xin: mo ming xin:yinshiming:ruanjianxin";
    char *token = strtok(buf, ":");
    if (token)
        printf("%s\n", token);
    return 0;
#endif
}
#endif
