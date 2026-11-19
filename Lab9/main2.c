#include <stdio.h>
#include <pthread.h>

void *greet(void *arg) {
    const char *name = (const char *)arg;
    printf("Hello, %s\n", name);
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    int err;

    err = pthread_create(&t1, NULL, greet, "A");
    if (err != 0) return 1;

    err = pthread_create(&t2, NULL, greet, "B");
    if (err != 0) return 1;

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}