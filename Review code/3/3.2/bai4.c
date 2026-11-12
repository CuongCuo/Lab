#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
 * ĐỀ KIỂM TRA GIỮA KỲ - MÃ LỚP: UET.CE2020 8
 * Bài 4: Quản lý danh sách sinh viên
 */

// Định nghĩa cấu trúc SinhVien
typedef struct {
    char ma[16];   // Mã sinh viên, tối đa 15 ký tự, không chứa khoảng trắng
    float diem;    // Điểm tổng kết (từ 0.0 đến 10.0)
} SinhVien;

// Hàm đếm số sinh viên có điểm tổng kết từ 5.0 trở lên
int demDat(const SinhVien *ds, int n) {
    int dem = 0;
    for (int i = 0; i < n; i++) {
        // Điểm từ 5.0 trở lên (sử dụng sai số epsilon nhỏ 1e-6 để tránh sai số số thực)
        if (ds[i].diem >= 5.0f - 1e-6f) {
            dem++;
        }
    }
    return dem;
}

// Hàm sắp xếp danh sách sinh viên theo yêu cầu:
// - Điểm tổng kết giảm dần
// - Nếu điểm bằng nhau, mã sinh viên theo thứ tự từ điển nhỏ hơn xếp trước
// - KHÔNG sử dụng hàm thư viện qsort() (ở đây sử dụng thuật toán Interchange Sort / Selection Sort)
void sapXepSinhVien(SinhVien *ds, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            // So sánh hai phần tử ds[i] và ds[j]
            // Cần hoán đổi nếu:
            // 1. Điểm của ds[i] nhỏ hơn ds[j] (vì cần giảm dần)
            // 2. Hoặc điểm bằng nhau nhưng mã ds[i] lớn hơn mã ds[j] theo từ điển
            int need_swap = 0;
            if (fabsf(ds[i].diem - ds[j].diem) > 1e-5f) {
                if (ds[i].diem < ds[j].diem) {
                    need_swap = 1;
                }
            } else {
                // Điểm bằng nhau
                if (strcmp(ds[i].ma, ds[j].ma) > 0) {
                    need_swap = 1;
                }
            }

            if (need_swap) {
                SinhVien temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    // Nhập số lượng sinh viên n (1 <= n <= 100)
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0;
    }

    // 1. Cấp phát động mảng gồm n cấu trúc SinhVien
    SinhVien *ds = (SinhVien *)malloc(n * sizeof(SinhVien));
    if (ds == NULL) {
        return 1;
    }

    // Nhập thông tin từng sinh viên
    for (int i = 0; i < n; i++) {
        scanf("%15s %f", ds[i].ma, &ds[i].diem);
    }

    // 2. Đếm số sinh viên đạt (điểm >= 5.0)
    int soDat = demDat(ds, n);

    // 3. Sắp xếp danh sách sinh viên
    sapXepSinhVien(ds, n);

    // In kết quả:
    // Dòng 1: In số sinh viên có điểm từ 5.0 trở lên
    printf("%d\n", soDat);

    // n dòng tiếp theo: In mã sinh viên và điểm tổng kết (1 chữ số thập phân)
    for (int i = 0; i < n; i++) {
        printf("%s %.1f\n", ds[i].ma, ds[i].diem);
    }

    // Giải phóng bộ nhớ đã cấp phát
    free(ds);

    return 0;
}

