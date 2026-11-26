#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define DATA_SIZE 100000
#define BINS 256
#define NUM_THREADS 4

int data[DATA_SIZE];

typedef struct {
    int start;
    int end;
    long local_hist[BINS];
} HistTask;

void *calc_hist(void *arg) {
    HistTask *t = (HistTask *)arg;
    for (int i = 0; i < BINS; i++) t->local_hist[i] = 0;

    for (int i = t->start; i < t->end; i++) {
        t->local_hist[data[i]]++;
    }
    return NULL;
}

int main(void) {
    // Khởi tạo mảng pixel ngẫu nhiên từ 0..255
    for (int i = 0; i < DATA_SIZE; i++) {
        data[i] = rand() % BINS;
    }

    pthread_t tids[NUM_THREADS];
    HistTask tasks[NUM_THREADS];
    int chunk = DATA_SIZE / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        tasks[i].start = i * chunk;
        tasks[i].end = (i == NUM_THREADS - 1) ? DATA_SIZE : (i + 1) * chunk;
        pthread_create(&tids[i], NULL, calc_hist, &tasks[i]);
    }

    long final_hist[BINS] = {0};
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tids[i], NULL);
        for (int b = 0; b < BINS; b++) {
            final_hist[b] += tasks[i].local_hist[b];
        }
    }

    // In thử 10 giá trị đầu tiên của histogram
    for (int b = 0; b < 10; b++) {
        printf("Gia tri %3d: %ld lan\n", b, final_hist[b]);
    }
    return 0;
}
