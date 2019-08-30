#include<stdlib.h>
#include<stdio.h>
#include<time.h>

static void red()
{
    int red[6];
    int value;
    int cnt = 0;
    int i;
    srand((unsigned)time(NULL));
    while(1) {
        int flag = 0;
        value = rand()%33+1;
        if (cnt==6)
            break;
#if 1
        if (cnt == 0) {
            red[cnt++] = value;
        } else {
            for (i=0; i<cnt; ++i) {
                if (red[i] == value) {
                    flag = 1;
                    break;
                }
            }
            if(!flag)
                red[cnt++] = value;
        }
#endif
    }

    printf("red: ");
    for(i=0; i<cnt; ++i)
        printf("%d ", red[i]);
    printf("\n");
}
static void blue()
{
    srand((unsigned)time(NULL));
    int value = rand()%16+1;
    printf("blue: %d\n", value);
}
int main(int argc, char *argv[])
{
    red();
    blue();
    return 0;
}
