# Đồ Án Cuối Kỳ: Trò Chơi Tetris (Xếp Gạch) 🎮

Báo cáo và mã nguồn đồ án cuối kỳ môn **Kỹ năng nghề nghiệp (SS004)** - Trường Đại học Công nghệ Thông tin, ĐHQG-HCM (UIT).

---

## 📌 Thông Tin Chung

- **Môn học:** Kỹ năng nghề nghiệp (SS004)
- **Mã lớp:** SS004.F31.CN1.CNTT
- **Đề tài:** Xây dựng và phát triển trò chơi Tetris (Console C++)
- **Năm học:** 2025 - 2026

### 👥 Danh sách thành viên nhóm

| STT | Họ và Tên | MSSV | Vai trò |
| :---: | :--- | :---: | :---: |
| 1 | Phạm Ngọc Hoàng Long | 26730046 | Nhóm trưởng |
| 2 | Huỳnh Thị Kim Anh | 26730002 | Thành viên |
| 3 | Hoàng Gia Huy | 26730026 | Thành viên |
| 4 | Lê Thành Nam | 26730050 | Thành viên |
| 5 | Phạm Mạnh Thiên Phúc | 26730057 | Thành viên |

---

## 📂 Cấu Trúc Thư Mục Dự Án

```text
Tetris/
├── README.md                           # Tài liệu giới thiệu tổng quan dự án
│
├── tetris/                             # Mã nguồn trò chơi
│   └── main.cpp                        # File mã nguồn C++ chính (Console Tetris)
│
└── latex/                              # Dự án báo cáo học thuật LaTeX
    ├── main.tex                        # Master file LaTeX tổng hợp toàn bộ báo cáo
    ├── assest/                         # Thư mục hình ảnh & tài nguyên
    │   └── Logo_uit.jpg                # Logo trường ĐH Công nghệ Thông tin (UIT)
    │
    ├── 01_hop_dong_nhom/               # Mục 1: Hợp đồng nhóm & bảng chữ ký xác nhận
    ├── 02_cac_lien_ket/                # Mục 2: Tổng hợp liên kết Trello, Git, Slack, Overleaf
    ├── 03_gioi_thieu_va_huong_dan/     # Mục 3: Giới thiệu game & hướng dẫn điều khiển
    ├── 04_tai_lieu_ky_thuat/           # Mục 4: Tài liệu kỹ thuật, Game Loop & thuật toán
    ├── 05_qua_trinh_lam_viec_nhom/     # Mục 5: Kế hoạch, phân công & nhật ký làm việc
    ├── 06_ky_nang_ap_dung/             # Mục 6: Kỹ năng mềm, kỹ năng chuyên môn & quản trị
    ├── 07_danh_gia_hop_dong/           # Mục 7: Tiêu chí, tự đánh giá đóng góp & bài học
    │
    └── _output/                        # Thư mục chứa file PDF kết quả sau biên dịch
        └── main.pdf                    # File PDF báo cáo hoàn chỉnh
```

## 🔗 Các Liên Kết Dự Án

