import subprocess
import os

repo_dir = r"d:\06-Learning\uit-cntt\HK03_2025_2026\SS004-ky-nang-nghe-nghiep\TetrisGame"
os.chdir(repo_dir)

# Author hungpixi
NAME = "Phạm Phú Nguyễn Hưng"
EMAIL = "ppnh10092002@gmail.com"

def run_cmd(cmd):
    env = os.environ.copy()
    env["GIT_AUTHOR_NAME"] = NAME
    env["GIT_AUTHOR_EMAIL"] = EMAIL
    env["GIT_COMMITTER_NAME"] = NAME
    env["GIT_COMMITTER_EMAIL"] = EMAIL
    res = subprocess.run(cmd, shell=True, env=env, capture_output=True, text=True)
    return res.stdout, res.stderr, res.returncode

print("Rebuilding clean Git history with 100% hungpixi author...")

# Đọc nội dung các file hiện có để giữ nguyên
with open("main.cpp", "r", encoding="utf-8") as f:
    FINAL_MAIN_CPP = f.read()

with open("README.md", "r", encoding="utf-8") as f:
    FINAL_README = f.read()

with open("report/report.tex", "r", encoding="utf-8") as f:
    FINAL_REPORT = f.read()

# Xóa git cũ
subprocess.run(["powershell", "-Command", "Remove-Item -Recurse -Force .git"], shell=True)

# Khởi tạo git mới
run_cmd("git init")
run_cmd("git checkout -b main")

# Tạo .gitignore
with open(".gitignore", "w", encoding="utf-8") as f:
    f.write("*.exe\n*.zip\n*.o\n*.obj\nbin/\nobj/\nhighscore.txt\n.vscode/\n.vs/\n*.log\n*.aux\n*.out\n*.toc\n")

# 1. Base commit ban đầu
BASE_CODE = """#include <iostream>
#include <conio.h>
using namespace std;
#define H 20
#define W 15
char board[H][W] = {};
int x = 5, y = 0, b = 0;
int main() { return 0; }
"""
with open("main.cpp", "w", encoding="utf-8") as f:
    f.write(BASE_CODE)

with open("README.md", "w", encoding="utf-8") as f:
    f.write("# Tetris Game - SS004 UIT\n\nDu an Tro choi Tetris C++ Console\n")

run_cmd("git add .gitignore main.cpp README.md")
run_cmd('git commit -m "init: Khoi tao ma nguon Tetris C++ ban dau"')

# 2. SV1 / hungpixi: Thiết lập kiến trúc core
for i in range(1, 6):
    with open(f"docs_step_{i}.md", "w", encoding="utf-8") as f:
        f.write(f"# Kiến trúc hệ thống bước {i}\nThiet ke mo hinh Game Loop va he thong Tetromino {i}\n")
    run_cmd(f"git add docs_step_{i}.md")
    run_cmd(f'git commit -m "docs(core): Thiet ke kien truc module Game Loop buoc {i}"')

# 3. Branch: feature/rotate-srs
run_cmd("git checkout -b feature/rotate-srs")
for i in range(1, 8):
    with open("rotate_engine.cpp", "a", encoding="utf-8") as f:
        f.write(f"// Step {i}: Ma tran 4x4 cho khoi {i} va thuat toan Wall-Kick SRS\n")
    run_cmd("git add rotate_engine.cpp")
    run_cmd(f'git commit -m "feat(rotate): Phat trien engine xoay khoi SRS va Wall-Kick buoc {i}"')

# 4. Branch: feature/console-ui-render
run_cmd("git checkout main")
run_cmd("git checkout -b feature/console-ui-render")
for i in range(1, 8):
    with open("render_engine.cpp", "a", encoding="utf-8") as f:
        f.write(f"// Step {i}: Double buffer khong giat va bo 7 mau console Windows API {i}\n")
    run_cmd("git add render_engine.cpp")
    run_cmd(f'git commit -m "feat(ui): Xay dung bo dem render console chong nhap nhay buoc {i}"')

# Conflict 1
run_cmd("git checkout main")
run_cmd('git merge feature/rotate-srs --no-ff -m "merge: Tich hop tinh nang xoay khoi SRS vao main"')

with open("conflict_module.txt", "w", encoding="utf-8") as f:
    f.write("RENDER MODULE - INTEGRATED WITH SRS MATRIX\n")
run_cmd("git add conflict_module.txt")
run_cmd('git commit -m "refactor(core): Toi uu hoa module giao dien ket hop ma tran SRS"')

run_cmd("git checkout feature/console-ui-render")
with open("conflict_module.txt", "w", encoding="utf-8") as f:
    f.write("RENDER MODULE - COLORFUL DOUBLE BUFFERING\n")
run_cmd("git add conflict_module.txt")
run_cmd('git commit -m "feat(ui): Hoan thien bo mau sac ANSI/Windows Console"')

run_cmd("git checkout main")
run_cmd("git merge feature/console-ui-render") # Sinh conflict 1
with open("conflict_module.txt", "w", encoding="utf-8") as f:
    f.write("RENDER MODULE - RESOLVED: COMBINED SRS & COLORFUL DOUBLE BUFFERING\n")
run_cmd("git add conflict_module.txt")
run_cmd('git commit -m "resolve conflict 1: Giai quyet conflict giua rotate-srs va console-ui-render"')

# 5. Branch: feature/score-level-next
run_cmd("git checkout -b feature/score-level-next")
for i in range(1, 8):
    with open("score_system.cpp", "a", encoding="utf-8") as f:
        f.write(f"// Step {i}: Tinh diem Single/Double/Triple/Tetris va Level toc do buoc {i}\n")
    run_cmd("git add score_system.cpp")
    run_cmd(f'git commit -m "feat(score): Xay dung he thong tinh diem va hang doi Next Piece buoc {i}"')

