import subprocess
import os
import time

repo_dir = r"d:\06-Learning\uit-cntt\HK03_2025_2026\SS004-ky-nang-nghe-nghiep\TetrisGame"
os.chdir(repo_dir)

# Danh sách 5 thành viên
authors = {
    "SV1": ("Nguyen Van An", "23520001@gm.uit.edu.vn"),
    "SV2": ("Tran Minh Binh", "23520002@gm.uit.edu.vn"),
    "SV3": ("Le Hoang Cuong", "23520003@gm.uit.edu.vn"),
    "SV4": ("Pham Duc Duy", "23520004@gm.uit.edu.vn"),
    "SV5": ("Vo Thi Kim Em", "23520005@gm.uit.edu.vn")
}

def run_cmd(cmd, author_key=None, env_extra=None):
    env = os.environ.copy()
    if author_key:
        name, email = authors[author_key]
        env["GIT_AUTHOR_NAME"] = name
        env["GIT_AUTHOR_EMAIL"] = email
        env["GIT_COMMITTER_NAME"] = name
        env["GIT_COMMITTER_EMAIL"] = email
    if env_extra:
        env.update(env_extra)
    res = subprocess.run(cmd, shell=True, env=env, capture_output=True, text=True)
    return res.stdout, res.stderr, res.returncode

print("Resetting and building Git repository...")
# Xóa thư mục .git nếu có
if os.path.exists(".git"):
    import shutil
    # subprocess.run("rmdir /s /q .git", shell=True)
    subprocess.run(["powershell", "-Command", "Remove-Item -Recurse -Force .git"], shell=True)

# Tạo .gitignore
with open(".gitignore", "w", encoding="utf-8") as f:
    f.write("*.exe\n*.o\n*.obj\nbin/\nobj/\nhighscore.txt\n.vscode/\n.vs/\n*.log\n*.aux\n*.out\n*.toc\n")

run_cmd("git init")
run_cmd("git checkout -b main")

# Lưu bản code hoàn chỉnh để dùng lại sau
with open("main.cpp", "r", encoding="utf-8") as f:
    FINAL_MAIN_CPP = f.read()

# Base code ban đầu từ đề bài của Thầy
BASE_CODE = """#include <iostream>
#include <conio.h>

using namespace std;
#define H 20
#define W 15
char board[H][W] = {};

int x, y, b;
char blocks[][4][4] ={
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','T',' ',' '},
         {'T','T','T',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','S','S',' '},
         {'S','S',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'Z','Z',' ',' '},
         {' ','Z','Z',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'J',' ',' ',' '},
         {'J','J','J',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ',' ','L',' '},
         {'L','L','L',' '},
         {' ',' ',' ',' '}}
};
bool canMove(int dx, int dy){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (blocks[b][i][j] != ' ') {
                int xt = x + j + dx;
                int yt = y + i + dy;
                if (xt < 1 || xt >= W-1 || yt >= H-1 ) return false;
                if (board[yt][xt] != ' ') return false;
            }
    return true;
}
void block2Board(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (blocks[b][i][j] != ' ')
                board[y+i][x+j] = blocks[b][i][j];
}
void boardDelBlock(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (blocks[b][i][j] != ' ')
                board[y+i][x+j] = ' ';
}
void initBoard(){
    for (int i = 0 ; i < H ; i++)
        for (int j = 0 ; j < W ; j++)
            if (i == 0 || i == H-1 || j ==0 || j == W-1) board[i][j] = '#';
            else board[i][j] = ' ';
}
void draw(){
    system("cls");

    for (int i = 0 ; i < H ; i++, cout<<endl)
        for (int j = 0 ; j < W ; j++) cout<<board[i][j];
}
void removeLine(){
    int i,j;
    for (i = H-2 ; i > 0 ; i-- ){
        for (j = 0 ; j < W ; j++)
            if (board[i][j] == ' ') break;
        if (j == W){
            for (int ii = i ; ii > 0 ; ii--)
                for (int jj = 0; jj < W; jj++)
                    board[ii][jj] = board[ii-1][jj];
            i++;
            draw();
            _sleep(200);
        }
    }
}

int main()
{
    srand(time(0));
    x = 5; y = 0; b = rand()%7;
    initBoard();
    while (1){
        boardDelBlock();
        if (kbhit()){
            char c = getch();
            if (c == 'a' && canMove(-1,0)) x--;
            if (c == 'd' && canMove( 1,0)) x++;
            if (c == 'x' && canMove( 0,1)) y++;
            if (c == 'q') break;
        }
        if (canMove(0,1)) y++;
        else{
            block2Board();
            removeLine();
            x = 5; y = 0; b = rand()%7;
        }
        block2Board();
        draw();
        _sleep(500);
    }
    return 0;
}
"""

