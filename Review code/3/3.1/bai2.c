#include <stdio.h>

/*
 * ĐỀ KIỂM TRA GIỮA KỲ - MÃ LỚP: UET.CE2020 7
 * Bài 2: Đếm số lượng và tính tổng các phần tử chẵn trong mảng
 * Lưu ý: Số 0 và các số nguyên âm chẵn đều được tính là số chẵn.
 */

// Hàm đếm số phần tử có giá trị chẵn trong mảng
int demSoChan(const int a[], int n) {
    int dem = 0;
    for (int i = 0; i < n; i++) {
        // Trong C, phép toán % 2 == 0 đúng với cả số chẵn dương, số 0 và số chẵn âm
        // Ví dụ: (-4) % 2 == 0, 0 % 2 == 0, 2 % 2 == 0
        if (a[i] % 2 == 0) {
            dem++;
        }
    }
    return dem;
}

// Hàm tính tổng các phần tử có giá trị chẵn trong mảng
long long tongSoChan(const int a[], int n) {
    long long tong = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) {
            tong += a[i];
        }
    }
    return tong;
}

int main() {
    int n;
    // Nhập số lượng phần tử n (1 <= n <= 100)
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0;
    }

    int a[105];
    // Nhập n số nguyên của mảng a
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // Gọi các hàm xử lý
    int dem = demSoChan(a, n);
    long long tong = tongSoChan(a, n);

    // In kết quả: số lượng và tổng cách nhau bởi 1 dấu cách
    // Nếu không có phần tử chẵn thì dem = 0, tong = 0 -> in "0 0" đúng yêu cầu
    printf("%d %lld\n", dem, tong);

    return 0;
}

