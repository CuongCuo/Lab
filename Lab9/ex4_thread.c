/*
Chương trình 1 – Thread
1. Tạo một luồng mới.
2. Luồng mới gán shared_var = 10 rồi kết thúc.
3. Luồng chính chờ bằng pthread_join() rồi in shared_var.
*/
#include <stdio.h>
#include <pthread.h>
int shared_var = 0;
void *gan(void *arg){
    shared_var = 10;
    return NULL;
}

int main(void){
    pthread_t tid;

    pthread_create(&tid,NULL,gan,NULL);
    pthread_join(tid, NULL);
    
    printf("%d\n",shared_var);
    return 0;
}