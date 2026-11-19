/*
Viết chương trình bai5.c tính tổng một mảng long bằng bốn luồng.
1. Tạo mảng gồm N = 1000000 phần tử, với a[i] = i + 1.
2. Chia mảng thành bốn đoạn gần bằng nhau.
3. Mỗi luồng nhận chỉ số bắt đầu và kết thúc của đoạn cần xử lý.
4. Mỗi luồng tính một partial_sum riêng, không cùng cập nhật một biến tổng toàn cục.
5. Luồng chính chờ bốn luồng rồi cộng bốn kết quả cục bộ để tạo tổng cuối cùng.
6. Kiểm tra kết quả bằng công thức N * (N + 1) / 2.
*/

#include <stdio.h>
#include <pthread.h>
typedef struct {
    const long *array;
    size_t begin;
    size_t end;
    long long partial_sum;
} Task;