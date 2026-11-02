/*
Bài 1: Quản lý tọa độ robot
Mô tả bài toán: Một robot di chuyển trong mặt phẳng 2D và được biểu diễn bằng tọa độ
(x, y). Chương trình cần lưu và cập nhật vị trí robot.
Yêu cầu:
ˆ Khai báo struct Point gồm hai thành phần x, y.
ˆ Nhập tọa độ ban đầu của robot.
ˆ Viết hàm cập nhật vị trí.
ˆ In vị trí sau khi cập nhật.
Ví dụ: Input: (3,4), dịch chuyển (2,1) → Output: (5,5)
*/
#include <stdio.h>
typedef struct Point {
    int x;
    int y;
} Point; // call via typedef
// kiem tra xem co tran hay k
int add_ok(int a, int b){
    if ((a > 0 && b > 0) ||( a < 0 && b < 0)) return 0;
    else return 1;
}
// x + dx ; y + dy, truyền vào con trỏ cũ
void update_point(Point *a, int dx, int dy){
    if (!add_ok(a->x, dx) || !add_ok(a->y, dy)) return;
    a->x = a->x + dx; // using -> to truyen gia tri vao con tro
    a->y = a->y + dy;
}
int main(){
    Point p;
    int dx, dy;
    printf("Nhap vao vi tri ban dau: ");
    scanf("%d %d", &p.x, &p.y);
    printf("Nhap vao vi tri can update: ");
    scanf("%d %d", &dx, &dy);
    update_point(&p, dx, dy);
    printf("Vi tri sau khi cap nhat la: %d %d\n", p.x, p.y); // call thi goi bang p.x
    return 0;
} 
