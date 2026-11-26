#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int turn = 0; // 0: lượt Ping, 1: lượt Pong

void *ping_thread(void *arg) {
    (void)arg;
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mtx);
        while (turn != 0) pthread_cond_wait(&cond, &mtx);
        printf("Ping\n");
        turn = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

void *pong_thread(void *arg) {
    (void)arg;
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mtx);
        while (turn != 1) pthread_cond_wait(&cond, &mtx);
        printf("Pong\n");
        turn = 0;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, ping_thread, NULL);
    pthread_create(&t2, NULL, pong_thread, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cond);
    return 0;
}
