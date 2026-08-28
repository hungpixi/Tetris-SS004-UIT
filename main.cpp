/**
 * ============================================================================
 * TRƯỜNG ĐẠI HỌC CÔNG NGHỆ THÔNG TIN - ĐHQG TP.HCM
 * KHOA KỸ THUẬT MÁY TÍNH & KHOA HỌC MÁY TÍNH
 * MÔN HỌC: KỸ NĂNG NGHỀ NGHIỆP (SS004)
 * ----------------------------------------------------------------------------
 * ĐỒ ÁN CUỐI KỲ: TRÒ CHƠI TETRIS HOÀN CHỈNH (CONSOLE C++)
 * NHÓM THỰC HIỆN: NHÓM 01
 * CÁC THÀNH VIÊN:
 * 1. SV1: MSSV 23520001 - Nguyễn Văn An   (Trưởng nhóm - Quản lý & Core Architecture)
 * 2. SV2: MSSV 23520002 - Trần Minh Bình  (Xoay khối SRS & Xử lý va chạm)
 * 3. SV3: MSSV 23520003 - Lê Hoàng Cường  (UI/UX Console, Màu sắc & Render không nhấp nháy)
 * 4. SV4: MSSV 23520004 - Phạm Đức Duy    (Điểm số, Level, Next Piece & Hold Piece)
 * 5. SV5: MSSV 23520005 - Võ Thị Kim Em   (Âm thanh Beep, HighScore File & Game Flow)
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

// ==========================================
// CÁC HẰNG SỐ CẤU HÌNH TRÒ CHƠI
// ==========================================
const int BOARD_HEIGHT = 20; // Chiều cao vùng chơi
const int BOARD_WIDTH  = 10; // Chiều rộng vùng chơi
const int OFFSET_X     = 4;  // Tọa độ X vẽ bảng trên Console
const int OFFSET_Y     = 2;  // Tọa độ Y vẽ bảng trên Console

// Màu sắc Console (Windows Console API)
enum ConsoleColor {
    COLOR_BLACK         = 0,
    COLOR_DARK_BLUE     = 1,
    COLOR_DARK_GREEN    = 2,
    COLOR_DARK_CYAN     = 3,
    COLOR_DARK_RED      = 4,
    COLOR_DARK_MAGENTA  = 5,
    COLOR_DARK_YELLOW   = 6,
    COLOR_GRAY          = 7,
    COLOR_DARK_GRAY     = 8,
    COLOR_BLUE          = 9,
    COLOR_GREEN         = 10,
    COLOR_CYAN          = 11,
    COLOR_RED           = 12,
    COLOR_MAGENTA       = 13,
    COLOR_YELLOW        = 14,
    COLOR_WHITE         = 15
};

// 7 loại Tetromino chuẩn
enum TetrominoType {
    PIECE_I = 0,
    PIECE_O = 1,
    PIECE_T = 2,
    PIECE_S = 3,
    PIECE_Z = 4,
    PIECE_J = 5,
    PIECE_L = 6,
    PIECE_NONE = 7
};

// Dữ liệu 4 trạng thái xoay của 7 loại khối (4x4 matrix)
const int PIECES[7][4][4][4] = {
    // 0: Khối I (Cyan)
    {
        {{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
        {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}},
        {{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}},
        {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}}
    },
    // 1: Khối O (Yellow)
    {
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}}
    },
    // 2: Khối T (Purple / Magenta)
    {
        {{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}},
        {{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}
    },
    // 3: Khối S (Green)
    {
        {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
        {{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},
        {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}
    },
    // 4: Khối Z (Red)
    {
        {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},
        {{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}}
    },
    // 5: Khối J (Blue)
    {
        {{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}}
    },
    // 6: Khối L (Orange / Dark Yellow)
    {
        {{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}},
        {{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}}
    }
};

const ConsoleColor PIECE_COLORS[7] = {
    COLOR_CYAN,        // I
    COLOR_YELLOW,      // O
    COLOR_MAGENTA,     // T
    COLOR_GREEN,       // S
    COLOR_RED,         // Z
    COLOR_BLUE,        // J
    COLOR_DARK_YELLOW  // L
};

// ==========================================
// CÁC HÀM TIỆN ÍCH CONSOLE (SV3 & SV5)
// ==========================================
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int textColor, int bgColor = 0) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void playSoundEffect(int type) {
    // SV5: Âm thanh thông báo
    switch (type) {
        case 1: Beep(900, 30); break;   // Move / Rotate
        case 2: Beep(500, 40); break;   // Drop / Lock
        case 3: Beep(1200, 100); break; // Clear line
        case 4:                         // Tetris Clear Combo
            Beep(1000, 80);
            Beep(1400, 80);
            Beep(1800, 120);
            break;
        case 5:                         // Game Over
            Beep(600, 200);
            Beep(400, 200);
            Beep(250, 400);
            break;
    }
}

// ==========================================
// LỚP TETROMINO (SV2: Di chuyển, xoay khối SRS)
// ==========================================
class Piece {
public:
    int type;
    int rotation;
    int x, y;

    Piece() {
        reset(rand() % 7);
    }

    void reset(int t) {
        type = t;
        rotation = 0;
        x = BOARD_WIDTH / 2 - 2;
        y = 0;
    }

    void rotate() {
        rotation = (rotation + 1) % 4;
    }

    void unrotate() {
        rotation = (rotation + 3) % 4;
    }
};

// ==========================================
// LỚP QUẢN LÝ BẢN ĐỒ VÀ ĐIỂM SỐ (SV1, SV4, SV5)
// ==========================================
class TetrisGame {
private:
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    Piece currentPiece;
    Piece nextPiece;
    Piece holdPiece;
    bool canHold;
    bool hasHoldPiece;

    int score;
    int linesCleared;
    int level;
    int highScore;
    bool isGameOver;
    bool isPaused;

    const string HIGH_SCORE_FILE = "highscore.txt";

public:
    TetrisGame() {
        srand((unsigned int)time(0));
        loadHighScore();
        initGame();
    }

    void initGame() {
        for (int r = 0; r < BOARD_HEIGHT; r++) {
            for (int c = 0; c < BOARD_WIDTH; c++) {
                board[r][c] = -1; // -1: ô trống
            }
        }
        score = 0;
        linesCleared = 0;
        level = 1;
        isGameOver = false;
        isPaused = false;
        canHold = true;
        hasHoldPiece = false;

        currentPiece.reset(rand() % 7);
        nextPiece.reset(rand() % 7);
    }

    void loadHighScore() {
        highScore = 0;
        ifstream fin(HIGH_SCORE_FILE);
        if (fin.is_open()) {
            fin >> highScore;
            fin.close();
        }
    }

    void saveHighScore() {
        if (score > highScore) {
            highScore = score;
            ofstream fout(HIGH_SCORE_FILE);
            if (fout.is_open()) {
                fout << highScore;
                fout.close();
            }
        }
    }

    // SV2: Kiểm tra va chạm
    bool isValidPosition(int px, int py, int prot, int ptype) {
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                if (PIECES[ptype][prot][r][c]) {
                    int bx = px + c;
                    int by = py + r;

                    // Ngoài biên
                    if (bx < 0 || bx >= BOARD_WIDTH || by >= BOARD_HEIGHT) return false;
                    // Chạm khối đã đặt
                    if (by >= 0 && board[by][bx] != -1) return false;
                }
            }
        }
        return true;
    }

    // SV2: Xoay khối với cơ chế Wall-kick cơ bản
    void rotatePiece() {
        int oldRot = currentPiece.rotation;
        currentPiece.rotate();
        
        if (!isValidPosition(currentPiece.x, currentPiece.y, currentPiece.rotation, currentPiece.type)) {
            // Thử Wall-kick dịch sang trái 1 ô
            if (isValidPosition(currentPiece.x - 1, currentPiece.y, currentPiece.rotation, currentPiece.type)) {
                currentPiece.x -= 1;
            }
            // Thử Wall-kick dịch sang phải 1 ô
            else if (isValidPosition(currentPiece.x + 1, currentPiece.y, currentPiece.rotation, currentPiece.type)) {
                currentPiece.x += 1;
            }
            // Không xoay được thì trả về vị trí cũ
            else {
                currentPiece.rotation = oldRot;
                return;
            }
        }
        playSoundEffect(1);
    }

    // SV4: Tính năng Hold Piece
    void holdCurrentPiece() {
        if (!canHold) return;

        if (!hasHoldPiece) {
            holdPiece.type = currentPiece.type;
            hasHoldPiece = true;
            currentPiece.reset(nextPiece.type);
            nextPiece.reset(rand() % 7);
        } else {
            int temp = holdPiece.type;
            holdPiece.type = currentPiece.type;
            currentPiece.reset(temp);
        }
        canHold = false;
        playSoundEffect(1);
    }

    // Khóa khối vào bàn chơi khi tiếp đất
    void lockPiece() {
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                if (PIECES[currentPiece.type][currentPiece.rotation][r][c]) {
                    int bx = currentPiece.x + c;
                    int by = currentPiece.y + r;
                    if (by >= 0 && by < BOARD_HEIGHT && bx >= 0 && bx < BOARD_WIDTH) {
                        board[by][bx] = currentPiece.type;
                    }
                }
            }
        }
        playSoundEffect(2);
        clearLines();

        // Đổi khối tiếp theo
        currentPiece.reset(nextPiece.type);
        nextPiece.reset(rand() % 7);
        canHold = true;

        // Nếu khối mới sinh ra mà bị đè -> Game Over
        if (!isValidPosition(currentPiece.x, currentPiece.y, currentPiece.rotation, currentPiece.type)) {
            isGameOver = true;
            saveHighScore();
            playSoundEffect(5);
        }
    }

    // SV4: Xóa hàng đầy & Tính điểm
    void clearLines() {
        int clearedCount = 0;
        for (int r = BOARD_HEIGHT - 1; r >= 0; r--) {
            bool full = true;
            for (int c = 0; c < BOARD_WIDTH; c++) {
                if (board[r][c] == -1) {
                    full = false;
                    break;
                }
            }
            if (full) {
                clearedCount++;
                for (int row = r; row > 0; row--) {
                    for (int col = 0; col < BOARD_WIDTH; col++) {
                        board[row][col] = board[row - 1][col];
                    }
                }
                for (int col = 0; col < BOARD_WIDTH; col++) {
                    board[0][col] = -1;
                }
                r++; // Kiểm tra lại hàng này sau khi đã dồn xuống
            }
        }

        if (clearedCount > 0) {
            linesCleared += clearedCount;
            // Hệ thống điểm chuẩn
            int points = 0;
            switch (clearedCount) {
                case 1: points = 100 * level; playSoundEffect(3); break;
                case 2: points = 300 * level; playSoundEffect(3); break;
                case 3: points = 500 * level; playSoundEffect(3); break;
                case 4: points = 800 * level; playSoundEffect(4); break; // TETRIS!
            }
            score += points;
            level = 1 + linesCleared / 10;
            if (score > highScore) highScore = score;
        }
    }

    // Tính toán bóng khối rơi (Ghost Piece)
    int getGhostY() {
        int gy = currentPiece.y;
        while (isValidPosition(currentPiece.x, gy + 1, currentPiece.rotation, currentPiece.type)) {
            gy++;
        }
        return gy;
    }

    // Hard drop
    void hardDrop() {
        int dropDistance = 0;
        while (isValidPosition(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.type)) {
            currentPiece.y++;
            dropDistance++;
        }
        score += dropDistance * 2;
        lockPiece();
    }

    // SV3: Render giao diện không nhấp nháy
    void render() {
        gotoxy(0, 0);

        // Header
        setColor(COLOR_YELLOW);
        cout << "========================================================\n";
        cout << "   [UIT - SS004] TRO CHOI TETRIS - NHOM 01 (C++ CONSOLE)\n";
        cout << "========================================================\n\n";

        int ghostY = getGhostY();

        // Vẽ Khung Bàn Chơi và Thông Tin Phụ
        for (int r = 0; r < BOARD_HEIGHT; r++) {
            // Lề trái
            gotoxy(OFFSET_X, OFFSET_Y + r + 3);
            setColor(COLOR_WHITE);
            cout << "<!";

            // Vẽ các ô trong dòng
            for (int c = 0; c < BOARD_WIDTH; c++) {
                int cellColor = board[r][c];

                // Kiểm tra xem ô có thuộc khối đang rơi không
                bool isCurrent = false;
                for (int pr = 0; pr < 4; pr++) {
                    for (int pc = 0; pc < 4; pc++) {
                        if (PIECES[currentPiece.type][currentPiece.rotation][pr][pc]) {
                            if (currentPiece.y + pr == r && currentPiece.x + pc == c) {
                                isCurrent = true;
                                cellColor = currentPiece.type;
                            }
                        }
                    }
                }

                // Kiểm tra xem ô có thuộc Ghost piece không
                bool isGhost = false;
                if (!isCurrent) {
                    for (int pr = 0; pr < 4; pr++) {
                        for (int pc = 0; pc < 4; pc++) {
                            if (PIECES[currentPiece.type][currentPiece.rotation][pr][pc]) {
                                if (ghostY + pr == r && currentPiece.x + pc == c) {
                                    isGhost = true;
                                }
                            }
                        }
                    }
                }

                if (isCurrent) {
                    setColor(PIECE_COLORS[cellColor]);
                    cout << "[]";
                } else if (isGhost) {
                    setColor(COLOR_DARK_GRAY);
                    cout << "::";
                } else if (cellColor != -1) {
                    setColor(PIECE_COLORS[cellColor]);
                    cout << "[]";
                } else {
                    setColor(COLOR_DARK_GRAY);
                    cout << " .";
                }
            }

            // Lề phải
            setColor(COLOR_WHITE);
            cout << "!>";

            // Panel bên phải: Thông tin điểm, Level, Next Piece, Hold Piece
            int panelX = OFFSET_X + BOARD_WIDTH * 2 + 6;
            gotoxy(panelX, OFFSET_Y + r + 3);

            if (r == 0) {
                setColor(COLOR_GREEN);
                cout << "+-----------------------+";
            } else if (r == 1) {
                setColor(COLOR_GREEN); cout << "| ";
                setColor(COLOR_YELLOW); cout << "SCORE:      ";
                setColor(COLOR_WHITE); printf("%-9d", score);
                setColor(COLOR_GREEN); cout << " |";
            } else if (r == 2) {
                setColor(COLOR_GREEN); cout << "| ";
                setColor(COLOR_YELLOW); cout << "HIGH SCORE: ";
                setColor(COLOR_WHITE); printf("%-9d", highScore);
                setColor(COLOR_GREEN); cout << " |";
            } else if (r == 3) {
                setColor(COLOR_GREEN); cout << "| ";
                setColor(COLOR_CYAN); cout << "LEVEL:      ";
                setColor(COLOR_WHITE); printf("%-9d", level);
                setColor(COLOR_GREEN); cout << " |";
            } else if (r == 4) {
                setColor(COLOR_GREEN); cout << "| ";
                setColor(COLOR_CYAN); cout << "LINES:      ";
                setColor(COLOR_WHITE); printf("%-9d", linesCleared);
                setColor(COLOR_GREEN); cout << " |";
            } else if (r == 5) {
                setColor(COLOR_GREEN);
                cout << "+-----------------------+";
            } else if (r == 7) {
                setColor(COLOR_CYAN);
                cout << "  [ NEXT PIECE ]";
            } else if (r >= 8 && r <= 11) {
                int pr = r - 8;
                cout << "     ";
                for (int pc = 0; pc < 4; pc++) {
                    if (PIECES[nextPiece.type][0][pr][pc]) {
                        setColor(PIECE_COLORS[nextPiece.type]);
                        cout << "[]";
                    } else {
                        cout << "  ";
                    }
                }
            } else if (r == 13) {
                setColor(COLOR_MAGENTA);
                cout << "  [ HOLD PIECE (C/H) ]";
            } else if (r >= 14 && r <= 17) {
                int pr = r - 14;
                cout << "     ";
                if (hasHoldPiece) {
                    for (int pc = 0; pc < 4; pc++) {
                        if (PIECES[holdPiece.type][0][pr][pc]) {
                            setColor(PIECE_COLORS[holdPiece.type]);
                            cout << "[]";
                        } else {
                            cout << "  ";
                        }
                    }
                } else {
                    setColor(COLOR_DARK_GRAY);
                    cout << "   (None)   ";
                }
            }
        }

        // Đáy bàn cờ
        gotoxy(OFFSET_X, OFFSET_Y + BOARD_HEIGHT + 3);
        setColor(COLOR_WHITE);
        cout << "<!====================!>\n";
        gotoxy(OFFSET_X + 2, OFFSET_Y + BOARD_HEIGHT + 4);
        cout << "\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n\n";

        // Hướng dẫn phím bấm
        setColor(COLOR_GRAY);
        cout << " [A]/[D] hoac [<-]/[->]: Sang trai/phai  | [W] / [^]: Xoay khoi\n";
        cout << " [S]     hoac [v]     : Roi nhanh        | [SPACE]  : Tha roi ngay (Hard Drop)\n";
        cout << " [C] / [H]            : Hold Giu khoi    | [P]: Tam dung | [R]: Choi lai | [Q]: Thoat\n";

        // Trạng thái Pause / Game Over
        if (isPaused) {
            gotoxy(OFFSET_X + 4, OFFSET_Y + BOARD_HEIGHT / 2 + 2);
            setColor(COLOR_YELLOW, COLOR_DARK_RED);
            cout << " *** GAME TAM DUNG (PAUSED) - BAM [P] DE TIEP TUC *** ";
            setColor(COLOR_WHITE, COLOR_BLACK);
        } else if (isGameOver) {
            gotoxy(OFFSET_X + 6, OFFSET_Y + BOARD_HEIGHT / 2 + 1);
            setColor(COLOR_RED, COLOR_WHITE);
            cout << " ============================== ";
            gotoxy(OFFSET_X + 6, OFFSET_Y + BOARD_HEIGHT / 2 + 2);
            cout << "       GAME OVER! BAN THUA      ";
            gotoxy(OFFSET_X + 6, OFFSET_Y + BOARD_HEIGHT / 2 + 3);
            cout << "   BAM [R] CHOI LAI - [Q] THOAT ";
            gotoxy(OFFSET_X + 6, OFFSET_Y + BOARD_HEIGHT / 2 + 4);
            cout << " ============================== ";
            setColor(COLOR_WHITE, COLOR_BLACK);
        }
    }

    // Vòng lặp trò chơi chính
    void run() {
        hideCursor();
        int tickCounter = 0;

        while (true) {
            // Tốc độ rơi theo Level
            int dropInterval = max(1, 10 - level);

            // Xử lý Input bàn phím
            if (kbhit()) {
                int ch = getch();
                if (ch == 224) { // Phím mũi tên
                    ch = getch();
                    if (!isGameOver && !isPaused) {
                        if (ch == 75 && isValidPosition(currentPiece.x - 1, currentPiece.y, currentPiece.rotation, currentPiece.type)) {
                            currentPiece.x--;
                            playSoundEffect(1);
                        } else if (ch == 77 && isValidPosition(currentPiece.x + 1, currentPiece.y, currentPiece.rotation, currentPiece.type)) {
                            currentPiece.x++;
                            playSoundEffect(1);
                        } else if (ch == 72) { // Up arrow
                            rotatePiece();
                        } else if (ch == 80) { // Down arrow (soft drop)
                            if (isValidPosition(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.type)) {
                                currentPiece.y++;
                                score += 1;
                            }
                        }
                    }
                } else {
                    char c = tolower(ch);
                    if (c == 'q') {
                        saveHighScore();
                        break;
                    }
                    if (c == 'p' && !isGameOver) {
                        isPaused = !isPaused;
                    }
                    if (c == 'r' && isGameOver) {
                        initGame();
                    }

                    if (!isGameOver && !isPaused) {
                        if ((c == 'a') && isValidPosition(currentPiece.x - 1, currentPiece.y, currentPiece.rotation, currentPiece.type)) {
                            currentPiece.x--;
                            playSoundEffect(1);
                        } else if ((c == 'd') && isValidPosition(currentPiece.x + 1, currentPiece.y, currentPiece.rotation, currentPiece.type)) {
                            currentPiece.x++;
                            playSoundEffect(1);
                        } else if (c == 'w') {
                            rotatePiece();
                        } else if (c == 's') { // Soft drop
                            if (isValidPosition(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.type)) {
                                currentPiece.y++;
                                score += 1;
                            }
                        } else if (c == ' ') { // Hard drop
                            hardDrop();
                        } else if (c == 'c' || c == 'h') { // Hold
                            holdCurrentPiece();
                        }
                    }
                }
            }

            // Tự động rơi theo nhịp game
            if (!isGameOver && !isPaused) {
                tickCounter++;
                if (tickCounter >= dropInterval) {
                    tickCounter = 0;
                    if (isValidPosition(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.type)) {
                        currentPiece.y++;
                    } else {
                        lockPiece();
                    }
                }
            }

            render();
            Sleep(40); // 25 FPS mượt mà
        }
    }
};

int main() {
    // Đặt tiêu đề Console và chế độ hiển thị
    SetConsoleTitleA("UIT - SS004: Tetris Game - Nhom 01");
    
    TetrisGame game;
    game.run();

    gotoxy(0, OFFSET_Y + BOARD_HEIGHT + 7);
    setColor(COLOR_WHITE);
    cout << "Cam on ban da trai nghiem tro choi Tetris!\n";
    return 0;
}
