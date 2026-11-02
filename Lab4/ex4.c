#include <stdio.h>
#include <stdlib.h>

// Khai bao enum bieu dien trang thai cam bien
typedef enum {
    NORMAL,
    WARNING,
    ERROR
} SensorStatus;

// Khai bao struct SensorData su dung typedef
typedef struct {
    float temperature;
    int timestamp;
    SensorStatus status;
} SensorData;

// Ham chuyen enum sang chuoi de in ra man hinh
const char* lay_ten_trang_thai(SensorStatus status) {
    switch (status) {
        case NORMAL:
            return "NORMAL";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

// Ham nhap danh sach du lieu cam bien
void nhap_danh_sach(SensorData a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Nhap du lieu cam bien thu %d ---\n", i + 1);
        printf("Nhap nhiet do (float): ");
        scanf("%f", &a[i].temperature);

        printf("Nhap timestamp (int): ");
        scanf("%d", &a[i].timestamp);

        int st;
        printf("Nhap trang thai (0: NORMAL, 1: WARNING, 2: ERROR): ");
        scanf("%d", &st);
        a[i].status = (SensorStatus)st;
    }
}

// Ham in toan bo du lieu cam bien
void in_danh_sach(SensorData a[], int n) {
    printf("\n%-5s %-15s %-15s %-15s\n", "STT", "Nhiet do", "Timestamp", "Trang thai");
    for (int i = 0; i < n; i++) {
        printf("%-5d %-15.2f %-15d %-15s\n", 
               i + 1, a[i].temperature, a[i].timestamp, lay_ten_trang_thai(a[i].status));
    }
}

// Ham tinh nhiet do trung binh
float tinh_nhiet_do_tb(SensorData a[], int n) {
    if (n <= 0) return 0.0f;
    float tong = 0;
    for (int i = 0; i < n; i++) {
        tong += a[i].temperature;
    }
    return tong / n;
}

// Ham tim nhiet do lon nhat
float tim_nhiet_do_max(SensorData a[], int n) {
    float max = a[0].temperature;
    for (int i = 1; i < n; i++) {
        if (a[i].temperature > max) {
            max = a[i].temperature;
        }
    }
    return max;
}

// Ham dem so lan cam bien o tung trang thai
void dem_trang_thai(SensorData a[], int n) {
    int dem_normal = 0;
    int dem_warning = 0;
    int dem_error = 0;

    for (int i = 0; i < n; i++) {
        if (a[i].status == NORMAL) {
            dem_normal++;
        } else if (a[i].status == WARNING) {
            dem_warning++;
        } else if (a[i].status == ERROR) {
            dem_error++;
        }
    }

    printf("\n--- So lan cam bien o tung trang thai ---\n");
    printf("NORMAL : %d\n", dem_normal);
    printf("WARNING: %d\n", dem_warning);
    printf("ERROR  : %d\n", dem_error);
}

// Ham so sanh theo timestamp tang dan dung cho qsort
int so_sanh_timestamp(const void *a, const void *b) {
    const SensorData *s1 = (const SensorData *)a;
    const SensorData *s2 = (const SensorData *)b;

    if (s1->timestamp < s2->timestamp) return -1;
    if (s1->timestamp > s2->timestamp) return 1;
    return 0;
}

int main() {
    int n;
    printf("Nhap so luong lan do cua cam bien: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("So luong khong hop le!\n");
        return 0;
    }
    SensorData *ds = (SensorData *)malloc(n * sizeof(SensorData));
    if (ds == NULL) {
        printf("Loi cap phat bo nho!\n");
        return 1;
    }
    nhap_danh_sach(ds, n);
    printf("\n=== DANH SACH VUA NHAP ===");
    in_danh_sach(ds, n);
    printf("\nNhiet do trung binh: %.2f\n", tinh_nhiet_do_tb(ds, n));
    printf("Nhiet do lon nhat: %.2f\n", tim_nhiet_do_max(ds, n));
    dem_trang_thai(ds, n);
    qsort(ds, n, sizeof(SensorData), so_sanh_timestamp);
    printf("\n=== DANH SACH SAU KHI SAP XEP THEO TIMESTAMP TANG DAN ===");
    in_danh_sach(ds, n);
    free(ds);
    return 0;
}
