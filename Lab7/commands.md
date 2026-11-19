# Hướng Dẫn Biên Dịch & Thực Thi Lab 7 (IPC & Pipe)

> **Ghi chú**: Mở Terminal trỏ vào thư mục `Lab7` trước khi thực hiện.
> ```bash
> cd "c:/Users/Cuong/OneDrive/Desktop/HOC TAP/NAM 2 KI 1/SYSTEM_PROGRAMMING(2627I_UET.CE2020_4)/Lab/Lab7"
> ```

---

## ⚡ 1. Biên dịch nhanh tất cả các bài (ex1 -> ex12)

Chạy lệnh vòng lặp này để biên dịch đồng loạt toàn bộ 12 bài:

```bash
for i in {1..12}; do gcc -Wall -Wextra "ex${i}.c" -o "ex${i}"; done
```

Dọn dẹp các file thực thi và FIFO sau khi chạy xong:
```bash
rm -f ex1 ex2 ex3 ex4 ex5 ex6 ex7 ex8 ex9 ex10 ex11 ex12 *.fifo output.txt
```

---

## 🚀 2. Lệnh biên dịch & chạy từng bài chi tiết

### 🔹 Bài 1: Truyền chuỗi qua Pipe trong cùng một tiến trình
```bash
gcc -Wall -Wextra ex1.c -o ex1 && ./ex1
```
* **Kết quả dự kiến**:
  ```text
  Received: Hello pipe
  ```

---

### 🔹 Bài 2: Cha gửi dữ liệu cho con qua Pipe
```bash
gcc -Wall -Wextra ex2.c -o ex2 && ./ex2
```
* **Kết quả dự kiến**:
  ```text
  Child received: Message from parent
  ```

---

### 🔹 Bài 3: Con gửi dữ liệu cho cha qua Pipe
```bash
gcc -Wall -Wextra ex3.c -o ex3 && ./ex3
```
* **Kết quả dự kiến**:
  ```text
  Parent received: Hello parent
  ```

---

### 🔹 Bài 4: Đọc dữ liệu đến EOF
```bash
gcc -Wall -Wextra ex4.c -o ex4 && ./ex4
```
* **Kết quả dự kiến**:
  ```text
  packet 1
  packet 2
  packet 3
  EOF received
  ```

---

### 🔹 Bài 5: Trao đổi hai chiều bằng hai Pipe
```bash
gcc -Wall -Wextra ex5.c -o ex5 && ./ex5
```
* **Kết quả dự kiến**:
  ```text
  Child received: Hello child
  Parent received: Hello parent
  ```

---

### 🔹 Bài 6: Chuyển hướng stdout vào tệp `output.txt`
```bash
gcc -Wall -Wextra ex6.c -o ex6 && ./ex6 && cat output.txt
```
* **Kết quả dự kiến**:
  ```text
  Day di ong chau oi
  Hello world
  ```

---

### 🔹 Bài 7: Chuyển hướng stdin từ tệp `input.txt`
```bash
echo "system programming with pipes" > input.txt && gcc -Wall -Wextra ex7.c -o ex7 && ./ex7
```
* **Kết quả dự kiến**:
  ```text
  data: system programming with pipes
  ```

---

### 🔹 Bài 8: Thu đầu ra của lệnh bằng pipe (`uname -a`)
```bash
gcc -Wall -Wextra ex8.c -o ex8 && ./ex8
```
* **Kết quả dự kiến**:
  ```text
  Captured: Linux ...
  ```

---

### 🔹 Bài 9: Xây dựng pipeline `ls | wc -l`
```bash
gcc -Wall -Wextra ex9.c -o ex9 && ./ex9
```
* Kiểm tra đối chiếu với lệnh shell:
```bash
ls | wc -l
```

---

### 🔹 Bài 10: Tạo FIFO và truyền dữ liệu giữa hai chương trình

#### Cách 1: Chạy tự động cả 2 tiến trình (Nhanh nhất)
```bash
gcc -Wall -Wextra ex10.c -o ex10 && ./ex10
```

#### Cách 2: Chạy trên 2 Terminal độc lập (Đúng chuẩn mô phỏng IPC 2 process)
* **Biên dịch**:
  ```bash
  gcc -Wall -Wextra ex10.c -o ex10
  ```
* **Terminal 1 (Reader)**:
  ```bash
  ./ex10 reader
  ```
* **Terminal 2 (Writer)**:
  ```bash
  ./ex10 writer
  ```
* **Dọn dẹp**:
  ```bash
  rm -f data.fifo
  ```

---

### 🔹 Bài 11: Truyền dữ liệu cảm biến qua FIFO đến EOF

#### Cách 1: Chạy tự động cả 2 tiến trình
```bash
gcc -Wall -Wextra ex11.c -o ex11 && ./ex11
```

#### Cách 2: Chạy trên 2 Terminal độc lập
* **Biên dịch**:
  ```bash
  gcc -Wall -Wextra ex11.c -o ex11
  ```
* **Terminal 1 (Monitor / Đọc)**:
  ```bash
  ./ex11 monitor
  ```
* **Terminal 2 (Sensor / Ghi)**:
  ```bash
  ./ex11 sensor
  ```
* **Kết quả dự kiến ở Terminal 1**:
  ```text
  S1 -65
  S2 -70
  S3 -60
  ```
* **Dọn dẹp**:
  ```bash
  rm -f sensor.fifo
  ```

---

### 🔹 Bài 12: Client – Server đơn giản bằng 2 FIFO

#### Cách 1: Chạy tự động cả 2 tiến trình
```bash
gcc -Wall -Wextra ex12.c -o ex12 && ./ex12
```

#### Cách 2: Chạy trên 2 Terminal độc lập
* **Biên dịch**:
  ```bash
  gcc -Wall -Wextra ex12.c -o ex12
  ```
* **Terminal 1 (Server)**:
  ```bash
  ./ex12 server
  ```
* **Terminal 2 (Client)**:
  ```bash
  ./ex12 client
  ```
* **Kết quả**:
  - Terminal Server in: `Request: STATUS`
  - Terminal Client in: `Response: OK`
* **Dọn dẹp**:
  ```bash
  rm -f request.fifo response.fifo
  ```
