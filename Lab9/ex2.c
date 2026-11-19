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
#include <string.h>
#include <pthread.h>

void *sum(void *arg){
    int n = *(int*)arg;
    int tong = 0;
    for (int i = 0; i <=n; i++) tong += i;
    printf("%d\n",tong);
    return NULL;
}
int main(){
    int n;
    printf("Nhap so nguyen duong: \n");
    scanf("%d", &n);
    pthread_t thread;
    pthread_create(&thread,NULL,sum,NULL);
    pthread_join(thread,NULL);
    return 0;

}