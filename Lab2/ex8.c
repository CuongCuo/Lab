#include <stdio.h>

int main() {
    int n;
    printf("Nhap so luong phan tu n: ");
    scanf("%d", &n);

    int a[n];
    long long tich = 1;

    for (int i = 0; i < n; i++) {
        printf("Nhap a[%d]: ", i);
        scanf("%d", &a[i]);// nhap tung phan tu -> gan vao mang
        tich *= a[i];
    }

    printf("Tich cac phan tu trong mang la: %lld\n", tich); // % long long decimal

    return 0;
}
