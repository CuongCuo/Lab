#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * ĐỀ KIỂM TRA GIỮA KỲ - MÃ LỚP: UET.CE2020 7
 * Bài 4: Quản lý danh sách sản phẩm trong kho hàng
 */

// Định nghĩa cấu trúc SanPham
typedef struct {
    char ma[16];   // Mã sản phẩm, tối đa 15 ký tự, không chứa khoảng trắng
    int soLuong;   // Số lượng sản phẩm hiện có trong kho (số nguyên không âm)
} SanPham;

// Hàm đếm số sản phẩm cần nhập thêm hàng (số lượng < ngưỡng k)
int demCanNhap(const SanPham *ds, int n, int k) {
    int dem = 0;
    for (int i = 0; i < n; i++) {
        if (ds[i].soLuong < k) {
            dem++;
        }
    }
    return dem;
}

// Hàm sắp xếp danh sách sản phẩm:
// - Sắp xếp theo số lượng TĂNG DẦN
// - Nếu số lượng bằng nhau, sản phẩm có mã nhỏ hơn theo thứ tự từ điển xuất hiện trước
// - KHÔNG sử dụng hàm thư viện qsort() (ở đây sử dụng thuật toán Interchange Sort / Selection Sort)
void sapXepSanPham(SanPham *ds, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            int need_swap = 0;
            // Tiêu chí 1: Số lượng tăng dần (nếu ds[i] > ds[j] thì cần hoán đổi)
            if (ds[i].soLuong > ds[j].soLuong) {
                need_swap = 1;
            } else if (ds[i].soLuong == ds[j].soLuong) {
                // Tiêu chí 2: Nếu số lượng bằng nhau, mã nhỏ hơn đứng trước
                // Nếu mã ds[i] lớn hơn mã ds[j] theo từ điển thì hoán đổi
                if (strcmp(ds[i].ma, ds[j].ma) > 0) {
                    need_swap = 1;
                }
            }

            if (need_swap) {
                SanPham temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }
}

int main() {
    int n, k;
    // Nhập số nguyên n và ngưỡng k
    if (scanf("%d %d", &n, &k) != 2 || n <= 0) {
        return 0;
    }

    // 1. Cấp phát động mảng gồm n cấu trúc SanPham
    SanPham *ds = (SanPham *)malloc(n * sizeof(SanPham));
    if (ds == NULL) {
        return 1;
    }

    // Nhập thông tin từng sản phẩm
    for (int i = 0; i < n; i++) {
        scanf("%15s %d", ds[i].ma, &ds[i].soLuong);
    }

    // 2. Xác định số sản phẩm cần nhập thêm hàng (soLuong < k)
    int soCanNhap = demCanNhap(ds, n, k);

    // 3. Sắp xếp danh sách sản phẩm
    sapXepSanPham(ds, n);

    // In kết quả:
    // Dòng 1: In số sản phẩm cần nhập thêm hàng
    printf("%d\n", soCanNhap);

    // n dòng tiếp theo: In mã và số lượng từng sản phẩm sau khi sắp xếp
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", ds[i].ma, ds[i].soLuong);
    }

    // Giải phóng bộ nhớ động đã cấp phát
    free(ds);

    return 0;
}

