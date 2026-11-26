#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *sum_even(void *arg) {
    int n = *(int *)arg;
    long *res = malloc(sizeof(long));
    *res = 0;
    for (int i = 2; i <= n; i += 2) {
        *res += i;
    }
    return res;
}

int main(void) {
    int n;
    printf("Nhap N: ");
    scanf("%d", &n);

    pthread_t tid;
    pthread_create(&tid, NULL, sum_even, &n);

    void *ret;
    pthread_join(tid, &ret);

    printf("Tong cac so chan tu 1 den %d la: %ld\n", n, *(long *)ret);
    free(ret);
    return 0;
}
