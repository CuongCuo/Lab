# ÔN TẬP: LẬP TRÌNH HỆ THỐNG

---

## Bài 1

**1.1** Viết các lệnh shell để:
- Chuyển đến thư mục home của người dùng.
- Liệt kê toàn bộ nội dung trong thư mục đó.

**1.2** Đếm tổng số file trong thư mục home của người dùng có phần mở rộng `.c`.

**1.3** Viết một shell script:
- Nhận vào từ người dùng một số nguyên N.
- Tính tổng các số từ 1 đến N.
- Lưu kết quả vào file có tên `Result_ex1.txt`.

---

## Bài 2

**2.1** Viết chương trình C để:
- Đọc nội dung của file `Data.txt`.
- Sao chép nội dung vào một file mới có tên `Data_copy.txt`.

**2.2** Mở rộng chương trình trên để:
- Nối thêm chuỗi `"Goodbye, see you again."` vào cuối file `Data_copy.txt`.
- Đếm và hiển thị số ký tự và số dòng của file `Data_copy.txt`.

---

## Bài 3

**3.1** Viết chương trình tạo một tiến trình con, trong đó tiến trình cha **không** chờ tiến trình con kết thúc.

**3.2** Viết chương trình C mô phỏng lệnh shell: `ls | grep ".txt"`:
- Tiến trình con thực thi lệnh `ls`.
- Tiến trình cha thực thi lệnh `grep ".txt"` để lọc kết quả.

---

## Bài 4

**4.1** Viết chương trình C tạo một luồng (thread) để:
- Tính tổng các số chẵn từ 1 đến N (N được nhập từ bàn phím).
- Trả kết quả về luồng chính (main thread) để in ra màn hình.

**4.2** Viết chương trình tạo hai luồng:
- Luồng 1 in `"Ping"` rồi chờ.
- Luồng 2 in `"Pong"` sau `"Ping"`, rồi báo hiệu cho Luồng 1 tiếp tục.
- Lặp lại 5 lần, dùng **condition variable** để đồng bộ.

---

## Bài 5

Cho file `Hello.txt` với nội dung: `"Hello! What is your name?"`. Viết chương trình để:

a) Đọc nội dung file `Hello.txt` và in ra màn hình.

b) Đọc nội dung file `Hello.txt` bắt đầu từ **byte thứ 7** tính từ đầu file và in ra màn hình.
*(Gợi ý: dùng system call `lseek`)*

---

## Bài 6

Viết chương trình tạo file với hai lựa chọn:

- **Lựa chọn 1:** Nội dung file được nhập từ bàn phím.
- **Lựa chọn 2:** Đọc nội dung từ file khác và ghi vào file vừa tạo.

> [!NOTE]
> **(Nâng cao)** Tạo hai phiên bản của chương trình trên: một phiên bản dùng system call cơ bản `open()`, `read()`, `write()`, `close()` và một phiên bản dùng thư viện C chuẩn. So sánh thời gian thực thi của hai phiên bản (dùng lệnh `time`). Phiên bản nào nhanh hơn? Tại sao?

---

## Bài 7

Viết chương trình nhập vào tên một file và in ra:
- Kích thước của file.
- Thông tin quyền truy cập của file.

*(Gợi ý: dùng `stat` hoặc `fstat`)*

---

## Bài 8

Viết chương trình tên `linuxecho.c` mô phỏng lệnh:

```
echo [string] > example.txt
```

*(Chuỗi cần in đặt ở `argv[1]`, tên file đặt ở `argv[2]`)*

---

## Bài 9

Viết chương trình tên `linuxgrep.c` mô phỏng lệnh `grep`, trong đó:
- Từ cần lọc đặt ở `argv[1]`.
- Đường dẫn file đặt ở `argv[2]`.

> [!NOTE]
> **(Nâng cao)** Viết chương trình tên `grepdir.c` liệt kê tất cả các file trong thư mục có chứa từ cần lọc. Chương trình nhận 2 tham số đầu vào: từ cần lọc ở `argv[1]` và đường dẫn thư mục ở `argv[2]`.
>
> *Gợi ý:* Duyệt thư mục đầu vào, với mỗi file trong thư mục, tái sử dụng code của `linuxgrep` để lọc nội dung. Nếu từ cần tìm xuất hiện trong file, in tên file đó ra.

---

## Bài 10

Cho chương trình C dưới đây bị thiếu. Hoàn chỉnh chương trình để tạo một tiến trình con:

