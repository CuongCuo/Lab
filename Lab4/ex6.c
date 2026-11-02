/*
Bài 6: Union lưu dữ liệu đo
Mô tả bài toán: Một thiết bị đo có thể trả về dữ liệu dưới các dạng khác nhau, ví dụ số
nguyên hoặc số thực, nhưng tại một thời điểm chỉ có một giá trị là hợp lệ. Chương trình cần
sử dụng union để lưu dữ liệu đo và hiển thị kết quả tương ứng.
Yêu cầu:
 Khai báo union để lưu một trong hai kiểu dữ liệu: int hoặc float.
 Viết chương trình cho phép người dùng chọn kiểu dữ liệu cần nhập.
 Nếu người dùng chọn số nguyên, lưu và in giá trị nguyên.
 Nếu người dùng chọn số thực, lưu và in giá trị thực.
 In kích thước của union bằng sizeof() và nhận xét.
*/
#include<stdio.h>
#include<stdlib.h>
typedef union Data{
    int i;
    float f;
} Data;
int main(){
    Data d;
    int i;
    float f;
    printf("Nhap 1 (int) hay 2 (float):");
    scanf("%d", &i);
    if(i==1){
        printf("nhap int : ");
        scanf("%d", &d.i);
        printf("gia tri vua nhap la:%d\n",d.i);
    }
    else if (i==2){
        printf("nhap float: ");
        scanf("%f",&d.f);
        printf("gia tri vua nhap la:%f\n",d.f);
    }
    else return -1;
    printf("Kich thuoc union la: %d\n", sizeof(d));
    return 0;
}
