/*
Viết chương trình bai2.c trong đó một luồng tính tổng các số nguyên từ 1 đến N.
1. Nhập N từ bàn phím.
2. Tạo một luồng nhận N thông qua tham số void *arg.
3. Luồng tính 1 + 2 + ... + N.
4. Kết quả được đặt trong một vùng nhớ hợp lệ sau khi luồng kết thúc, ví dụ vùng nhớ cấp phát
động.
5. Luồng trả địa chỉ kết quả bằng return hoặc pthread_exit().
6. Luồng chính nhận kết quả thông qua đối số thứ hai của pthread_join(), in kết quả và giải phóng
vùng nhớ nếu cần.
Kiểm thử
*/
#include <stdio.h>
#include <pthread.h>

void *tinh_tong(void *arg) {
    int n = *(int *)arg;
    static long long ket_qua;

    ket_qua = 0;
    for (int i = 1; i <= n; i++)
        ket_qua += i;
    return &ket_qua; // NOT RETURN NULL
}

int main(void) {
    int n;
    pthread_t tid;
    void *ret;

    printf("Nhap so nguyen duong: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    if (pthread_create(&tid, NULL, tinh_tong, &n) != 0) return 1;
    if (pthread_join(tid, &ret) != 0) return 1;

    printf("Tong = %lld\n", *(long long *)ret);
    return 0;
}