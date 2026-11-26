#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_SIZE 100000
#define NUM_THREADS 4

char *arr[ARR_SIZE];
const char *target = "item_54321";

atomic_int found = 0;       // Biến cờ dừng sớm
int found_idx = -1;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int id;
    int start;
    int end;
} SearchTask;

void *search_chunk(void *arg) {
    SearchTask *t = (SearchTask *)arg;
    for (int i = t->start; i < t->end; i++) {
        if (atomic_load(&found)) break; // Có luồng khác tìm thấy -> dừng sớm

        if (strcmp(arr[i], target) == 0) {
            pthread_mutex_lock(&mtx);
            if (!atomic_load(&found)) {
                atomic_store(&found, 1);
                found_idx = i;
                printf("Thread %d tim thay '%s' tai vi tri %d!\n", t->id, target, i);
            }
            pthread_mutex_unlock(&mtx);
            break;
        }
    }
    return NULL;
}

int main(void) {
    // Khởi tạo mảng chuỗi mẫu
    for (int i = 0; i < ARR_SIZE; i++) {
        arr[i] = malloc(20);
        snprintf(arr[i], 20, "item_%d", i);
    }

    pthread_t tids[NUM_THREADS];
    SearchTask tasks[NUM_THREADS];
    int chunk = ARR_SIZE / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        tasks[i].id = i + 1;
        tasks[i].start = i * chunk;
        tasks[i].end = (i == NUM_THREADS - 1) ? ARR_SIZE : (i + 1) * chunk;
        pthread_create(&tids[i], NULL, search_chunk, &tasks[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tids[i], NULL);
    }

    if (found_idx == -1) printf("Khong tim thay '%s'.\n", target);

    for (int i = 0; i < ARR_SIZE; i++) free(arr[i]);
    pthread_mutex_destroy(&mtx);
    return 0;
}
