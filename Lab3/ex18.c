/*Bài 18: Mở rộng danh sách nhiệt độ
Mô tả bài toán: Một cảm biến nhiệt độ ban đầu gửi về n giá trị. Sau đó, cảm biến gửi thêm
m giá trị mới. Chương trình cần mở rộng vùng nhớ đã cấp phát ban đầu để lưu toàn bộ dữ
liệu cũ và mới.
Yêu cầu:
1. Nhập n và cấp phát mảng động ban đầu.
2. Nhập n giá trị nhiệt độ.
3. Nhập thêm m.
4. Dùng realloc() để mở rộng mảng thành n + m phần tử.
5. Nhập tiếp m giá trị mới.
6. In toàn bộ danh sách sau khi mở rộng.
7. Giải phóng bộ nhớ.
Ví dụ:
Ban đầu nhập 3 nhiệt độ: 30, 31, 29
Sau đó nhập thêm 2 nhiệt độ: 32, 30
Kết quả cuối cùng là danh sách 30, 31, 29, 32, 30*/
#include <stdio.h>
#include <stdlib.h>
int main(){
    int n;
    printf("Nhap vao n nhiet do ban dau: ");
    scanf("%d", &n);
    int *arr = (int*) malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) scanf("%d", &arr[i]);
    // thay doi kich thuoc
    int m;
    printf("Nhap them m: ");
    scanf("%d", &m);
    int new_size = n+m;
    
    arr = (int*)realloc(arr, new_size * sizeof(int)); // thay bằng độ dài mới * cỡ của dữ liệu
    for(int i = n; i < new_size; i++) scanf("%d", &arr[i]);
    for(int i = 0; i < new_size; i++) printf("%d ", arr[i]);
    free(arr);
    return 0;
}
