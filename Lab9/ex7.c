#include <stdio.h>
#include <pthread.h>

#define LOOP 1000000
long counter = 0;
// tao 2 thread, pthread_t t1, t2

void *work(void *arg){
    (void)arg;
    for(int i = 0; i < LOOP; i ++){
        counter ++;
    }
    return NULL;
}

int main(void){
    pthread_t t1,t2;
    pthread_create(&t1, NULL, work, NULL);
    pthread_create(&t2, NULL, work, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Mong doi: %d\n", 2 * LOOP);
    printf("Thuc te :%ld\n", counter);
    return 0;
    
}