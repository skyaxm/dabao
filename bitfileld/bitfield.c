#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

#define MODE_BE //big-endian

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

struct B {
    int a:7;
    int b:3;
};
uint8_t buf[]={0x5b,0x59,0x97,0x85};
/*
 * 0101 1011
 * 0101 1001
 * 1001 0111
 * 1000 0101
 */

/*little-endian's bytes from right to left to struct BitField*/
int main(int argc,char *argv[])
{
#if 1
    struct B b;
    memcpy(&b, buf, sizeof(b));
    printf("B.a:%d\n", b.a);
    printf("B.b:%d\n", b.b);

    b.a = -37;
    b.b = 2;
//    int c = (int)b;
    printf("%x\n", b);
#endif
#if 0
    struct BitField Test;
    printf("size: %d\n", sizeof(struct BitField));
    memcpy(&Test,buf,sizeof(buf));

    printf("a:%d\n",Test.a);
    printf("b:%d\n",Test.b);
    printf("c:%d\n",Test.c);
    printf("d:%d\n",Test.d);
#endif
    return 0;
}
