#include<stdio.h>
#include<stdlib.h>

int main()
{
	char* counter_names_array[] = {
        "in-octets",
        "in-unicast-pkts",
        "in-errors",
        "in-discards",
        NULL/*"in-fifo"*/,
        NULL/*"in-frames"*/,
        NULL/*in-compressed*/,
        "in-multicast-pkts",
        "out-octets",
        "out-unicast-pkts",
        "out-errors",
        "out-discards",
        NULL/*"out-fifo"*/,
        NULL/*out-collisions*/,
        NULL/*out-carrier*/,
        NULL/*out-compressed*/
    };
	int i=sizeof(counter_names_array)/sizeof(char*);
	printf("%d\n",i);
}