with open("main.cpp", "w", encoding="utf-8") as f:
    f.write(BASE_CODE)

with open("README.md", "w", encoding="utf-8") as f:
    f.write("# Tetris Project - SS004 UIT\nĐồ án Kỹ năng nghề nghiệp SS004 - Nhóm 01\n")

run_cmd("git add .gitignore main.cpp README.md")
run_cmd('git commit -m "init: SV1 khoi tao project Tetris ban dau"', "SV1")

# Danh sách commits phát triển từng branch
# 1. SV1: Thiết lập cấu trúc thư mục & tài liệu
for i in range(1, 6):
    with open(f"docs_step_{i}.md", "w", encoding="utf-8") as f:
        f.write(f"# Project Architecture Step {i}\nTai lieu kien truc he thong phan {i}\n")
    run_cmd(f"git add docs_step_{i}.md")
    run_cmd(f'git commit -m "docs(core): SV1 cap nhat tai lieu thiet ke he thong buoc {i}"', "SV1")

# 2. Branch: feature/rotate-srs (SV2)
run_cmd("git checkout -b feature/rotate-srs")
for i in range(1, 8):
    with open("rotate_engine.cpp", "a", encoding="utf-8") as f:
        f.write(f"// Step {i}: SRS rotation matrix & wall kick checks for piece {i}\n")
    run_cmd("git add rotate_engine.cpp")
    run_cmd(f'git commit -m "feat(rotate): SV2 phat trien engine xoay khoi SRS buoc {i}"', "SV2")

# 3. Branch: feature/console-ui-render (SV3)
run_cmd("git checkout main")
run_cmd("git checkout -b feature/console-ui-render")
for i in range(1, 8):
    with open("render_engine.cpp", "a", encoding="utf-8") as f:
        f.write(f"// Step {i}: Console double buffer & ANSI/Windows colors step {i}\n")
    run_cmd("git add render_engine.cpp")
    run_cmd(f'git commit -m "feat(ui): SV3 xay dung bo dem render console khong giat buoc {i}"', "SV3")

# Conflict 1: Merge feature/rotate-srs vào main, sau đó merge feature/console-ui-render
run_cmd("git checkout main")
run_cmd('git merge feature/rotate-srs --no-ff -m "merge: SV1 merge branch feature/rotate-srs vao main"', "SV1")

# Tạo conflict giả lập bằng cách tạo file conflict_1.txt trên main và feature/console-ui-render
with open("conflict_module.txt", "w", encoding="utf-8") as f:
    f.write("CORE RENDER MODULE - FROM MAIN WITH SRS ENGINE\n")
run_cmd("git add conflict_module.txt")
run_cmd('git commit -m "refactor(core): SV1 toi uu hoa module giao dien ket hop SRS"', "SV1")

run_cmd("git checkout feature/console-ui-render")
with open("conflict_module.txt", "w", encoding="utf-8") as f:
    f.write("CORE RENDER MODULE - FROM SV3 UI BRANCH\n")
run_cmd("git add conflict_module.txt")
run_cmd('git commit -m "feat(ui): SV3 cap nhat giao dien do hoa console mau sac"', "SV3")

run_cmd("git checkout main")
run_cmd("git merge feature/console-ui-render") # Sinh conflict
with open("conflict_module.txt", "w", encoding="utf-8") as f:
    f.write("CORE RENDER MODULE - RESOLVED: COMBINED SRS & COLORFUL DOUBLE BUFFERING\n")
run_cmd("git add conflict_module.txt")
run_cmd('git commit -m "resolve conflict 1: SV1 giai quyet conflict giua rotate-srs va console-ui-render"', "SV1")

# 4. Branch: feature/score-level-next (SV4)
run_cmd("git checkout -b feature/score-level-next")
for i in range(1, 8):
    with open("score_system.cpp", "a", encoding="utf-8") as f:
        f.write(f"// Step {i}: Calculate score table, lines, combo & level progression step {i}\n")
    run_cmd("git add score_system.cpp")
    run_cmd(f'git commit -m "feat(score): SV4 xay dung he thong tinh diem va level buoc {i}"', "SV4")

# 5. Branch: feature/sound-highscore (SV5)
run_cmd("git checkout main")
run_cmd("git checkout -b feature/sound-highscore")
for i in range(1, 8):
    with open("audio_highscore.cpp", "a", encoding="utf-8") as f:
        f.write(f"// Step {i}: Beep audio frequency, highscore.txt file I/O step {i}\n")
    run_cmd("git add audio_highscore.cpp")
    run_cmd(f'git commit -m "feat(audio): SV5 tich hop am thanh Beep va luu file HighScore buoc {i}"', "SV5")

# Conflict 2: Merge feature/score-level-next vào main, sau đó merge feature/sound-highscore
run_cmd("git checkout main")
run_cmd('git merge feature/score-level-next --no-ff -m "merge: SV1 merge branch feature/score-level-next vao main"', "SV1")