**Trong tiến trình con:**
- In giá trị của hai biến `idata` và `istack`. Thay đổi giá trị của chúng. Sau đó in giá trị mới ra màn hình.
- Dịch chuyển file offset đến byte thứ 7 từ đầu file.

**Trong tiến trình cha:**
- Chờ tiến trình con kết thúc.
- In giá trị của `idata` và `istack`.
- Đọc nội dung file `Hello.txt`.

**Câu hỏi:**
1. Giá trị của `idata` và `istack` được in ra trong tiến trình cha và con như thế nào? Giải thích tại sao.
2. Trong tiến trình cha, nội dung file `Hello.txt` được in ra như thế nào? Từ đó rút ra kết luận gì về file descriptor giữa tiến trình cha và con?

```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static int idata = 1000; // Cấp phát trong data segment

int main() {
    int istack = 150;    // Cấp phát trong stack segment
    int fd = open("Hello.txt", O_WRONLY);
    pid_t childPid;
    // ... (hoàn chỉnh chương trình)
}
```

---

## Bài 11

Viết chương trình tạo một tiến trình con, trong đó tiến trình con thực thi lệnh `ls` để liệt kê nội dung thư mục home của người dùng.

---

## Bài 12

Hoàn chỉnh chương trình C bên dưới mô phỏng một shell đơn giản (tiến trình cha) có thể thực thi các lệnh shell cơ bản.

```c
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define CMDSIZ 32

int main(int argc, char *argv[])
{
    int logout = 0, cmdsiz;
    char cmdbuf[CMDSIZ];

    while (!logout) {
        write(1, "myshell> ", 9);
        cmdsiz = read(0, cmdbuf, CMDSIZ);
        cmdbuf[cmdsiz - 1] = '\0';

        if (strcmp("logout", cmdbuf) == 0)
            ++logout;
        else
            process_command(cmdbuf);
    }
}

void process_command(char *cmdbuf)
{
    // Hoàn chỉnh hàm này
}
```

> [!NOTE]
> *Gợi ý:* Hàm `process_command` tạo tiến trình con để thực thi các chương trình như `linuxls`, `linuxcd` (các chương trình mô phỏng lệnh shell từ lab trước).

---

## Bài 13

Viết chương trình C trong đó tiến trình cha và tiến trình con trao đổi thông điệp với nhau:

- Tiến trình con gửi thông điệp `"Hello parent"` đến tiến trình cha. Tiến trình cha đọc và in thông điệp từ con ra màn hình.
- Tiến trình cha gửi thông điệp `"Hello children"` đến tiến trình con. Tiến trình con đọc và in thông điệp từ cha ra màn hình.

*(Gợi ý: Dùng hai pipe)*

---

## Bài 14

Viết chương trình C mô phỏng lệnh pipe: `ls | wc -l`, trong đó:
- Tiến trình con thực thi lệnh `ls`.
- Tiến trình cha thực thi lệnh `wc -l`.

*(Gợi ý: Dùng system call `pipe` để tạo pipe giữa hai tiến trình; dùng system call `dup2` để chuyển hướng input/output)*

---

## Bài 15

Viết chương trình C-Unix **liên tục kiểm tra mỗi 1 phút** và in danh sách các file bên trong một thư mục. Khi người dùng nhấn `Ctrl+C`, in ra thông báo `"Program is terminated by user"` và kết thúc chương trình.

> [!NOTE]
> *Gợi ý:*
> - Dùng `opendir`, `readdir`, `closedir`, `stat` để duyệt thư mục và in file.
> - Viết hàm xử lý tín hiệu ngắt (signal handler) khi người dùng nhấn `Ctrl+C`.

---

## Bài 16

Tạo một luồng in các số từ 1 đến N, mỗi số trên một dòng. N được nhập từ bàn phím. Luồng chính phải chờ luồng này kết thúc trước khi in `"Main thread exiting."`.

---

## Bài 17

Viết chương trình trong đó một luồng mới tính tổng các số từ 1 đến N và trả về kết quả. N được nhập từ bàn phím. Luồng chính lấy kết quả và in ra màn hình.

---

## Bài 18

Viết chương trình tạo **ba luồng**. Mỗi luồng in một thông điệp riêng cùng với ID luồng của nó. Luồng chính in `"Main thread is running"`. Chương trình phải chờ tất cả các luồng kết thúc trước khi thoát.

---

## Bài 19

