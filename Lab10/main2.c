#define CAPACITY 5
int buffer[CAPACITY];
int head = 0, tail = 0, count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_full  = PTHREAD_COND_INITIALIZER;

// --- Producer: Thêm phần tử ---
void produce(int value) {
    pthread_mutex_lock(&mutex);
    while (count == CAPACITY) {               // Buffer đầy → chờ
        pthread_cond_wait(&not_full, &mutex);
    }
    buffer[tail] = value;
    tail = (tail + 1) % CAPACITY;
    count++;
    pthread_cond_signal(&not_empty);          // Báo consumer có dữ liệu
    pthread_mutex_unlock(&mutex);
}

// --- Consumer: Lấy phần tử ---
int consume(void) {
    pthread_mutex_lock(&mutex);
    while (count == 0) {                      // Buffer rỗng → chờ
        pthread_cond_wait(&not_empty, &mutex);
    }
    int value = buffer[head];
    head = (head + 1) % CAPACITY;
    count--;
    pthread_cond_signal(&not_full);           // Báo producer có chỗ trống
    pthread_mutex_unlock(&mutex);
    return value;
}