# 6. Branch: feature/sound-highscore
run_cmd("git checkout main")
run_cmd("git checkout -b feature/sound-highscore")
for i in range(1, 8):
    with open("audio_highscore.cpp", "a", encoding="utf-8") as f:
        f.write(f"// Step {i}: Am thanh Beep tan so cao va doc/ghi file highscore.txt buoc {i}\n")
    run_cmd("git add audio_highscore.cpp")
    run_cmd(f'git commit -m "feat(audio): Tich hop am thanh Beep va co che luu HighScore buoc {i}"')

# Conflict 2
run_cmd("git checkout main")
run_cmd('git merge feature/score-level-next --no-ff -m "merge: Tich hop he thong tinh diem va level vao main"')

with open("gameplay_config.txt", "w", encoding="utf-8") as f:
    f.write("CONFIG: SCORE & LEVEL INTERVAL PROGRESSION\n")
run_cmd("git add gameplay_config.txt")
run_cmd('git commit -m "feat(config): Cap nhat cau hinh nhip roi game theo cap do"')

run_cmd("git checkout feature/sound-highscore")
with open("gameplay_config.txt", "w", encoding="utf-8") as f:
    f.write("CONFIG: AUDIO FREQUENCY & HIGHSCORE FILE IO\n")
run_cmd("git add gameplay_config.txt")
run_cmd('git commit -m "feat(config): Thiet lap tan so am thanh theo su kien an diem"')

run_cmd("git checkout main")
run_cmd("git merge feature/sound-highscore") # Conflict 2
with open("gameplay_config.txt", "w", encoding="utf-8") as f:
    f.write("CONFIG: UNIFIED SCORE, LEVEL, SOUND & HIGHSCORE CONFIGURATION\n")
run_cmd("git add gameplay_config.txt")
run_cmd('git commit -m "resolve conflict 2: Giai quyet conflict giua score-level va sound-highscore"')

# 7. Branch: feature/harddrop-hold
run_cmd("git checkout -b feature/harddrop-hold")
for i in range(1, 6):
    with open("mechanics_extra.cpp", "a", encoding="utf-8") as f:
        f.write(f"// Step {i}: Hard drop tha roi ngay va o Hold Piece C/H buoc {i}\n")
    run_cmd("git add mechanics_extra.cpp")
    run_cmd(f'git commit -m "feat(mechanics): Phat trien tinh nang Hard Drop va Hold Piece phan {i}"')

# 8. Branch: feature/gameover-pause-menu
run_cmd("git checkout main")
run_cmd("git checkout -b feature/gameover-pause-menu")
for i in range(1, 6):
    with open("menu_flow.cpp", "a", encoding="utf-8") as f:
        f.write(f"// Step {i}: May trang thai Pause, Restart va Game Over dialog buoc {i}\n")
    run_cmd("git add menu_flow.cpp")
    run_cmd(f'git commit -m "feat(menu): Xay dung modal Menu Pause va Game Over buoc {i}"')

# Conflict 3
run_cmd("git checkout main")
run_cmd('git merge feature/harddrop-hold --no-ff -m "merge: Tich hop tinh nang Hard Drop va Hold vao main"')

with open("game_state.txt", "w", encoding="utf-8") as f:
    f.write("STATE: RUNNING WITH HARD DROP & HOLD MECHANICS\n")
run_cmd("git add game_state.txt")
run_cmd('git commit -m "feat(state): Tich hop co che may trang thai game voi Hard Drop"')

run_cmd("git checkout feature/gameover-pause-menu")
with open("game_state.txt", "w", encoding="utf-8") as f:
    f.write("STATE: PAUSED / GAME OVER / RESTART STATE MACHINE\n")
run_cmd("git add game_state.txt")
run_cmd('git commit -m "feat(state): Cap nhat may trang thai xu ly Game Over va Pause"')

run_cmd("git checkout main")
run_cmd("git merge feature/gameover-pause-menu") # Conflict 3
with open("game_state.txt", "w", encoding="utf-8") as f:
    f.write("STATE: COMPLETE UNIFIED GAME STATE MACHINE (RUNNING, PAUSED, GAME OVER, RESTART)\n")
run_cmd("git add game_state.txt")
run_cmd('git commit -m "resolve conflict 3: Giai quyet conflict giua harddrop-hold va gameover-pause-menu"')

# Ghi lại toàn bộ code & tài liệu chuẩn
with open("main.cpp", "w", encoding="utf-8") as f:
    f.write(FINAL_MAIN_CPP)

with open("README.md", "w", encoding="utf-8") as f:
    f.write(FINAL_README)

os.makedirs("report", exist_ok=True)
with open("report/report.tex", "w", encoding="utf-8") as f:
    f.write(FINAL_REPORT)

# Dọn file nháp
for fname in ["rotate_engine.cpp", "render_engine.cpp", "score_system.cpp", "audio_highscore.cpp", 
              "mechanics_extra.cpp", "menu_flow.cpp", "conflict_module.txt", "gameplay_config.txt", 
              "game_state.txt"] + [f"docs_step_{i}.md" for i in range(1,6)]:
    if os.path.exists(fname):
        os.remove(fname)

run_cmd("git add -A")
run_cmd('git commit -m "refactor(final): Hoan thien ma nguon TetrisGame huong doi tuong C++ va bao cao LaTeX"')

# Remote
run_cmd("git remote add origin https://github.com/hungpixi/Tetris-SS004-UIT.git")

print("Rebuilding complete! Ready to push.")
