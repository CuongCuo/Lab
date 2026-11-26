#include <pthread.h>
#include <stdio.h>

void *print_nums(void *arg) {
    int n = *(int *)arg;
    for (int i = 1; i <= n; i++) {
        printf("%d\n", i);
    }
    return NULL;
}

int main(void) {
    int n;
    printf("Nhap N: ");
    scanf("%d", &n);

    pthread_t tid;
    pthread_create(&tid, NULL, print_nums, &n);
    pthread_join(tid, NULL);

    printf("Main thread exiting.\n");
    return 0;
}
