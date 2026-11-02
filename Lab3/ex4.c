#include <stdio.h>
float avg(float a, float b, float c){
    return (a + b + c) / 3;
}
float max(float a, float b, float c){
    int max_p = a;
    if (b > max_p) max_p = b;
    if (c > max_p) max_p = c;
    return max_p;
}
void rank(float a, float b, float c){
    float tb = avg(a,b,c);
    if (tb < 5.0) printf("Hoc luc: Truot\n");
    else if (tb < 6.5) printf("Hoc luc: Dat\n");
    else if (tb < 8.0) printf("Hoc luc: Kha\n");
    else printf("Hoc luc: Gioi\n");
}
int main() {
    float a,b,c;
    printf("Nhap diem cua 3 mon: ");
    scanf("%f%f%f", &a,&b,&c);
    printf("Diem trung binh: %.2f\n", avg(a,b,c));
    printf("Diem cao nhat: %.2f\n", max(a,b,c));
    rank(a,b,c);
    return 0;   
}
