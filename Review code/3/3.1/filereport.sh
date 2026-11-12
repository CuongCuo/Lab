#!/bin/bash
# ==============================================================================
# Tên sinh viên: [Họ và tên sinh viên]
# Tên script: filereport.sh
# Mục đích của chương trình: Thu thập và hiển thị thông tin về các tệp trong thư
# mục hiện tại, bao gồm đường dẫn tuyệt đối, danh sách các mục (cả mục ẩn), 
# đếm số lượng tệp thông thường (regular files), đếm số lượng tệp .txt, hiển thị
# trên màn hình đồng thời lưu kết quả vào filereport.txt.
# ==============================================================================

# Hàm tạo báo cáo
tao_bao_cao() {
    echo "==================== BÁO CÁO TỆP TIN HIỆN TẠI ===================="
    
    # b) Hiển thị đường dẫn tuyệt đối của thư mục hiện tại
    echo "1. Đường dẫn tuyệt đối của thư mục hiện tại:"
    pwd
    echo ""

    # c) Liệt kê tất cả các tệp và thư mục, bao gồm cả các mục ẩn
    echo "2. Danh sách tất cả tệp và thư mục (bao gồm mục ẩn):"
    ls -la
    echo ""

    # d) Đếm và hiển thị số lượng tệp thông thường (regular files)
    so_tep_thuong=$(find . -maxdepth 1 -type f | wc -l)
    echo "3. Số lượng tệp thông thường (regular files): $so_tep_thuong"

    # e) Đếm và hiển thị số lượng tệp thông thường có phần mở rộng .txt
    so_tep_txt=$(find . -maxdepth 1 -type f -name "*.txt" | wc -l)
    echo "4. Số lượng tệp thông thường có phần mở rộng .txt: $so_tep_txt"
    
    echo "=================================================================="
}

# g) Hiển thị báo cáo ra màn hình đồng thời lưu vào tệp filereport.txt
tao_bao_cao | tee filereport.txt

