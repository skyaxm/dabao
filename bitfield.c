#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

#define MODE_BE

uint8_t buf[]={0x5b,0x59,0x97,0x85};

struct BitField
{
#ifdef MODE_BE
    uint32_t a:1;
    uint32_t b:2;
    uint32_t c:3;
    uint32_t d:4;
    uint32_t e:4;
    uint32_t f:5;
    uint32_t g:6;
    uint32_t h:7;
#else
    uint32_t h:7;
    uint32_t g:6;
    uint32_t f:5;
    uint32_t e:4;
    uint32_t d:4;
    uint32_t c:3;
    uint32_t b:2;
    uint32_t a:1;
#endif
};

int main(int argc,char *argv[])
{
    struct BitField Test;
    memcpy(&Test,buf,sizeof(buf));

    printf("a:%d\n",Test.a);
    printf("b:%d\n",Test.b);
    printf("c:%d\n",Test.c);
    printf("d:%d\n",Test.d);

    return 0;
}
