#include <stdio.h>

float tong_tien(int n, int price){
    return n * price;
}

float giamgia(float n, float price, float g){
    return tong_tien(n, price) * g / 100;
}

float tong_cuoi(float n, float price, float g){
    return tong_tien(n, price) - giamgia(n, price, g);
}

int main(){
    int n, price, g;
    printf("Nhap so luong san pham, don gia cua tung san pham, phan tram giam gia: ");
    scanf("%d%d%d", &n, &price, &g);
    printf("Tong tien truoc khi giam gia: %.2f\n", tong_tien(n, price));
    printf("So tien duoc giam: %.2f\n", giamgia(n, price, g));
    printf("So tien cuoi cung phai tra: %.2f\n", tong_cuoi(n, price, g));
    return 0;
}
