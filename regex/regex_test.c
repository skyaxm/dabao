#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

int match_regex(const char* pattern, const char* str)
{
    int ret = 0;
    regex_t regex;
    char buf[1024];
    int regex_init = regcomp(&regex, pattern, REG_EXTENDED);
    if (regex_init) {
        printf("regcomp() failed\n");
        regerror(regex_init, &regex, buf, 1024);
        printf("%s\n", buf);
    } else {
        int reti = regexec(&regex, str, 0, NULL, 0);
        if (reti) {
            printf("'%s' not match\n", str);
        } else {
            ret = 1;
        }
    }
    regfree(&regex);
    return ret;
}

int main(int argc, char *argv[])
{
    char *pattern = "^/O-RAN*";
    char *pattern1 = "windows(\?=95|98NT)";
    char *pattern2 = "^(?:.*\\d)(?=.*[a-z])$";
    char *pattern3 = "^/O-RAN[^OoRA]";

    char *str1 = "/O-RAN";
    char *str2 = "/O-RAN/*.log";
    char *str3 = "/O-ran/";
 //   char *str4 = "start test"; //no match
//    char *str4 = "Start test"; //no match
    char *str4 = "StartTest";

    int ret = match_regex(pattern2, str4);
    if(ret) {
        printf("the '%s' match the regex\n", str4);
    }
#if 1
    ret = match_regex(pattern3, str1);
    if (ret) {
        printf("the %s regex match!\n", str1);
    }

    ret = match_regex(pattern3, str2);
    if (ret) {
        printf("the %s regex match!\n", str2);
    }

    ret = match_regex(pattern3, str3);
    if (ret) {
        printf("the %s regex match!\n", str3);
    }
#endif
    return 0;
}
