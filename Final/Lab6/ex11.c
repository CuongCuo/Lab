/*
Bài 11. Xử lý SIGINT
Viết chương trình C bai11.c bắt tín hiệu SIGINT khi người dùng nhấn Ctrl+C và kết thúc
chương trình theo cách có kiểm soát.
1. Khai báo biến cờ kiểu static volatile sig_atomic_t stop = 0.
2. Đăng ký hàm xử lý SIGINT bằng sigaction(), trong đó handler chỉ gán stop = 1.
3. Chương trình in PID rồi tiếp tục chạy cho đến khi người dùng nhấn Ctrl+C.
4. Sau khi cờ dừng được đặt, chương trình in SIGINT received, exiting rồi kết thúc bình
thường.
*/
// chiu chet