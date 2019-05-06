#include <stdio.h>
#include <pthread.h>

/* example 2 */
void *ThreadFunc(void *pArg)
{
    int arg = (int)pArg;
    sleep(arg);
    if (arg < 3)
        return (void*)(arg*2);
    else
        pthread_exit((void*)(arg*2));
}

int main()
{
    pthread_t thdId;
    int ret;
    pthread_create(&thdId, NULL, ThreadFunc, (void*)2);
    pthread_join(thdId, (void**)&ret);
    printf("the first thread ret is : %d\n", ret);

    return 0;
}

#if 0
/* example 1 */
void *ThreadFunc(void *pArg)
{
    int i;
    for (i=0; i<10; ++i) {
        printf("Hi, I'm child thread, arg is: %d\n", (int)pArg);
        sleep(1);
    }
    pthread_exit(NULL);
}
int main()
{
    pthread_t thdId;
    pthread_create(&thdId, NULL, ThreadFunc, (void*)123);
    int i;
    for(i=0; i<10; ++i) {
        printf("Hi,I'm main thread, child thread id is:%x\n", thdId);
        sleep(1);
    }
    return 0;
}
#endif