- **Trello (Quản lý tiến độ):** [https://trello.com/invite/b/6aa188aa2f75faeccf5ebbaf/ATTI1a9f8836e1c759ebe41c00396a016869FF68DB50/tetris](https://trello.com/invite/b/6aa188aa2f75faeccf5ebbaf/ATTI1a9f8836e1c759ebe41c00396a016869FF68DB50/tetris)
- **GitHub (Quản lý source):** [https://github.com/26730046/Tetris](https://github.com/26730046/Tetris)
- **Overleaf (Soạn thảo LaTeX):** [https://www.overleaf.com/read/kpymwszxcbmn#4c9919](https://www.overleaf.com/read/kpymwszxcbmn#4c9919)
- **Slack (Kênh trao đổi nhóm):** [https://app.slack.com/client/T0BGG4XP66M/C0BV4TA3E0N](https://app.slack.com/client/T0BGG4XP66M/C0BV4TA3E0N)

---

## 📅 Phân Công Công Việc (Tuần 2)

**Mục tiêu:** Ứng dụng Git vào làm việc nhóm và phát triển các tính năng cốt lõi của game Tetris đồng thời.

- **SV1 - Phạm Ngọc Hoàng Long (Nhóm trưởng / PM):**
  - Khởi tạo Git repository cho dự án.
  - Xóa hàm `removeLine` khỏi code gốc và đưa bộ code cơ sở (cấu trúc dữ liệu cơ bản) lên branch `main`.
  - Hỗ trợ các thành viên khác, review code trên Pull Request và thực hiện merge code vào nhánh `main` khi đã hoàn thiện.
- **SV2 - Huỳnh Thị Kim Anh:** 
  - Tạo branch riêng để làm việc.
  - Lập trình hàm `removeLine()` (xử lý logic xóa dòng khi gạch lấp đầy hàng ngang và kéo các khối bên trên xuống).
- **SV3 - Hoàng Gia Huy:** 
  - Tạo branch riêng để làm việc.
  - Viết lại giao diện hiển thị bảng và các khối gạch sao cho hình dáng trông vuông vức hơn (vì console hiện hành hiển thị dạng hình chữ nhật đứng).
- **SV4 - Lê Thành Nam:** 
  - Tạo branch riêng để làm việc.
  - Nghiên cứu thuật toán xoay block và lập trình chức năng xoay khi người dùng nhấn phím điều hướng.
- **SV5 - Phạm Mạnh Thiên Phúc:** 
  - Tạo branch riêng để làm việc.
  - Viết logic tăng độ khó: mỗi khi nhóm xoá được dòng (gọi hàm `removeLine` thành công), tốc độ rơi của khối sẽ được tăng lên (thời gian `sleep` giảm xuống).


## 📅 Phân Công Công Việc (Tuần 3)

**Mục tiêu:** Phát triển game.

- **SV1 - Phạm Ngọc Hoàng Long (Nhóm trưởng / PM):**
  - Tạo Abstract Base Class Block chứa thuộc tính char shape[4][4].
  - Khai báo các hàm ảo: virtual void rotate() và có thể là virtual Block* clone() (hoặc undoRotate()) để hỗ trợ việc khôi phục trạng thái nếu xoay bị vướng tường.
  - Thay thế các mảng blocks và current toàn cục bằng con trỏ Block* currentBlock.
  - Quản lý bộ nhớ ở hàm main: Thêm logic delete currentBlock khi kết thúc khối cũ trước khi gọi khối mới.
  - Hỗ trợ các thành viên khác, review code trên Pull Request và thực hiện merge code vào nhánh `main` khi đã hoàn thiện.
- **SV2 - Hoàng Gia Huy:** 
  - Viết 7 class con kế thừa từ Block: IBlock, OBlock, TBlock, SBlock, ZBlock, JBlock, LBlock.
  - Thiết lập ma trận đặc trưng cho từng khối bên trong hàm khởi tạo (constructor) của chúng.
  - Sửa hàm loadCurrent() thành mô hình giống Factory Pattern: Sử dụng lệnh switch-case dựa trên biến b (từ 0-6) để new ra một đối tượng khối tương ứng và gán cho currentBlock.
- **SV3 - Phạm Mạnh Thiên Phúc:** 
  - Viết hàm rotate() mặc định trong class Block (thuật toán xoay ma trận 4x4 góc 90 độ theo chiều kim đồng hồ).
  - Ghi đè (override) hàm rotate() cho OBlock (xoay khối vuông thì không cần làm gì cả).
  - Ghi đè (override) hàm rotate() cho IBlock hoặc các khối đặc biệt khác nếu cần giới hạn trạng thái xoay (ví dụ khối chữ I chỉ xoay ngang và dọc).
- **SV4 - Lê Thành Nam:** 
  - Sửa lại hàm canPlace(...): Thay vì nhận mảng char shape[4][4], hãy sửa để nhận object Block* (hoặc trực tiếp gọi currentBlock->shape).
  - Sửa lại hàm block2Board() (chép khối vào bảng).
  - Sửa lại hàm boardDelBlock() (xóa khối khỏi bảng).
  - Đảm bảo logic vẽ hình (draw()) vẫn hiển thị đúng.
- **SV5 - Huỳnh Thị Kim Anh:** 
  - Viết lại luồng xử lý phím w trong hàm main().
  - Sửa hàm rotate() toàn cục cũ thành cơ chế thử xoay:
    - Lưu trạng thái / hoặc clone currentBlock ra một bản nháp.
    - Gọi hàm đa hình currentBlock->rotate().
    - Áp dụng thuật toán Wall Kicks (thử các tọa độ lân cận x + kicks[k]) và dùng hàm canPlace() của Người 4 để kiểm tra.
    - Nếu không có vị trí nào hợp lệ, khôi phục lại trạng thái cũ của khối. Nếu hợp lệ, cập nhật tọa độ x, y.


**Quy trình nộp bài:** Các thành viên sẽ tiến hành lập trình đồng thời trên các nhánh của mình. Xong việc thì submit (Push) lên Git repository và tạo yêu cầu gộp mã (Merge). Nhóm trưởng sẽ kiểm tra code ổn định trước khi hợp nhất.


## 📅 Phân Công Công Việc (Tuần 4)

**Mục tiêu:** Hoàn thiện nâng cấp game Tetris và hoàn thành bộ tài liệu báo cáo kỹ thuật trên LaTeX.

- **SV1 - Phạm Ngọc Hoàng Long (Nhóm trưởng / PM):**
  - Trực tiếp lập trình phần Nâng cấp Game: Thêm tính năng Ghost Piece, Hard Drop, Next Block Preview, thuật toán 7-Bag Randomizer, Hệ thống tính điểm & Level, giao diện màu sắc/Pause.
  - Quản lý tiến độ chung của tuần 4.
  - Biên tập, chỉnh sửa và tổng hợp master file Latex cuối cùng (đảm bảo layout, hình ảnh), xuất ra file PDF hoàn chỉnh.
- **SV2 - Huỳnh Thị Kim Anh:**
  - Phụ trách Latex phần: **Đánh giá việc thực hiện hợp đồng nhóm** (dựa theo tiêu chí ở hợp đồng nhóm).
  - Phối hợp kiểm thử (test) các tính năng game mới, rà soát lỗi và hỗ trợ cung cấp mô tả giải thuật cho báo cáo.
- **SV3 - Hoàng Gia Huy:**
  - Phụ trách Latex phần: **Tài liệu kỹ thuật của trò chơi** (Độ dài: 2 - 10 trang).
  - Giới thiệu các chức năng chính, các class/struct quan trọng, mô tả cấu trúc chương trình tổng thể. Vẽ diagram (sơ đồ lớp, sơ đồ luồng) để mô tả cách tổ chức dữ liệu và giải thuật (Lưu ý: Không copy nguyên code).
- **SV4 - Lê Thành Nam:**
  - Phụ trách Latex phần: **Mô tả quá trình làm việc nhóm** (Độ dài: 2 - 5 trang).
  - Thu thập minh chứng trên Trello/Git/Slack. Nêu rõ các giai đoạn, khó khăn đã gặp và cách giải quyết, đánh giá quá trình phân chia và phân chia lại công việc của các thành viên.
- **SV5 - Phạm Mạnh Thiên Phúc:**
  - Phụ trách Latex phần: **Các kỹ năng mà nhóm đã áp dụng trong đồ án này** (Độ dài: 1 - 3 trang).
  - Trình bày cụ thể các kỹ năng mềm và công cụ thực tế đã vận dụng trong đồ án.

**Quy trình nộp bài Tuần 4:** Mã nguồn nâng cấp game gộp lên nhánh `main` của GitHub. Mã nguồn Latex gộp trên dự án Overleaf chung. Các thành viên phải tuân thủ đúng số trang quy định của từng phần báo cáo.