Hoàn chỉnh hai chương trình dưới đây: Chương trình 1 tạo một luồng để sửa đổi biến toàn cục. Chương trình 2 tạo một tiến trình để sửa đổi cùng biến toàn cục đó. Sau đó chạy hai chương trình. Giá trị của biến toàn cục trong hai chương trình là bao nhiêu? Giải thích tại sao.

**Chương trình 1 (Thread):**
```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sharedVar = 5; // Dùng chung giữa các luồng

void *threadFunc(void *arg) {
    // Viết code thay đổi giá trị biến toàn cục ở đây
}

int main() {
    pthread_t thread;
    // Viết code tạo luồng ở đây
    // Viết code chờ luồng kết thúc ở đây
    printf("Main: sharedVar = %d\n", sharedVar);
    return 0;
}
```

**Chương trình 2 (Process):**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sharedVar = 5; // Mỗi tiến trình có bản sao riêng

int main() {
    // Viết code tạo tiến trình con ở đây
    if (pid == 0) { // Tiến trình con
        // Viết code thay đổi giá trị biến toàn cục ở đây
        printf("Child Process: sharedVar = %d\n", sharedVar);
        exit(0);
    } else {
        // Viết code chờ tiến trình con kết thúc ở đây
        printf("Parent Process: sharedVar = %d\n", sharedVar);
    }
    return 0;
}
```

---

## Bài 20

Viết chương trình:
- Định nghĩa một biến đếm toàn cục (`counter`).
- Tạo hai luồng: một luồng **tăng** counter 100 lần; một luồng **giảm** counter 50 lần.
- Dùng **mutex** để tránh race condition.
- In giá trị cuối cùng của counter.

---

## Bài 21

Barrier là cơ chế đồng bộ hóa khiến tất cả các luồng phải chờ cho đến khi một số lượng luồng nhất định đã đến một điểm chung.

Viết chương trình:
- Tạo N luồng (ví dụ: 4 luồng).
- Mỗi luồng in `"Thread X reached the barrier"`, rồi chờ tại barrier.
- Luồng đến cuối cùng in `"All threads reached the barrier! Releasing them..."` và cho phép tất cả tiếp tục.
- Mỗi luồng in `"Thread X passed the barrier"` sau khi được giải phóng.

> [!NOTE]
> *Gợi ý:* Dùng mutex để bảo vệ biến đếm và condition variable để báo hiệu tất cả các luồng khi luồng cuối cùng đến.

---

## Bài 22

Viết chương trình **producer-consumer** dùng mutex và condition variable.

Chương trình cần:
- Dùng một buffer chia sẻ (mảng số nguyên kích thước n).
- Có một luồng **producer** (nhà sản xuất):
  - Tạo các số và thêm vào buffer.
  - Chờ nếu buffer đầy.
- Có một luồng **consumer** (người tiêu dùng):
  - Lấy và in các số từ buffer.
  - Chờ nếu buffer rỗng.

---

## Bài 23

Viết chương trình song song đếm **bao nhiêu số lẻ** tồn tại trong một dải (ví dụ: từ 1 đến 10 triệu). Mỗi luồng xử lý một đoạn con và duy trì biến đếm cục bộ. Kết quả cuối là tổng của tất cả các biến đếm cục bộ.

---

## Bài 24

Viết chương trình tính **histogram song song**:
- Cho một mảng số nguyên (ví dụ: giá trị pixel từ 0–255), mỗi luồng đếm tần suất các số trong phần của mình.
- Gộp các kết quả đếm tần suất lại ở cuối để tạo histogram cuối cùng.

---

## Bài 25

Viết chương trình song song **tìm kiếm chuỗi** trong một mảng lớn các chuỗi:
- Mỗi luồng tìm kiếm trong một đoạn của mảng.
- Nếu một luồng tìm thấy chuỗi mục tiêu, nó báo cáo chỉ số tìm thấy và dừng tất cả các luồng khác.
- Dùng một **biến cờ chia sẻ** để đồng bộ việc dừng sớm.

---

## Bảng Phân Loại Bài Theo Chủ Đề

| Chủ đề | Bài |
|--------|-----|
| **Shell script & lệnh cơ bản** | 1 |
| **File I/O (syscall thấp)** | 2, 5, 6, 7, 8, 9 |
| **stat, lstat** | 7 |
| **fork, exec, wait** | 3, 10, 11, 12 |
| **Pipe & dup2** | 13, 14 |
| **Signal** | 15 |
| **Thread cơ bản** | 4, 16, 17, 18, 19 |
| **Mutex** | 20 |
| **Condition variable / Barrier** | 21, 22 |
| **Song song hóa (parallel)** | 23, 24, 25 |
