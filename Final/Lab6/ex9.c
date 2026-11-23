#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
/*
Viết chương trình C bai9.c để tạo có chủ đích một tiến trình zombie trong thời gian ngắn và
quan sát trạng thái của nó bằng ps.
1. Tiến trình con kết thúc ngay bằng _exit(0).
2. Tiến trình cha in PID của con rồi ngủ 20 giây mà chưa gọi waitpid().
3. Trong terminal thứ hai, dùng ps -o pid,ppid,stat,cmd -p <PID> để quan sát trạng
thái Z.
4. Sau 20 giây, tiến trình cha gọi waitpid() để thu thập tiến trình con trước khi kết thúc.
Điểm cần quan sát: Trong khoảng thời gian tiến trình cha đang ngủ, tiến trình con đã kết
thúc nhưng chưa được thu thập nên có thể xuất hiện ở trạng thái zombie.*/
int main(){
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        return 1;
    }
    if(pid == 0){
        _exit(0);
    }
    printf("Pid con: %d\n",getpid());
    sleep(20);
}