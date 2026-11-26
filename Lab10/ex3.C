#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#define CAPACITY 5
int buffer[CAPACITY];
int head = 0;
int tail = 0;
int count = 0;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_signal cond = PTHREAD_COND_INITIALIZER;

void *producer(void *arg){
    (void)arg;
    pthread_mutex_lock(&mutex);
        
}