#include <pthread.h>
#include <stdio.h>

#define LOOPS 1000000
static long counter = 0; // cho biến đếm này ngắn nhất có thể
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // khởi tạo tĩnh 

void *worker(void *arg) {
    for (long i = 0; i < LOOPS; i++) {
        // flow
        pthread_mutex_lock(&mutex); 
        counter++;
        pthread_mutex_unlock(&mutex); // luôn mở khóa khi xong thread
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("Expected: %d | Got: %ld\n", 2 * LOOPS, counter);  // Luôn đúng
    
    return 0;
}