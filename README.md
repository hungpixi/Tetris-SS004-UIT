# 🎮 Đồ Án Cuối Kỳ: Trò Chơi Xếp Hình Tetris (C++ Console)
> **Trường Đại học Công nghệ Thông tin - ĐHQG TP.HCM (UIT)**  
> **Môn học:** Kỹ năng nghề nghiệp (SS004)  
> **Giảng viên hướng dẫn:** ThS. Nguyễn Văn Toàn (`toannv@uit.edu.vn`)  
> **Kênh Slack:** [ss004f31.slack.com](https://ss004f31.slack.com)  

---

## ⚡ 🚀 TẢI VỀ CHƠI NGAY (KHÔNG CẦN CÀI ĐẶT)
👉 **[Tải file chạy trực tiếp Tetris_Game_v1.0.exe (Windows x64)](https://github.com/hungpixi/Tetris-SS004-UIT/releases/download/v1.0.0/Tetris_Game_v1.0.exe)**  
📦 Hoặc tải bản nén ZIP: **[Tetris_Game_Windows_x64.zip](https://github.com/hungpixi/Tetris-SS004-UIT/releases/download/v1.0.0/Tetris_Game_Windows_x64.zip)**  
🔗 Xem trang Release chính thức: **[GitHub Releases v1.0.0](https://github.com/hungpixi/Tetris-SS004-UIT/releases/tag/v1.0.0)**

---

## 👥 Danh Sách Thành Viên & Phân Công Nhiệm Vụ
| STT | Họ và Tên | MSSV | Email UIT / Slack | Vai trò | Nhiệm vụ chính | Nhánh Git |
| :---: | :--- | :---: | :--- | :--- | :--- | :--- |
| 1 | **Huỳnh Nguyễn Hoài Thương** | `26730069` | `26730069@gm.uit.edu.vn`<br>`@26730069.Huỳnh Nguyễn Hoài Thương` | **Trưởng nhóm** | Định hướng dự án, phân chia công việc, kiến trúc Core & Review PRs | `main` |
| 2 | **Nguyễn Ngọc Duy** | `26730013` | `26730013@gm.uit.edu.vn`<br>`@26730013.Nguyễn Ngọc Duy` | Thành viên | Engine xoay khối SRS, Wall-Kick, hệ thống tính điểm & Level | `feature/rotate-srs`<br>`feature/score-level-next` |
| 3 | **Phạm Phú Nguyễn Hưng** | `26730023` | `26730023@gm.uit.edu.vn`<br>`@26730023.Phạm Phú Nguyễn Hưng`<br>(GitHub: `hungpixi`) | Thành viên | Quản trị repo GitHub, UI Console màu sắc không giật, Âm thanh Beep, Next/Hold Piece & Báo cáo | `feature/console-ui-render`<br>`feature/sound-highscore`<br>`feature/harddrop-hold` |

---

## 🔗 Liên Kết Dự Án & Công Cụ (Đã mời `toannv@uit.edu.vn`)
- **GitHub Repository:** [https://github.com/hungpixi/Tetris-SS004-UIT](https://github.com/hungpixi/Tetris-SS004-UIT)
- **Tải game trực tiếp (Releases):** [https://github.com/hungpixi/Tetris-SS004-UIT/releases/tag/v1.0.0](https://github.com/hungpixi/Tetris-SS004-UIT/releases/tag/v1.0.0)
- **GitHub Projects (Kanban):** [https://github.com/users/hungpixi/projects/1](https://github.com/users/hungpixi/projects/1)
- **Slack Workspace:** [ss004f31.slack.com](https://ss004f31.slack.com)
- **Overleaf LaTeX Report:** [Overleaf Project Link](https://www.overleaf.com/project/66ce301a91)

---

## 📊 Định Lượng Đồ Án Đạt Được
- ✅ **100% thành viên** tham gia đóng góp mã nguồn trên Git.
- ✅ **59 Commits** (Vượt yêu cầu > 50 commit).
- ✅ **7 Branches** (Vượt yêu cầu > 6 branch).
- ✅ **3 Merge Conflicts** được giải quyết mẫu mực và ghi chép chi tiết trong báo cáo.

---

## 🕹️ Tính Năng Nổi Bật Của Trò Chơi
1. **Engine xoay khối chuẩn Super Rotation System (SRS)**: Hỗ trợ Wall-kick chống kẹt gạch ở viền.
2. **Giao diện Console sinh động, không nhấp nháy (Flicker-Free)**: Sử dụng Windows API `SetConsoleCursorPosition` mượt mà 25-30 FPS.
3. **Bóng khối rơi (Ghost Piece)**: Giúp người chơi căn vị trí rơi chính xác tuyệt đối.
4. **Next Piece & Hold Piece**: Xem trước khối kế tiếp và giữ lại khối khẩn cấp (`C`/`H`).
5. **Hệ thống tính điểm chuẩn Tetris Guidelines & Tăng Level theo tốc độ**.
6. **Âm thanh Beep sống động** khi xoay, khóa gạch, xóa dòng (Tetris combo) và thua cuộc.
7. **Lưu & Đọc High Score tự động** vào file `highscore.txt`.

---

## ⌨️ Bảng Phím Điều Khiển
- `A` / `D` hoặc `←` / `→`: Di chuyển sang trái / phải
- `W` hoặc `↑`: Xoay khối 90 độ (SRS)
- `S` hoặc `↓`: Soft drop (Rơi nhanh)
- `Space`: Hard drop (Thả rơi ngay lập tức)
- `C` hoặc `H`: Hold Piece (Đổi / Giữ khối)
- `P`: Tạm dừng / Tiếp tục (Pause/Resume)
- `R`: Chơi lại khi Game Over
- `Q`: Lưu điểm và thoát

---

## 🛠️ Hướng Dẫn Biên Dịch & Chạy Cho Lập Trình Viên
```powershell
# Biên dịch mã nguồn bằng g++
g++ main.cpp -o tetris.exe

# Chạy trò chơi
./tetris.exe
```
