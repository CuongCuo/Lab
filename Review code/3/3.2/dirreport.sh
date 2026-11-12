#!/bin/bash
# ==============================================================================
# Tên sinh viên: [Họ và tên sinh viên]
# Tên script: dirreport.sh
# Mục đích của chương trình: Thu thập và hiển thị thông tin về thư mục hiện tại,
# bao gồm đường dẫn, danh sách các file và thư mục, số lượng thư mục con,
# số lượng file thông thường, đồng thời lưu toàn bộ kết quả vào file report.txt.
# ==============================================================================

# Hàm tạo báo cáo
tao_bao_cao() {
    echo "==================== BÁO CÁO THƯ MỤC HIỆN TẠI ===================="
    
    # b) Hiển thị đường dẫn của thư mục hiện tại
    echo "1. Đường dẫn thư mục hiện tại:"
    pwd
    echo ""

    # c) Liệt kê tất cả các file và thư mục trong thư mục hiện tại
    echo "2. Danh sách tất cả file và thư mục:"
    ls -la
    echo ""

    # d) Đếm và hiển thị số lượng thư mục con (chỉ tính các thư mục con trực tiếp)
    so_thu_muc_con=$(find . -maxdepth 1 -mindepth 1 -type d | wc -l)
    echo "3. Số lượng thư mục con: $so_thu_muc_con"

    # e) Đếm và hiển thị số lượng file thông thường (regular files)
    so_file_thuong=$(find . -maxdepth 1 -type f | wc -l)
    echo "4. Số lượng file thông thường (regular files): $so_file_thuong"
    
    echo "=================================================================="
}

# g) Hiển thị báo cáo ra màn hình và lưu toàn bộ kết quả vào file report.txt
tao_bao_cao | tee report.txt