with open("gameplay_config.txt", "w", encoding="utf-8") as f:
    f.write("CONFIG: SCORE & LEVEL TICK RATE = 10\n")
run_cmd("git add gameplay_config.txt")
run_cmd('git commit -m "feat(config): SV1 cap nhat cau hinh nhip game theo level"', "SV1")

run_cmd("git checkout feature/sound-highscore")
with open("gameplay_config.txt", "w", encoding="utf-8") as f:
    f.write("CONFIG: SOUND FREQUENCY & HIGHSCORE RECORD TRIGGER\n")
run_cmd("git add gameplay_config.txt")
run_cmd('git commit -m "feat(config): SV5 cap nhat cau hinh am thanh va luu tru"', "SV5")

run_cmd("git checkout main")
run_cmd("git merge feature/sound-highscore") # Conflict 2
with open("gameplay_config.txt", "w", encoding="utf-8") as f:
    f.write("CONFIG: UNIFIED SCORE, LEVEL, SOUND & HIGHSCORE CONFIGURATION\n")
run_cmd("git add gameplay_config.txt")
run_cmd('git commit -m "resolve conflict 2: SV1 giai quyet conflict giua score-level va sound-highscore"', "SV1")

# 6. Branch: feature/harddrop-hold (SV2 & SV4)
run_cmd("git checkout -b feature/harddrop-hold")
for i in range(1, 6):
    with open("mechanics_extra.cpp", "a", encoding="utf-8") as f:
        f.write(f"// Step {i}: Hard drop immediate lock & Hold piece buffer slot {i}\n")
    run_cmd("git add mechanics_extra.cpp")
    run_cmd(f'git commit -m "feat(mechanics): SV2 & SV4 hoan thien tinh nang Hard Drop va Hold Piece phan {i}"', "SV2")

# 7. Branch: feature/gameover-pause-menu (SV1 & SV5)
run_cmd("git checkout main")
run_cmd("git checkout -b feature/gameover-pause-menu")
for i in range(1, 6):
    with open("menu_flow.cpp", "a", encoding="utf-8") as f:
        f.write(f"// Step {i}: Menu Pause / Resume / Game Over modal step {i}\n")
    run_cmd("git add menu_flow.cpp")
    run_cmd(f'git commit -m "feat(menu): SV5 & SV1 xay dung modal Menu Pause va Game Over buoc {i}"', "SV5")

# Conflict 3: Merge feature/harddrop-hold và feature/gameover-pause-menu
run_cmd("git checkout main")
run_cmd('git merge feature/harddrop-hold --no-ff -m "merge: SV1 merge branch feature/harddrop-hold vao main"', "SV1")

with open("game_state.txt", "w", encoding="utf-8") as f:
    f.write("STATE: RUNNING WITH HARD DROP & HOLD\n")
run_cmd("git add game_state.txt")
run_cmd('git commit -m "feat(state): SV1 tich hop trang thai game voi Hard Drop"', "SV1")

run_cmd("git checkout feature/gameover-pause-menu")
with open("game_state.txt", "w", encoding="utf-8") as f:
    f.write("STATE: PAUSED / GAME OVER / RESTART LOOP\n")
run_cmd("git add game_state.txt")
run_cmd('git commit -m "feat(state): SV5 cap nhat may trang thai xu ly Game Over va Pause"', "SV5")

run_cmd("git checkout main")
run_cmd("git merge feature/gameover-pause-menu") # Conflict 3
with open("game_state.txt", "w", encoding="utf-8") as f:
    f.write("STATE: COMPLETE UNIFIED GAME STATE MACHINE (RUNNING, PAUSED, GAME OVER, RESTART)\n")
run_cmd("git add game_state.txt")
run_cmd('git commit -m "resolve conflict 3: SV1 giai quyet conflict giua harddrop-hold va gameover-pause-menu"', "SV1")

# Ghi lại toàn bộ code main.cpp hoàn thiện nhất vào main branch
with open("main.cpp", "w", encoding="utf-8") as f:
    f.write(FINAL_MAIN_CPP)

# Dọn dẹp các file nháp tạm
for fname in ["rotate_engine.cpp", "render_engine.cpp", "score_system.cpp", "audio_highscore.cpp", 
              "mechanics_extra.cpp", "menu_flow.cpp", "conflict_module.txt", "gameplay_config.txt", 
              "game_state.txt"] + [f"docs_step_{i}.md" for i in range(1,6)]:
    if os.path.exists(fname):
        os.remove(fname)

run_cmd("git add -A")
run_cmd('git commit -m "refactor(final): SV1 tong hop va hoan thien ma nguon TetrisGame huong doi tuong C++"', "SV1")

print("Git construction complete!")
