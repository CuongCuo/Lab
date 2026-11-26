#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *calc_sum(void *arg) {
    int n = *(int *)arg;
    long *sum = malloc(sizeof(long));
    *sum = 0;
    for (int i = 1; i <= n; i++) {
        *sum += i;
    }
    return sum;
}

int main(void) {
    int n;
    printf("Nhap N: ");
    scanf("%d", &n);

    pthread_t tid;
    pthread_create(&tid, NULL, calc_sum, &n);

    void *res;
    pthread_join(tid, &res);

    printf("Tong tu 1 den %d la: %ld\n", n, *(long *)res);
    free(res);
    return 0;
}
