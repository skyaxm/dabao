/**
 * 本程序主要是测试longjmp根据jmp_buf跳转到对应的setjmp处。	
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
 
static jmp_buf exception_env;
static int exception_type;
 
/* This program's output is:
 
calling first
calling second
entering second
second failed with type 3 exception; remapping to type 1.
first failed, exception type 1 
*/
void second(void);

void first(void) 
{
    jmp_buf my_env;
    
    memcpy(my_env, exception_env, sizeof(jmp_buf));
    switch (setjmp(exception_env)) {
		case 0:
            /* normal, desired operation */
			printf("calling second\n");
            second();
            printf("second succeeded\n");  /* not reached */
			break;
        case 3:
            /* if we get here there was an exception. */
            printf("second failed with type 3 exception; remapping to type 1.\n");
            exception_type = 1;
// 			break;
        default: /* fall through */
            memcpy(exception_env, my_env, sizeof(jmp_buf)); /* restore exception stack */
            longjmp(exception_env, exception_type); /* continue handling the exception */
			break;
    }
    memcpy(exception_env, my_env, sizeof(jmp_buf)); /* restore exception stack */
}
 
void second(void) 
{
    printf("entering second\n" ); /* reached */
    exception_type = 3;
    longjmp(exception_env, exception_type); /* declare that the program has failed */
    printf("leaving second\n"); /* not reached */
}
 
int main() 
{
    void *mem_buffer;
 
    mem_buffer = NULL;
    if (setjmp(exception_env)) {
        printf("first failed, exception type %d\n", exception_type);
    } else {
        printf("calling first\n");
        first();
        mem_buffer = malloc(300); /* allocate a resource */
        printf(strcpy((char*) mem_buffer, "first succeeded!")); /* ... this will not happen */
    }
    if (mem_buffer)
        free((void*) mem_buffer); /* carefully deallocate resource */
    return 0;
}
 


