#include<stdio.h>
#include<assert.h>

int main(int argc, char *argv[])
{
    int temp = 5;
    assert(temp == 5 && "temp is zero!");
    printf("temp: %d\n", temp);

    return 0;
}
