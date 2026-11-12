#include <stdio.h>


// Hàm đếm số lượng phần tử có giá trị lớn hơn 0
// Nhận vào mảng a (hằng) và số phần tử n
int demSoDuong(const int a[], int n) {
    int dem = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            dem++;
        }
    }
    return dem;
}

// Hàm tính tổng các phần tử có giá trị lớn hơn 0
// Nhận vào mảng a (hằng) và số phần tử n, trả về kiểu long long để tránh tràn số
long long tongSoDuong(const int a[], int n) {
    long long tong = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
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
    int dem = demSoDuong(a, n);
    long long tong = tongSoDuong(a, n);

    // In kết quả: số lượng và tổng cách nhau bởi 1 khoảng trắng
    // Nếu không có số dương nào thì dem = 0, tong = 0 -> in "0 0" theo đúng yêu cầu
    printf("%d %lld\n", dem, tong);

    return 0;
}

