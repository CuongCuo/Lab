/* Bài 6. Tính tổng từ 1 đến n
Mô tả bài toán: Viết hàm đệ quy tính tổng của các số nguyên từ 1 đến n.
Yêu cầu:
1. Nhập số nguyên dương n.
2. Viết hàm đệ quy tính:
1 + 2 + 3 + · · · + n
3. Không dùng vòng lặp trong hàm tính tổng.
4. In kết quả ra màn hình.
Gợi ý: Có thể viết công thức dưới dạng:
S(n) = n + S(n − 1)
và chọn điều kiện dừng là:
S(1) = 1
Ví dụ:
• Nếu n = 5 thì kết quả là 15.
*/
#include <stdio.h>
int tinh_tong(int n){
    if (n == 1) return 1;
    else return n + tinh_tong(n-1);
}
int main(){
    int n;
    printf("Nhap so nguyen duong n: ");
    scanf("%d", &n);
    printf("Tong tu 1 den %d la: %d\n", n, tinh_tong(n));
    return 0;
}
