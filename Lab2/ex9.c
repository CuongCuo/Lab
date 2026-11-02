#include <stdio.h>

int main() {
    int n;
    printf("Nhap so luong phan tu n: ");
    scanf("%d", &n);

    int a[n], chan[n], le[n];
    int dem_chan = 0, dem_le = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]); // nhap lieu theo thu tu phan tu n 
        if (a[i] % 2 == 0) { 
            chan[dem_chan++] = a[i]; // them pt vao mang chan, tang chi so dem chan
        } else {
            le[dem_le++] = a[i]; // them phan tu vao mang le, tang chi so dem le
        }
    }

    printf("Mang chan: ");
    for (int i = 0; i < dem_chan; i++) printf("%d ", chan[i]); // in ra mang chan 

    printf("\nMang le: ");
    for (int i = 0; i < dem_le; i++) printf("%d ", le[i]); // in ra mang le
    printf("\n");

    return 0;
}
