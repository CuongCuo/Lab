/*
Yêu cầu
Viết chương trình bai2.c gồm hai luồng và một biến dùng chung:
int ready = 0;
Sử dụng một mutex và một biến điều kiện.
1. Luồng consumer khóa mutex.
2. Khi ready == 0, consumer chờ bằng pthread_cond_wait() trong vòng lặp while.
3. Luồng producer thực hiện một công việc mô phỏng ngắn, sau đó khóa mutex và gán ready = 1.
4. Producer thông báo bằng pthread_cond_signal() rồi mở mutex.
5. Consumer thức dậy, kiểm tra lại điều kiện, in Consumer: Data received. rồi kết thúc.*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int ready = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
void *consumer(void *arg){
    (void)arg;
    // cong viec
    pthread_mutex_lock(&mutex);
    while(ready == 0){
        pthread_cond_wait(&cond,&mutex);
    }
    printf("Consumer: Data received\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
}
void *producer(void *arg){
    (void)arg;
    sleep(1); // mo phong ngan 

    pthread_mutex_lock(&mutex);
    ready = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
   return NULL;
}
int main(){
    pthread_t p1,p2;
    pthread_create(&p1,NULL,consumer,NULL);
    pthread_create(&p2,NULL,producer,NULL);
    
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);

    return 0;
}