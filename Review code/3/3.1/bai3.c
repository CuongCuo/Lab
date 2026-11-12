#include <stdio.h>
#include <stdlib.h>

/*
 * ĐỀ KIỂM TRA GIỮA KỲ - MÃ LỚP: UET.CE2020 7
 * Bài 3: Giữ các phần tử lớn hơn ngưỡng x bằng con trỏ và cấp phát động
 */

// Hàm tạo và trả về mảng mới chỉ chứa các phần tử lớn hơn x
// Bắt buộc truy cập phần tử thông qua phép toán con trỏ *(a + i)
int *giuLonHon(const int *a, int n, int x, int *m) {
    // Bước 1: Đếm số lượng phần tử lớn hơn x
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (*(a + i) > x) {
            count++;
        }
    }

    // Nếu không có phần tử nào thỏa mãn
    if (count == 0) {
        *m = 0;
        return NULL;
    }

    // Bước 2: Cấp phát động đúng bằng số lượng phần tử thỏa mãn (count phần tử)
    int *res = (int *)malloc(count * sizeof(int));
    if (res == NULL) {
        *m = 0;
        return NULL;
    }

    // Bước 3: Sao chép các phần tử lớn hơn x vào mảng mới bằng phép toán con trỏ
    int idx = 0;
    for (int i = 0; i < n; i++) {
        if (*(a + i) > x) {
            *(res + idx) = *(a + i);
            idx++;
        }
    }

    // Trả về số lượng phần tử qua con trỏ m
    *m = count;
    return res;
}

int main() {
    int n, x;
    // Nhập hai số nguyên n và x
    if (scanf("%d %d", &n, &x) != 2 || n <= 0) {
        return 0;
    }

    // 1. Cấp phát động mảng a gồm n phần tử
    int *a = (int *)malloc(n * sizeof(int));
    if (a == NULL) {
        return 1;
    }

    // Nhập dữ liệu mảng a bằng con trỏ
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }

    // 2. Gọi hàm giuLonHon
    int m = 0;
    int *res = giuLonHon(a, n, x, &m);

    // In kết quả:
    // Dòng 1: In số phần tử m
    printf("%d\n", m);

    // Dòng 2: In m phần tử, nếu không có phần tử nào thỏa mãn (m == 0) thì in EMPTY
    if (m == 0 || res == NULL) {
        printf("EMPTY\n");
    } else {
        for (int i = 0; i < m; i++) {
            printf("%d%c", *(res + i), (i == m - 1) ? '\n' : ' ');
        }
    }

    // 4. Giải phóng toàn bộ bộ nhớ đã cấp phát
    free(a);
    if (res != NULL) {
        free(res);
    }

    return 0;
}

