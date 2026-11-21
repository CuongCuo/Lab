/*
Viết chương trình C bai1.c để quan sát thông tin định danh của tiến trình đang chạy.
1. In PID của tiến trình bằng getpid() và PPID bằng getppid().
1
2. Giữ chương trình tiếp tục chạy trong 10 giây bằng sleep(10) trước khi kết thúc.
3. Trong terminal thứ hai, dùng ps để tìm tiến trình và đối chiếu PID, PPID với kết quả
của chương trình.
4. Dùng pstree -p để xác định tiến trình trong cây tiến trình.
*/
#include <stdio.h>
#include <unistd.h>
#define Sleep_time 10
int main() {
    // in pid , va pidd
    printf("PID: %d\n", getpid());
    printf("PPid: %d\n", getppid());

    fflush(stdout);
    sleep(Sleep_time);

}