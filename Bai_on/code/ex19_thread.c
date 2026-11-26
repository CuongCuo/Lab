#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sharedVar = 5; // Dùng chung giữa các luồng

void *threadFunc(void *arg) {
    (void)arg;
    sharedVar = 20;
    printf("Thread: sharedVar = %d\n", sharedVar);
    return NULL;
}

int main(void) {
    pthread_t thread;
    pthread_create(&thread, NULL, threadFunc, NULL);
    pthread_join(thread, NULL);

    // Kết quả: sharedVar = 20 vì các luồng dùng chung vùng nhớ toàn cục (data segment)
    printf("Main: sharedVar = %d\n", sharedVar);
    return 0;
}
