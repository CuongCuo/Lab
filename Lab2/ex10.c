#include <stdio.h>
#include <string.h>

int main() {
    int n;
    int sum = 0;

    printf("Nhap so luong sinh vien: ");
    scanf("%d", &n);
    
    while (getchar() != '\n');
    
    char names[n][50];
    int scores[n];

    for (int i =0; i < n; i ++){
        printf("Nhap ten sinh vien thu %d\n", i+1); // stt + 1
        fgets(names[i], sizeof(names[i]), stdin);
        // Xoa ky tu '\n' o cuoi chuoi ma fgets doc vao
        names[i][strcspn(names[i], "\n")] = '\0';
        
        printf("nhap diem sv thu %d\n", i+1);
        scanf("%d", &scores[i]);
        sum += scores[i];
        
        while (getchar() != '\n');
    }
    // In ra danh sach va diem tuong ung 
    printf("Danh sach sinh vien va diem tuong ung:\n");
    for(int i = 0; i < n; i++){
        printf("Sinh vien: %s, Diem: %d\n", names[i], scores[i]);
    }
    // Tinh diem tb ca lop 
    printf("Diem trung binh ca lop la: %.2f\n", (float) sum/n);
    //tim sv co diem cao nhat 
    // tim sv co diem thap nhat
    int max =0, min = 0;
    for (int i = 1; i < n; i ++){
        if(scores[i] > scores[max]){
            max = i;
        }
        if(scores[i] < scores[min]){
            min = i;
        }
    }
    printf("Sinh vien co diem cao nhat la: %s, Diem: %d\n", names[max], scores[max]);
    printf("Sinh vien co diem thap nhat la: %s, Diem: %d\n", names[min], scores[min]);
}


