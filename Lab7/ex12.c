/*
Bài 12. Client–server đơn giản bằng FIFO
Yêu cầu
Viết hai chương trình C server.c và client.c để trao đổi một yêu cầu và một phản hồi bằng hai FIFO.
1. Sử dụng request.fifo cho chiều client sang server và response.fifo cho chiều server sang client.
2. Tạo hai FIFO bằng lệnh mkfifo trước khi chạy chương trình.
3. Trong server, mở request.fifo bằng O_RDONLY, đọc yêu cầu rồi đóng file descriptor này.
4. Trong client, mở request.fifo bằng O_WRONLY, gửi chuỗi STATUS rồi đóng file descriptor này.
5. Sau khi nhận yêu cầu, server in Request: STATUS , mở response.fifo bằng O_WRONLY, gửi chuỗi
   OK rồi đóng file descriptor.
6. Client mở response.fifo bằng O_RDONLY, đọc phản hồi và in Response: OK .
7. Sau khi thực hành, xóa cả hai FIFO.

Gợi ý thứ tự chạy:
Terminal 1: ./ex12 server
Terminal 2: ./ex12 client
Hoặc chạy tự động 2 tiến trình: ./ex12
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define REQ_FIFO "request.fifo"
#define RES_FIFO "response.fifo"

int run_server(void) {
    char buf[128];

    // 1. Mở request.fifo để đọc yêu cầu
    int fd_req = open(REQ_FIFO, O_RDONLY);
    if (fd_req == -1) {
        perror("server open request.fifo");
        return 1;
    }

    ssize_t n = read(fd_req, buf, sizeof(buf) - 1);
    if (n == -1) {
        perror("server read request");
        close(fd_req);
        return 1;
    }
    buf[n] = '\0';
    close(fd_req);

    // 2. In yêu cầu nhận được
    printf("Request: %s\n", buf);

    // 3. Mở response.fifo để gửi phản hồi "OK"
    int fd_res = open(RES_FIFO, O_WRONLY);
    if (fd_res == -1) {
        perror("server open response.fifo");
        return 1;
    }

    const char *reply = "OK";
    if (write(fd_res, reply, strlen(reply)) == -1) {
        perror("server write response");
        close(fd_res);
        return 1;
    }

    close(fd_res);
    return 0;
}

int run_client(void) {
    // 1. Mở request.fifo để gửi yêu cầu "STATUS"
    int fd_req = open(REQ_FIFO, O_WRONLY);
    if (fd_req == -1) {
        perror("client open request.fifo");
        return 1;
    }

    const char *req = "STATUS";
    if (write(fd_req, req, strlen(req)) == -1) {
        perror("client write request");
        close(fd_req);
        return 1;
    }
    close(fd_req);

    // 2. Mở response.fifo để đọc phản hồi từ server
    int fd_res = open(RES_FIFO, O_RDONLY);
    if (fd_res == -1) {
        perror("client open response.fifo");
        return 1;
    }

    char buf[128];
    ssize_t n = read(fd_res, buf, sizeof(buf) - 1);
    if (n == -1) {
        perror("client read response");
        close(fd_res);
        return 1;
    }
    buf[n] = '\0';
    printf("Response: %s\n", buf);

    close(fd_res);
    return 0;
}

int main(int argc, char *argv[]) {
    // Tạo 2 FIFO nếu chưa tồn tại
    if (mkfifo(REQ_FIFO, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo request");
        return 1;
    }
    if (mkfifo(RES_FIFO, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo response");
        return 1;
    }

    // Chạy với tham số: ./ex12 server hoặc ./ex12 client
    if (argc > 1) {
        if (strcmp(argv[1], "server") == 0) {
            return run_server();
        } else if (strcmp(argv[1], "client") == 0) {
            return run_client();
        } else {
            fprintf(stderr, "Cách dùng:\n  %s server  (chạy server ở terminal 1)\n  %s client  (chạy client ở terminal 2)\n  %s         (chạy tự động cả hai)\n", 
                    argv[0], argv[0], argv[0]);
            return 1;
        }
    }

    // Nếu chạy không truyền đối số: Tự động fork 2 tiến trình
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Con: Client
        sleep(1); // Chờ server mở request.fifo trước
        int ret = run_client();
        _exit(ret);
    } else {
        // Cha: Server
        run_server();
        waitpid(pid, NULL, 0);

        // Dọn dẹp cả hai FIFO sau khi hoàn tất
        unlink(REQ_FIFO);
        unlink(RES_FIFO);
    }

    return 0;
}
