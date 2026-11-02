#include <stdio.h>
#include <stdlib.h>
int main() {
    int n, m;
    printf("Nhap so pt mang 1: ");
    scanf("%d", &n);
    printf("Nhap so pt mang 2: ");
    scanf("%d", &m);
    int *arr1 = (int*) malloc(n * sizeof(int));
    int *arr2 = (int*) malloc(m * sizeof(int));
    if (arr1 == NULL || arr2 == NULL) {
        printf("Loi cap phat bo nho!\n");
        return 1;
    }
    printf("Nhap %d phan tu cho mang 1:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr1[i]);
    printf("Nhap %d phan tu cho mang 2:\n", m);
    for (int i = 0; i < m; i++) scanf("%d", &arr2[i]);
    
    int new_size = n + m;
    int *arr3 = (int*) malloc(new_size * sizeof(int));
    if (arr3 == NULL) {
        printf("Loi cap phat bo nho cho mang 3!\n");
        free(arr1);
        free(arr2);
        return 1;
    }
// nua dau
    for (int i = 0; i < n; i++) arr3[i] = arr1[i];
// nua sau 
    for (int i = 0; i < m; i++) arr3[n + i] = arr2[i];
    // 7. In mảng kết quả
    printf("\nMang sau khi gop (%d phan tu):\n", new_size);
    for (int i = 0; i < new_size; i++) {
        printf("%d ", arr3[i]);
    }
    printf("\n");
    // 8. Giải phóng toàn bộ bộ nhớ đã cấp phát
    free(arr1);
    free(arr2);
    free(arr3);
    return 0;
}
