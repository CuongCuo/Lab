#include <stdio.h>
// luu tru va hien thi ten tuoi
int main(){
    char name[50];
    int age; 
    int cao;

    printf("Nhap ten : ");
    fgets(name, sizeof(name),stdin);
    printf("Nhap tuoi : ");
    scanf("%d",&age);
    printf("Nhap chieu cao : ");
    scanf("%d",&cao);
    printf("%s",name);
    printf("%d",age);
    printf("%d",cao);
    return 0;
}