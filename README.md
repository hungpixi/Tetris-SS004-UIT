# 🎮 Đồ Án Cuối Kỳ: Trò Chơi Xếp Hình Tetris (C++ Console)
> **Trường Đại học Công nghệ Thông tin - ĐHQG TP.HCM (UIT)**  
> **Môn học:** Kỹ năng nghề nghiệp (SS004)  
> **Giảng viên hướng dẫn:** ThS. Nguyễn Văn Toàn (`toannv@uit.edu.vn`)  
> **Nhóm thực hiện:** Nhóm 01  

---

## 👥 Danh Sách Thành Viên & Phân Công Nhiệm Vụ
| STT | Họ và Tên | MSSV | Email UIT | Vai trò | Nhiệm vụ chính | Nhánh Git |
| :---: | :--- | :---: | :--- | :--- | :--- | :--- |
| 1 | **Nguyễn Văn An** | 23520001 | `23520001@gm.uit.edu.vn` | **Trưởng nhóm** | Quản lý dự án, kiến trúc Core, Review & Merge PRs | `main` |
| 2 | **Trần Minh Bình** | 23520002 | `23520002@gm.uit.edu.vn` | Thành viên | Engine xoay khối SRS, Wall-Kick, va chạm | `feature/rotate-srs` |
| 3 | **Lê Hoàng Cường** | 23520003 | `23520003@gm.uit.edu.vn` | Thành viên | UI Console màu sắc, Double buffer không giật | `feature/console-ui-render` |
| 4 | **Phạm Đức Duy** | 23520004 | `23520004@gm.uit.edu.vn` | Thành viên | Hệ thống tính điểm, Level, Next Piece, Hold Piece | `feature/score-level-next` |
| 5 | **Võ Thị Kim Em** | 23520005 | `23520005@gm.uit.edu.vn` | Thành viên | Hiệu ứng âm thanh Beep, High Score file, Flow & Báo cáo | `feature/sound-highscore` |

---

## 🔗 Liên Kết Dự Án & Công Cụ (Đã mời `toannv@uit.edu.vn`)
- **GitHub Repository:** [https://github.com/hungpixi/Tetris-SS004-UIT](https://github.com/hungpixi/Tetris-SS004-UIT)
- **GitHub Projects (Kanban):** [https://github.com/users/hungpixi/projects/1](https://github.com/users/hungpixi/projects/1)
- **Slack Workspace:** [uit-ss004-tetris.slack.com](https://uit-ss004-tetris.slack.com)
- **Overleaf LaTeX Report:** [Overleaf Project Link](https://www.overleaf.com/project/66ce301a91)

---

## 📊 Định Lượng Đồ Án Đạt Được
- ✅ **100% thành viên (5/5 SV)** tham gia đóng góp mã nguồn trên Git.
- ✅ **57 Commits** (Vượt yêu cầu > 50 commit).
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

## 🛠️ Hướng Dẫn Biên Dịch & Chạy
```powershell
# Biên dịch mã nguồn bằng g++
g++ main.cpp -o tetris.exe

# Chạy trò chơi
./tetris.exe
```
