#include<stdio.h>
#include<stdlib.h>

int main()
{
	char *buf="10086 20 39 40 54";
	char *endptr;
	int counter=0;
    int i;
	for(i=0;i<5;++i)
	{
		endptr=NULL;
		counter=strtoull(buf,&endptr,10);
		if(counter==0&&endptr==buf)
			printf("error\n");
		printf("%d\n",counter);
        buf=endptr;
	}
}
