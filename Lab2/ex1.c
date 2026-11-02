#include<stdio.h>
int main() {
    char name[100];
    int age;
    float height;

    printf("Nhap ten: ");
    fgets(name, sizeof(name), stdin);

    printf("Nhap tuoi: ");
    scanf("%d", &age);

    printf("Nhap chieu cao cm): ");
    scanf("%f", &height);

    printf("\n--- THONG TIN CA NHAN ---\n");
    printf("Ho va ten : %s", name);
    printf("Tuoi      : %d\n", age);
    printf("Chieu cao : %.2f\n", height);

    return 0;
}

	
