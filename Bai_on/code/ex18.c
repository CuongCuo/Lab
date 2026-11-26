#include <pthread.h>
#include <stdio.h>

void *worker(void *arg) {
    int id = *(int *)arg;
    printf("Luong %d (TID=%lu): Xin chao!\n", id, (unsigned long)pthread_self());
    return NULL;
}

int main(void) {
    pthread_t tids[3];
    int ids[3] = {1, 2, 3};

    printf("Main thread is running\n");
    for (int i = 0; i < 3; i++) {
        pthread_create(&tids[i], NULL, worker, &ids[i]);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(tids[i], NULL);
    }
    return 0;
}
