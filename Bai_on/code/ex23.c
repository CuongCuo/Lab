#include <pthread.h>
#include <stdio.h>

#define MAX_N 10000000L
#define NUM_THREADS 4

typedef struct {
    long start;
    long end;
    long local_count;
} Task;

void *count_odd(void *arg) {
    Task *t = (Task *)arg;
    long cnt = 0;
    for (long i = t->start; i <= t->end; i++) {
        if (i % 2 != 0) cnt++;
    }
    t->local_count = cnt;
    return NULL;
}

int main(void) {
    pthread_t tids[NUM_THREADS];
    Task tasks[NUM_THREADS];
    long chunk = MAX_N / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        tasks[i].start = i * chunk + 1;
        tasks[i].end = (i == NUM_THREADS - 1) ? MAX_N : (i + 1) * chunk;
        tasks[i].local_count = 0;
        pthread_create(&tids[i], NULL, count_odd, &tasks[i]);
    }

    long total = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tids[i], NULL);
        total += tasks[i].local_count;
    }

    printf("Tong so le tu 1 den %ld la: %ld\n", MAX_N, total);
    return 0;
}
