/* 
Bai 2: Quan ly sinh vien
Mo ta bai toan: Mot lop hoc can quan ly thong tin sinh vien gom ma sinh vien, ho ten, tuoi
va diem so. Chuong trinh can cho phep nhap danh sach sinh vien, tim kiem, cap nhat, thong
ke va sap xep du lieu.
Yeu cau:
 Su dung typedef de dinh nghia kieu du lieu Student.
 Khai bao kieu Student gom id, name, age, score.
 Nhap so luong sinh vien va nhap danh sach sinh vien.
 In danh sach sinh vien.
 Tim kiem sinh vien theo id.
 Neu tim thay, in thong tin sinh vien tuong ung.
 Cap nhat diem cho sinh vien theo id.
 Tinh diem trung binh cua ca lop.
 Tim sinh vien co diem cao nhat.
 Sap xep danh sach theo diem giam dan.
 Sap xep danh sach theo ten theo thu tu bang chu cai.
 In danh sach sau khi sap xep.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Student {
    int id;
    char name[50];
    int age;
    float score;    
} Student;

// ham bo het ky tu con lai trong buffer cho den het dong (thay getchar)
void clear_buffer(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ham xoa new_line sau fgets
void rm_new_line(char *c){
    size_t len = strlen(c);
    if (len > 0 && c[len-1] == '\n') c[len-1] = '\0'; // n o cuoi -> 0
    
}
// nhap thong tin 1 sinh vien
void add_student(Student *student, int n){
    printf("Nhap id: \n");
    scanf("%d", &student -> id);
    clear_buffer(); // bo het ky tu thua sau scanf

    printf("Nhap ten: \n");
    fgets(student->name, 50, stdin);
    rm_new_line(student->name);
    
    printf("Nhap tuoi: \n");
    scanf("%d", &student -> age);
    clear_buffer();
    printf("Nhap diem: \n");
    scanf("%f", &student -> score);
    clear_buffer();
}
void danh_sach(Student *student, int n){
    for (int i = 0; i < n ; i ++){
        printf("Nhap thong tin sinh vien thu %d:\n", i+1);
        add_student(&student[i], n);
    }
    for(int i = 0; i < n; i++){ // in ra danh sach sinh vien
        printf("Danh sach sinh vien thu %d: ", i+1);
        printf("ID: %d, Name: %s, Age: %d, Score: %.2f\n",
        student[i].id, student[i].name, student[i].age, student[i].score); //using p.x, p.y
    }
}
void timkiemsv_id(Student *student, int n){ // tim kiem va in ra sinh vien
    int find_id;
    printf("Nhap id can tim: ");
    scanf("%d", &find_id);
    clear_buffer();
    for (int i = 0; i < n; i ++){
        if (student[i].id == find_id){
            printf("Tim thay sinh vien\n");
            printf("ID: %d, Name: %s, Age: %d, Score: %.2f\n", 
            student[i].id, student[i].name, student[i].age, student[i].score);
        }
    }
}
void cap_nhat_diem(Student *student, int n){
    int find_id;
    float new_point;
    printf("Nhap id can tim: ");
    scanf("%d", &find_id);
    clear_buffer();
    for (int i = 0; i < n; i ++){
        if (student[i].id == find_id){
            printf("Nhap diem moi: ");
            scanf("%f", &new_point);
            clear_buffer();
            student[i].score = new_point;
            printf("Diem sinh vien sau khi cap nhat: %.2f\n", student[i].score);
        }
    }
}
void avg(Student *student, int n){
    float sum = 0;
    for(int i = 0; i < n; i++) sum = sum + student[i].score;
    printf("Diem trung binh la: %f\n", sum/n);
}
void max_p(Student *student, int n){
    Student max_p = student[0];
    for(int i = 0; i < n; i++){
        if(student[i].score > max_p.score) max_p = student[i];
    }
    printf("Sinh vien co diem cao nhat: ");
    printf("ID: %d, Name: %s, Age: %d, Score: %.2f\n",
    max_p.id, max_p.name, max_p.age, max_p.score);
}
int cmp_point(const void *a, const void *b){
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;

    if(s1->score > s2 -> score) return -1; // neu diem s1 > s2 ==> s1 comes first
    else if(s1 -> score < s2 -> score) return 1; // else thi s2 o sau
    else return 0; // 2 diem bang nhau
}
void sort_point(Student *student, int n){
    // sap xep theo thu tu diem giam dan
    qsort(student, n, sizeof(Student), cmp_point);
    for(int i = 0; i<n; i++){
        printf("Danh sach sinh vien (theo diem): ID: %d, Name: %s, Age: %d, Score: %.2f\n",
        student[i].id, student[i].name, student[i].age, student[i].score);
    }
}
// sap xep theo ten (mang char la con tro -> dung strcmp de so sanh)
int cpm_char(const void *a, const void *b){
    const Student *s1 = (const Student *)a; // tro vao con tro
    const Student *s2 = (const Student *)b;
    return strcmp(s1->name, s2->name); // ham trong stdlib, truyen vao 2 tro de so sanh

}
void sort_char(Student *student, int n){
    qsort(student, n, sizeof(Student), cpm_char);
    for(int i = 0; i<n; i++){
        printf("Danh sach sinh vien (theo ten): ID: %d, Name: %s, Age: %d, Score: %.2f\n",
        student[i].id, student[i].name, student[i].age, student[i].score);
    }
}
int main(){
    int n;
    printf("Nhap so luong sinh vien: ");
    scanf("%d", &n);
    clear_buffer(); // bo het ky tu thua sau scanf so luong sv
    Student *student = (Student*)malloc(n* sizeof(Student));
    danh_sach(student, n); // danh_sach da goi add_student ben trong, khong can goi lai
    timkiemsv_id(student, n);
    cap_nhat_diem(student, n);
    avg(student, n);
    max_p(student, n);
    sort_point(student, n);
    sort_char(student, n);
    free(student);
    return 0;
}
