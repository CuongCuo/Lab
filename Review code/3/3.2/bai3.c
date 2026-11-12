#include <stdio.h>
#include <stdlib.h>

/*
 * ĐỀ KIỂM TRA GIỮA KỲ - MÃ LỚP: UET.CE2020 8
 * Bài 3: Loại bỏ phần tử có giá trị bằng x bằng con trỏ và cấp phát động
 */

// Hàm loại bỏ các phần tử có giá trị bằng x
// Bắt buộc sử dụng phép toán con trỏ *(a + i) và *(res + k)
int *loaiBoGiaTri(const int *a, int n, int x, int *m) {
    // Bước 1: Đếm số lượng phần tử khác x để cấp phát bộ nhớ chính xác
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (*(a + i) != x) {
            count++;
        }
    }

    // Nếu không có phần tử nào thỏa mãn (tất cả đều bằng x)
    if (count == 0) {
        *m = 0;
        return NULL;
    }

    // Bước 2: Cấp phát động đúng bằng số phần tử giữ lại (count phần tử)
    int *res = (int *)malloc(count * sizeof(int));
    if (res == NULL) {
        *m = 0;
        return NULL;
    }

    // Bước 3: Sao chép các phần tử khác x sang mảng mới bằng phép toán con trỏ
    int idx = 0;
    for (int i = 0; i < n; i++) {
        if (*(a + i) != x) {
            *(res + idx) = *(a + i);
            idx++;
        }
    }

    // Gán số phần tử của mảng mới qua con trỏ m
    *m = count;
    return res;
}

int main() {
    int n, x;
    // Nhập số nguyên n và x
    if (scanf("%d %d", &n, &x) != 2 || n <= 0) {
        return 0;
    }

    // 1. Cấp phát động cho mảng a gồm n phần tử
    int *a = (int *)malloc(n * sizeof(int));
    if (a == NULL) {
        return 1;
    }

    // Nhập dữ liệu cho mảng a
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }

    // 2. Gọi hàm loaiBoGiaTri
    int m = 0;
    int *res = loaiBoGiaTri(a, n, x, &m);

    // 4. In kết quả:
    // Dòng 1: In số phần tử m của mảng kết quả
    printf("%d\n", m);

    // Dòng 2: In m phần tử, nếu m == 0 thì in EMPTY
    if (m == 0 || res == NULL) {
        printf("EMPTY\n");
    } else {
        for (int i = 0; i < m; i++) {
            printf("%d%c", *(res + i), (i == m - 1) ? '\n' : ' ');
        }
    }

    // Giải phóng toàn bộ bộ nhớ động đã cấp phát
    free(a);
    if (res != NULL) {
        free(res);
    }

    return 0;
}

