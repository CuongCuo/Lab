#include <stdio.h>
#include <string.h>
#include <pthread.h>
/*
Viết chương trình bai1.c thực hiện các bước sau:
1. Nhập số nguyên dương N từ bàn phím.
2. Tạo một luồng mới bằng pthread_create().
3. Luồng mới in các số từ 1 đến N, mỗi số trên một dòng.
4. Luồng chính dùng pthread_join() để chờ luồng mới kết thúc.
5. Sau khi pthread_join() hoàn tất, luồng chính in Main thread exiting..
Kiểm thử
Với N = 5, chương trình cần kết thúc theo dạng:*/

