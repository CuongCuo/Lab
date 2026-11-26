#include <pthread.h>
#include <stdio.h>

int counter = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *inc_thread(void *arg) {
    (void)arg;
    for (int i = 0; i < 100; i++) {
        pthread_mutex_lock(&mtx);
        counter++;
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

void *dec_thread(void *arg) {
    (void)arg;
    for (int i = 0; i < 50; i++) {
        pthread_mutex_lock(&mtx);
        counter--;
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, inc_thread, NULL);
    pthread_create(&t2, NULL, dec_thread, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Gia tri counter cuoi cung: %d\n", counter);
    pthread_mutex_destroy(&mtx);
    return 0;
}
