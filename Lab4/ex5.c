#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Student {
    char *name;
    int age;
} Student;
int main() {
    Student s1;
    char temp[100];
    printf("Nhap ten sinh vien: ");
    if (fgets(temp, sizeof(temp), stdin) == NULL) return 1;
    size_t len = strlen(temp);
    if (len > 0 && temp[len - 1] == '\n') temp[len - 1] = '\0';

    s1.name = (char*)malloc(strlen(temp) + 1);
    if (s1.name == NULL) return 1;
    strcpy(s1.name, temp);

    printf("Nhap tuoi: ");
    if (scanf("%d", &s1.age) != 1) {
        free(s1.name);
        return 1;
    }

    printf("\n--- Thong tin sinh vien ---\n");
    printf("Ten: %s | Tuoi: %d\n", s1.name, s1.age);
    /* ---------- Shallow copy ---------- */
    Student shallow = s1;               // chi copy gia tri con tro name
    printf("\n[Shallow] s1.name   = %p\n", (void*)s1.name);
    printf("[Shallow] copy.name = %p  (cung dia chi)\n", (void*)shallow.name);
    /* ---------- Deep copy ---------- */
    Student deep;
    deep.age = s1.age;
    deep.name = (char*)malloc(strlen(s1.name) + 1);
    if (deep.name == NULL) {
        free(s1.name);
        return 1;
    }
    strcpy(deep.name, s1.name);         // copy ca noi dung
    printf("[Deep]    deep.name = %p  (dia chi khac)\n", (void*)deep.name);

    
    strcpy(s1.name, "Doi ten");   
    printf("\nSau khi sua s1.name:\n");
    printf("shallow.name = %s  (bi doi theo)\n", shallow.name);
    printf("deep.name    = %s  (khong bi anh huong)\n", deep.name);

    /* Giai phong: shallow KHONG free rieng vi dung chung vung nho voi s1 */
    free(s1.name);
    free(deep.name);
    s1.name = NULL;
    deep.name = NULL;
    shallow.name = NULL;                // tranh dangling pointer

    return 0;
}
