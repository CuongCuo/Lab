# Lệnh Biên Dịch & Chạy Nhanh (Bài 1 → 25)

> [!NOTE]
> Các bài thread (4, 16–25) cần thêm cờ `-pthread` khi biên dịch.

| Bài | File | Lệnh biên dịch & chạy |
|-----|------|-----------------------|
| 1 | `ex01.sh` | `chmod +x ex01.sh && ./ex01.sh` |
| 2 | `ex02.c` | `echo "Hello" > Data.txt && gcc -Wall -Wextra ex02.c -o ex02 && ./ex02` |
| 3.1 | `ex03_1.c` | `gcc -Wall -Wextra ex03_1.c -o ex03_1 && ./ex03_1` |
| 3.2 | `ex03_2.c` | `gcc -Wall -Wextra ex03_2.c -o ex03_2 && ./ex03_2` |
| 4.1 | `ex04_1.c` | `gcc -Wall -Wextra ex04_1.c -pthread -o ex04_1 && ./ex04_1` |
| 4.2 | `ex04_2.c` | `gcc -Wall -Wextra ex04_2.c -pthread -o ex04_2 && ./ex04_2` |
| 5 | `ex05.c` | `printf "Hello! What is your name?" > Hello.txt && gcc -Wall -Wextra ex05.c -o ex05 && ./ex05` |
| 6 | `ex06.c` | `gcc -Wall -Wextra ex06.c -o ex06 && ./ex06` |
| 7 | `ex07.c` | `gcc -Wall -Wextra ex07.c -o ex07 && ./ex07` |
| 8 | `linuxecho.c` | `gcc -Wall -Wextra linuxecho.c -o linuxecho && ./linuxecho "Xin chao" example.txt` |
| 9a | `linuxgrep.c` | `gcc -Wall -Wextra linuxgrep.c -o linuxgrep && ./linuxgrep "Hello" Hello.txt` |
| 9b | `grepdir.c` | `gcc -Wall -Wextra grepdir.c -o grepdir && ./grepdir "Hello" .` |
| 10 | `ex10.c` | `gcc -Wall -Wextra ex10.c -o ex10 && ./ex10` |
| 11 | `ex11.c` | `gcc -Wall -Wextra ex11.c -o ex11 && ./ex11` |
| 12 | `ex12.c` | `gcc -Wall -Wextra ex12.c -o ex12 && ./ex12` |
| 13 | `ex13.c` | `gcc -Wall -Wextra ex13.c -o ex13 && ./ex13` |
| 14 | `ex14.c` | `gcc -Wall -Wextra ex14.c -o ex14 && ./ex14` |
| 15 | `ex15.c` | `gcc -Wall -Wextra ex15.c -o ex15 && ./ex15 .` |
| 16 | `ex16.c` | `gcc -Wall -Wextra ex16.c -pthread -o ex16 && ./ex16` |
| 17 | `ex17.c` | `gcc -Wall -Wextra ex17.c -pthread -o ex17 && ./ex17` |
| 18 | `ex18.c` | `gcc -Wall -Wextra ex18.c -pthread -o ex18 && ./ex18` |
| 19a | `ex19_thread.c` | `gcc -Wall -Wextra ex19_thread.c -pthread -o ex19_thread && ./ex19_thread` |
| 19b | `ex19_process.c` | `gcc -Wall -Wextra ex19_process.c -o ex19_process && ./ex19_process` |
| 20 | `ex20.c` | `gcc -Wall -Wextra ex20.c -pthread -o ex20 && ./ex20` |
| 21 | `ex21.c` | `gcc -Wall -Wextra ex21.c -pthread -o ex21 && ./ex21` |
| 22 | `ex22.c` | `gcc -Wall -Wextra ex22.c -pthread -o ex22 && ./ex22` |
| 23 | `ex23.c` | `gcc -Wall -Wextra ex23.c -pthread -o ex23 && ./ex23` |
| 24 | `ex24.c` | `gcc -Wall -Wextra ex24.c -pthread -o ex24 && ./ex24` |
| 25 | `ex25.c` | `gcc -Wall -Wextra ex25.c -pthread -o ex25 && ./ex25` |
