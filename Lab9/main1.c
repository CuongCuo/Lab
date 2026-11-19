// hello from thread
#include <stdio.h>
#include <string.h>
#include <pthread.h>

void *worker(void *arg){
    (void)arg;
    printf("Luong phu\n");
    return NULL;
}
int main(){
    pthread_t tid;
    // ham tao thread
    int s = pthread_create(&tid,NULL,worker,NULL);
    if (s != 0) {
        fprintf(stderr, "pthread_create: %s\n", strerror(s)); // ko dung dc perror vi thu vien nay tra thang ve ket qua
        return 1;
    }
    s = pthread_join(tid,NULL);
    if (s != 0) {
        fprintf(stderr, "pthread_join: %s\n", strerror(s));
        return 1;
    }
    printf("luong chinh ket thuc");
    return 0;
}