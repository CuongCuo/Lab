/*Viết chương trình bai3.c tạo ba luồng. Mỗi luồng nhận một cấu trúc chứa:
• id: Số thứ tự luồng.
• message: Chuỗi thông điệp của luồng.
Mỗi luồng in:
Thread <id>: <message>
Luồng chính:
1. Tạo đủ ba luồng.
2. In Main thread is running..
3. Chờ cả ba luồng bằng ba lời gọi pthread_join().
4. In All threads finished. trước khi kết thúc.*/
#include <stdio.h>
#include <pthread.h>
// truyền nhiều giá trị qua struct
typedef struct {
    int id;
    char *msg;
} Args;
void *luong(void *arg){
    Args a = *(Args *)arg;// ** -> g// **
    printf("Thread %d: %s", a.id, a.msg);
    return NULL;
}
int main(){
    pthread_t tid[3];
    // khoi tao va truyen 
    Args arg[3]  = { {1, "Hello\n"}, {2, "World\n"}, {3, "nigga\n"} };
    for (int i = 0; i < 3; i ++){
        pthread_create(&tid[i],NULL,luong,&arg[i]);
    }
    printf("OK\n");
    for (int i = 0; i < 3; i++){
        pthread_join(tid[i],NULL);
    }
    printf("all\n");
    return 0;
}