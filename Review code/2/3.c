#include<stdio.h>
/*Yêu cầu: Viết chương trình nhập một số nguyên x và một số nguyên k biểu thị vị trí bit cần
kiểm tra (tính từ 0, bắt đầu từ bit thấp nhất). Chương trình cần xác định giá trị của bit thứ
k trong biểu diễn nhị phân của x và in ra kết quả bit đó là 0 hay 1.
Ví dụ:
 x = 10
 k = 1
ˆ Biểu diễn nhị phân của 10 là 1010, bit thứ 1 bằng 1.
1
 */
int main(){
    int x,k;
    printf("Nhap x: ");
    scanf("%d",&x);
    printf("Nhap k: ");
    scanf("%d",&k);
    // dich lay bit thu k va and voi 1 de trich xuat
    int bit = (x >> k) & 1;
    if(bit == 1) printf("Bit thu %d la 1",k);
    else printf("Bit thu %d la 0",k);
    return 0;
}