pid_t pid = fork();
if (pid == 0) {
    sleep(5);
    printf("Con PPID sau khi cha chết: %d\n", getppid());  // Phải là 1
    exit(0);
}
// Cha thoát ngay, không wait
exit(0);