#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 4

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int arrived = 0;

void *barrier_worker(void *arg) {
    int id = *(int *)arg;

    printf("Thread %d reached the barrier\n", id);

    pthread_mutex_lock(&mtx);
    arrived++;
    if (arrived == NUM_THREADS) {
        printf("All threads reached the barrier! Releasing them...\n");
        pthread_cond_broadcast(&cond); // Đánh thức tất cả các luồng đang chờ
    } else {
        while (arrived < NUM_THREADS) {
            pthread_cond_wait(&cond, &mtx);
        }
    }
    pthread_mutex_unlock(&mtx);

    printf("Thread %d passed the barrier\n", id);
    return NULL;
}

int main(void) {
    pthread_t tids[NUM_THREADS];
    int ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i + 1;
        pthread_create(&tids[i], NULL, barrier_worker, &ids[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tids[i], NULL);
    }

    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cond);
    return 0;
}
