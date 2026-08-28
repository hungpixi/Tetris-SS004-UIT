/**
 * ============================================================================
 * TRƯỜNG ĐẠI HỌC CÔNG NGHỆ THÔNG TIN - ĐHQG TP.HCM
 * KHOA KỸ THUẬT MÁY TÍNH & KHOA HỌC MÁY TÍNH
 * MÔN HỌC: KỸ NĂNG NGHỀ NGHIỆP (SS004)
 * ----------------------------------------------------------------------------
 * ĐỒ ÁN CUỐI KỲ: TRÒ CHƠI TETRIS HOÀN CHỈNH (CONSOLE C++ PRO)
 * NHÓM THỰC HIỆN: NHÓM 01
 * 1. Huỳnh Nguyễn Hoài Thương - 26730069 (Trưởng nhóm)
 * 2. Nguyễn Ngọc Duy          - 26730013 (Thành viên)
 * 3. Phạm Phú Nguyễn Hưng     - 26730023 (Thành viên - Quản trị Git)
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

const int BOARD_HEIGHT = 20;
const int BOARD_WIDTH  = 10;
const int OFFSET_X     = 3;
const int OFFSET_Y     = 2;

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

const int PIECES[7][4][4][4] = {
    // 0: I
    {
        {{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
        {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}},
        {{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}},
        {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}}
    },
    // 1: O
    {
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}}
    },
    // 2: T
    {
        {{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}},
        {{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}
    },
    // 3: S
    {
        {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
        {{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},
        {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}
    },
    // 4: Z
    {
        {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},
        {{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}}
    },
    // 5: J
    {
        {{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}}
    },
    // 6: L
    {
        {{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}},
        {{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}}
    }
};

const ConsoleColor PIECE_COLORS[7] = {
    COLOR_CYAN,
    COLOR_YELLOW,
    COLOR_MAGENTA,
    COLOR_GREEN,
    COLOR_RED,
    COLOR_BLUE,
    COLOR_DARK_YELLOW
};

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int textColor, int bgColor = 0) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

void setupConsole() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 780, 680, TRUE);

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
    system("cls");
}

void playSoundEffect(int type) {
    switch (type) {
        case 1: Beep(900, 25); break;
        case 2: Beep(450, 30); break;
        case 3: Beep(1100, 80); break;
        case 4: Beep(1000, 60); Beep(1400, 80); Beep(1800, 100); break;
        case 5: Beep(500, 150); Beep(300, 250); break;
    }
}

class Piece {
public:
    int type;
    int rotation;
    int x, y;

    Piece() { reset(rand() % 7); }

    void reset(int t) {
        type = t;
        rotation = 0;
        x = BOARD_WIDTH / 2 - 2;
        y = 0;
    }

    void rotate() { rotation = (rotation + 1) % 4; }
    void unrotate() { rotation = (rotation + 3) % 4; }
};

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
                board[r][c] = -1;
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

    bool isValidPosition(int px, int py, int prot, int ptype) {
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                if (PIECES[ptype][prot][r][c]) {
                    int bx = px + c;
                    int by = py + r;
                    if (bx < 0 || bx >= BOARD_WIDTH || by >= BOARD_HEIGHT) return false;
                    if (by >= 0 && board[by][bx] != -1) return false;
                }
            }
        }
        return true;
    }

    void rotatePiece() {
        int oldRot = currentPiece.rotation;
        currentPiece.rotate();
        if (!isValidPosition(currentPiece.x, currentPiece.y, currentPiece.rotation, currentPiece.type)) {
            if (isValidPosition(currentPiece.x - 1, currentPiece.y, currentPiece.rotation, currentPiece.type))
                currentPiece.x -= 1;
            else if (isValidPosition(currentPiece.x + 1, currentPiece.y, currentPiece.rotation, currentPiece.type))
                currentPiece.x += 1;
            else {
                currentPiece.rotation = oldRot;
                return;
            }
        }
        playSoundEffect(1);
    }

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

        currentPiece.reset(nextPiece.type);
        nextPiece.reset(rand() % 7);
        canHold = true;

        if (!isValidPosition(currentPiece.x, currentPiece.y, currentPiece.rotation, currentPiece.type)) {
            isGameOver = true;
            saveHighScore();
            playSoundEffect(5);
        }
    }

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
                r++;
            }
        }

        if (clearedCount > 0) {
            linesCleared += clearedCount;
            int points = 0;
            switch (clearedCount) {
                case 1: points = 100 * level; playSoundEffect(3); break;
                case 2: points = 300 * level; playSoundEffect(3); break;
                case 3: points = 500 * level; playSoundEffect(3); break;
                case 4: points = 800 * level; playSoundEffect(4); break;
            }
            score += points;
            level = 1 + linesCleared / 10;
            if (score > highScore) highScore = score;
        }
    }

    int getGhostY() {
        int gy = currentPiece.y;
        while (isValidPosition(currentPiece.x, gy + 1, currentPiece.rotation, currentPiece.type)) {
            gy++;
        }
        return gy;
    }

    void hardDrop() {
        int dropDistance = 0;
        while (isValidPosition(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.type)) {
            currentPiece.y++;
            dropDistance++;
        }
        score += dropDistance * 2;
        lockPiece();
    }

    // Render hoàn toàn không bị trôi dòng
    void render() {
        gotoxy(0, 0);

        setColor(COLOR_CYAN);
        cout << "================================================================\n";
        cout << "   [UIT - SS004] TRO CHOI TETRIS - NHOM 01 (C++ CONSOLE PRO)    \n";
        cout << "================================================================\n";

        int ghostY = getGhostY();

        for (int r = 0; r < BOARD_HEIGHT; r++) {
            gotoxy(OFFSET_X, OFFSET_Y + r + 2);
            setColor(COLOR_WHITE);
            cout << "<!";

            for (int c = 0; c < BOARD_WIDTH; c++) {
                int cellColor = board[r][c];
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

            setColor(COLOR_WHITE);
            cout << "!>   ";

            // Panel thông tin bên phải được format cố định
            int panelX = OFFSET_X + BOARD_WIDTH * 2 + 7;
            gotoxy(panelX, OFFSET_Y + r + 2);

            if (r == 0) {
                setColor(COLOR_GREEN); cout << "+-----------------------+";
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
                setColor(COLOR_GREEN); cout << "+-----------------------+";
            } else if (r == 7) {
                setColor(COLOR_CYAN); cout << " [ NEXT PIECE ]          ";
            } else if (r >= 8 && r <= 11) {
                int pr = r - 8;
                cout << "   ";
                for (int pc = 0; pc < 4; pc++) {
                    if (PIECES[nextPiece.type][0][pr][pc]) {
                        setColor(PIECE_COLORS[nextPiece.type]); cout << "[]";
                    } else {
                        cout << "  ";
                    }
                }
                cout << "         ";
            } else if (r == 13) {
                setColor(COLOR_MAGENTA); cout << " [ HOLD PIECE (C/H) ]    ";
            } else if (r >= 14 && r <= 17) {
                int pr = r - 14;
                cout << "   ";
                if (hasHoldPiece) {
                    for (int pc = 0; pc < 4; pc++) {
                        if (PIECES[holdPiece.type][0][pr][pc]) {
                            setColor(PIECE_COLORS[holdPiece.type]); cout << "[]";
                        } else {
                            cout << "  ";
                        }
                    }
                } else {
                    setColor(COLOR_DARK_GRAY); cout << "(Chua giu)  ";
                }
                cout << "         ";
            } else {
                cout << "                         ";
            }
        }

        gotoxy(OFFSET_X, OFFSET_Y + BOARD_HEIGHT + 2);
        setColor(COLOR_WHITE);
        cout << "<!====================!>                         \n";
        gotoxy(OFFSET_X, OFFSET_Y + BOARD_HEIGHT + 3);
        cout << "  \\/\\/\\/\\/\\/\\/\\/\\/\\/\\/                           \n\n";

        setColor(COLOR_GRAY);
        cout << " Dieu khien: [A]/[D] hoac [<-]/[->]: Sang trai/phai | [W]/[^]: Xoay (SRS) \n";
        cout << "             [S] hoac [v]: Roi nhanh | [SPACE]: Tha roi ngay (Hard Drop) \n";
        cout << "             [C]/[H]: Hold khoi | [P]: Tam dung | [R]: Choi lai | [Q]: Thoat\n";

        if (isPaused) {
            gotoxy(OFFSET_X + 2, OFFSET_Y + BOARD_HEIGHT / 2 + 1);
            setColor(COLOR_YELLOW, COLOR_DARK_RED);
            cout << " *** GAME TAM DUNG (PAUSED) - BAM [P] DE TIEP TUC *** ";
            setColor(COLOR_WHITE, COLOR_BLACK);
        } else if (isGameOver) {
            gotoxy(OFFSET_X + 3, OFFSET_Y + BOARD_HEIGHT / 2);
            setColor(COLOR_RED, COLOR_WHITE); cout << " ============================== ";
            gotoxy(OFFSET_X + 3, OFFSET_Y + BOARD_HEIGHT / 2 + 1);
            cout << "       GAME OVER! BAN THUA      ";
            gotoxy(OFFSET_X + 3, OFFSET_Y + BOARD_HEIGHT / 2 + 2);
            cout << "   BAM [R] CHOI LAI - [Q] THOAT ";
            gotoxy(OFFSET_X + 3, OFFSET_Y + BOARD_HEIGHT / 2 + 3);
            cout << " ============================== ";
            setColor(COLOR_WHITE, COLOR_BLACK);
        }
    }

    void run() {
        setupConsole();
        int tickCounter = 0;

        while (true) {
            int dropInterval = max(1, 10 - level);

            if (kbhit()) {
                int ch = getch();
                if (ch == 224) {
                    ch = getch();
                    if (!isGameOver && !isPaused) {
                        if (ch == 75 && isValidPosition(currentPiece.x - 1, currentPiece.y, currentPiece.rotation, currentPiece.type)) {
                            currentPiece.x--; playSoundEffect(1);
                        } else if (ch == 77 && isValidPosition(currentPiece.x + 1, currentPiece.y, currentPiece.rotation, currentPiece.type)) {
                            currentPiece.x++; playSoundEffect(1);
                        } else if (ch == 72) {
                            rotatePiece();
                        } else if (ch == 80) {
                            if (isValidPosition(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.type)) {
                                currentPiece.y++; score += 1;
                            }
                        }
                    }
                } else {
                    char c = tolower(ch);
                    if (c == 'q') { saveHighScore(); break; }
                    if (c == 'p' && !isGameOver) isPaused = !isPaused;
                    if (c == 'r' && isGameOver) { initGame(); system("cls"); }

                    if (!isGameOver && !isPaused) {
                        if ((c == 'a') && isValidPosition(currentPiece.x - 1, currentPiece.y, currentPiece.rotation, currentPiece.type)) {
                            currentPiece.x--; playSoundEffect(1);
                        } else if ((c == 'd') && isValidPosition(currentPiece.x + 1, currentPiece.y, currentPiece.rotation, currentPiece.type)) {
                            currentPiece.x++; playSoundEffect(1);
                        } else if (c == 'w') {
                            rotatePiece();
                        } else if (c == 's') {
                            if (isValidPosition(currentPiece.x, currentPiece.y + 1, currentPiece.rotation, currentPiece.type)) {
                                currentPiece.y++; score += 1;
                            }
                        } else if (c == ' ') {
                            hardDrop();
                        } else if (c == 'c' || c == 'h') {
                            holdCurrentPiece();
                        }
                    }
                }
            }

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
            Sleep(40);
        }
    }
};

int main() {
    SetConsoleTitleA("UIT - SS004: Tetris Game Pro - Nhom 01");
    TetrisGame game;
    game.run();
    return 0;
}
