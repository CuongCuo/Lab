#include <pthread.h>
#include <stdio.h>

#define BUF_SIZE 5
#define TOTAL_ITEMS 10

int buffer[BUF_SIZE];
int count = 0, in = 0, out = 0;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    (void)arg;
    for (int i = 1; i <= TOTAL_ITEMS; i++) {
        pthread_mutex_lock(&mtx);
        while (count == BUF_SIZE) {
            pthread_cond_wait(&not_full, &mtx); // Chờ nếu buffer đầy
        }
        buffer[in] = i * 10;
        in = (in + 1) % BUF_SIZE;
        count++;
        printf("[Producer] Them: %d (count=%d)\n", i * 10, count);
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

void *consumer(void *arg) {
    (void)arg;
    for (int i = 1; i <= TOTAL_ITEMS; i++) {
        pthread_mutex_lock(&mtx);
        while (count == 0) {
            pthread_cond_wait(&not_empty, &mtx); // Chờ nếu buffer rỗng
        }
        int item = buffer[out];
        out = (out + 1) % BUF_SIZE;
        count--;
        printf("[Consumer] Lay:  %d (count=%d)\n", item, count);
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main(void) {
    pthread_t prod, cons;
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);
    return 0;
}
