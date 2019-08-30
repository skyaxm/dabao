#include<stdio.h>
#include<string.h>

static int verify_local_path(const char* pattern, const char* str)
{
    char pstr[256];
    char *end = strchr(str+1, '/');
    if(end != NULL) {
        strncpy(pstr, str, end-str);
		pstr[end-str] = '\0';
    } else {
    	strcpy(pstr, str);
    }

    if(strcmp(pstr, pattern)) {
        printf("local_path out of bounds\n");
        return 1;
    }
    int i;
    for(i = 0; i<strlen(str); ++i) {
        switch(str[i]) {
            case '*':
                printf("find the '*'\n");
                return 2;
            case '?':
                printf("find the '?'\n");
                return 2;
            case '[':
                printf("find the '['\n");
                return 2;
            case ']':
                printf("find the ']'\n");
                return 2;
            default:
                continue;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    char *pattern = "/O-RAN";
    char *str1 = "/O-RAN";
    char *str2 = "/O-RAN/log/syslog.1";
    char *str3 = "/O-RAN/";
    int ret = verify_local_path(pattern, str2);
    if (ret==0) {
        printf("match!\n");
    }else if (ret == 1) {
        printf("out of bonds\n");
    }else {
        printf("find the wildcard\n");
    }
    return 0;
}
