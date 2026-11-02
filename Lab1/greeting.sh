#!/bin/bash
# Name: Vuong Viet Cuong
# Script Name: greeting.sh
# Purpose: Basic system and user information display

# 2. Hiển thị "Hello + username"
echo "Hello $USER"

# 3. Tên và phiên bản hệ điều hành
echo "OS Information: $(uname -s) $(uname -r)"

# 4. GID của user hiện tại
echo "Group ID: $(id -g)"

# 5. Ngày và giờ hiện tại
echo "Current Date & Time: $(date)"

# 6. Danh sách file trong thư mục của user hiện tại
echo "Files in home directory:"
ls -la ~

# 7. Giá trị của các biến TERM, PATH, HOME
echo "TERM: $TERM"
echo "PATH: $PATH"
echo "HOME: $HOME"

# 8. Hiển thị "Goodbye + current time"
echo "Goodbye, current time is $(date +'%T')"
