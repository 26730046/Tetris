#include <iostream>
#include <conio.h>
#include <windows.h>   // cho Sleep()/_sleep(), SetConsoleOutputCP
#include <cstdlib>     // cho rand(), srand(), system()
#include <ctime>       // cho time()

using namespace std;
#define H 20
#define W 15
char board[H][W] = {};

int x, y, b, next_b;
int dropSpeed = 500;
int score = 0;
int level = 1;
int totalLines = 0;

int bag[7];
int bag_index = 7; // force generation on first call

void shuffleBag() {
    for (int i = 0; i < 7; i++) bag[i] = i;
    for (int i = 6; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = bag[i];
        bag[i] = bag[j];
        bag[j] = temp;
    }
}

int getNextBlockType() {
    if (bag_index >= 7) {
        shuffleBag();
        bag_index = 0;
    }
    return bag[bag_index++];
}

// --- TASK 1: Base Class & Quản lý bộ nhớ ---
class Block {
public:
    char shape[4][4];
    
    virtual ~Block() {}
    
    // Hàm ảo để Người 3 cài đặt đa hình
    virtual void rotate() {
        char temp[4][4];
        for(int i=0; i<4; i++) for(int j=0; j<4; j++) temp[i][j] = shape[3-j][i];
        for(int i=0; i<4; i++) for(int j=0; j<4; j++) shape[i][j] = temp[i][j];
    }
    
    // Hàm ảo hỗ trợ khôi phục trạng thái cho Người 5
    virtual void undoRotate() {
        char temp[4][4];
        for(int i=0; i<4; i++) for(int j=0; j<4; j++) temp[i][j] = shape[j][3-i];
        for(int i=0; i<4; i++) for(int j=0; j<4; j++) shape[i][j] = temp[i][j];
    }
};

// Con trỏ đa hình thay thế cho mảng current và blocks
Block* currentBlock = nullptr;
Block* nextBlock = nullptr;
// ------------------------------------------

class IBlock : public Block {
    bool isVertical;
public:
    IBlock() {
        isVertical = false;
        char initialShape[4][4] = {
            {' ', ' ', ' ', ' '},
            {'I', 'I', 'I', 'I'},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
        for(int i=0; i<4; i++) for(int j=0; j<4; j++) shape[i][j] = initialShape[i][j];
    }
    void rotate() override {
        isVertical = !isVertical;
        for(int i=0; i<4; i++) for(int j=0; j<4; j++) shape[i][j] = ' ';
        if (isVertical) {
            shape[0][2] = 'I'; shape[1][2] = 'I'; shape[2][2] = 'I'; shape[3][2] = 'I';
        } else {
            shape[1][0] = 'I'; shape[1][1] = 'I'; shape[1][2] = 'I'; shape[1][3] = 'I';
        }
    }
    void undoRotate() override { rotate(); }
};

class JBlock : public Block {
public:
    JBlock() {
        char initialShape[4][4] = {
            {'J', ' ', ' ', ' '},
            {'J', 'J', 'J', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
        for(int i=0; i<4; i++) for(int j=0; j<4; j++) shape[i][j] = initialShape[i][j];
    }
};

class LBlock : public Block {
public:
    LBlock() {
        char initialShape[4][4] = {
            {' ', ' ', 'L', ' '},
            {'L', 'L', 'L', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
        for(int i=0; i<4; i++) for(int j=0; j<4; j++) shape[i][j] = initialShape[i][j];
    }
};

class OBlock : public Block {
public:
    OBlock() {
        char initialShape[4][4] = {
            {' ', 'O', 'O', ' '},
            {' ', 'O', 'O', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
        for(int i=0; i<4; i++) for(int j=0; j<4; j++) shape[i][j] = initialShape[i][j];
    }
    void rotate() override {}
    void undoRotate() override {}
};

class SBlock : public Block {
public:
    SBlock() {
        char initialShape[4][4] = {
            {' ', 'S', 'S', ' '},
            {'S', 'S', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
        for(int i=0; i<4; i++) for(int j=0; j<4; j++) shape[i][j] = initialShape[i][j];
    }
};

class TBlock : public Block {
public:
    TBlock() {
        char initialShape[4][4] = {
            {' ', 'T', ' ', ' '},
            {'T', 'T', 'T', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
        for(int i=0; i<4; i++) for(int j=0; j<4; j++) shape[i][j] = initialShape[i][j];
    }
};

class ZBlock : public Block {
public:
    ZBlock() {
        char initialShape[4][4] = {
            {'Z', 'Z', ' ', ' '},
            {' ', 'Z', 'Z', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
        for(int i=0; i<4; i++) for(int j=0; j<4; j++) shape[i][j] = initialShape[i][j];
    }
};
void loadCurrent(){
    switch (b) {
        case 0: currentBlock = new IBlock(); break;
        case 1: currentBlock = new JBlock(); break;
        case 2: currentBlock = new LBlock(); break;
        case 3: currentBlock = new OBlock(); break;
        case 4: currentBlock = new SBlock(); break;
        case 5: currentBlock = new TBlock(); break;
        case 6: currentBlock = new ZBlock(); break;
    }
}

void loadNext(){
    if (nextBlock != nullptr) delete nextBlock;
    switch (next_b) {
        case 0: nextBlock = new IBlock(); break;
        case 1: nextBlock = new JBlock(); break;
        case 2: nextBlock = new LBlock(); break;
        case 3: nextBlock = new OBlock(); break;
        case 4: nextBlock = new SBlock(); break;
        case 5: nextBlock = new TBlock(); break;
        case 6: nextBlock = new ZBlock(); break;
    }
}

bool canPlace(Block* block, int nx, int ny){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (block->shape[i][j] != ' ') {
                int xt = nx + j;
                int yt = ny + i;
                if (xt < 1 || xt >= W-1 || yt >= H-1 ) return false;
                if (board[yt][xt] != ' ') return false;
            }
    return true;
}

bool canMove(int dx, int dy){
    return canPlace(currentBlock, x + dx, y + dy);
}

void block2Board(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (currentBlock->shape[i][j] != ' ')
                board[y+i][x+j] = currentBlock->shape[i][j];
}

void boardDelBlock(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (currentBlock->shape[i][j] != ' ')
                board[y+i][x+j] = ' ';
}

void boardDelGhost(){
    for (int i = 1; i < H-1; i++ )
        for (int j = 1; j < W-1; j++ )
            if (board[i][j] == '.')
                board[i][j] = ' ';
}

void rotate(){
    int old_x = x;
    
    currentBlock->rotate();

    const int kicks[] = {0, -1, 1, -2, 2};
    bool placed = false;
    for (int k = 0; k < 5; k++){
        int nx = old_x + kicks[k];
        if (canPlace(currentBlock, nx, y)){
            x = nx;
            placed = true;
            break;
        }
    }
    
    if (!placed) {
        x = old_x;
        currentBlock->undoRotate();
    }
}

void initBoard(){
    for (int i = 0 ; i < H ; i++)
        for (int j = 0 ; j < W ; j++)
            if (i == 0 || i == H-1 || j == 0 || j == W-1) board[i][j] = '#';
            else board[i][j] = ' ';
}
void drawCell(char c){
    if (c == ' ') cout << "  ";
    else if (c == '#') cout << "██"; 
    else if (c == '.') cout << "░░";
    else cout << "[]";
}
void draw(){
    cout << "\x1B[H"; 

    cout << "  Điểm số: " << score << "   Cấp độ: " << level << "        \n";

    for (int i = 0 ; i < H ; i++) {
        for (int j = 0 ; j < W ; j++) drawCell(board[i][j]);
        
        if (i == 2) cout << "    Next Block:";
        else if (i >= 4 && i < 8 && nextBlock != nullptr) {
            cout << "    ";
            for (int j = 0; j < 4; j++) {
                drawCell(nextBlock->shape[i-4][j]);
            }
        }
        cout << endl;
    }
}

void removeLine(){
    int linesCleared = 0;
    for (int i = H-2; i > 0; i--){
        bool full = true;
        for (int j = 1; j < W-1; j++){
            if (board[i][j] == ' '){
                full = false;
                break;
            }
        }
        if (full){
            linesCleared++;
            for (int ii = i; ii > 1; ii--)
                for (int jj = 1; jj < W-1; jj++)
                    board[ii][jj] = board[ii-1][jj];
            for (int jj = 1; jj < W-1; jj++)
                board[1][jj] = ' ';

            draw();
            Sleep(100);

            i++; // kiểm tra lại dòng i vì vừa dịch xuống
        }
    }
    
    if (linesCleared > 0) {
        if (linesCleared == 1) score += 100;
        else if (linesCleared == 2) score += 300;
        else if (linesCleared == 3) score += 500;
        else if (linesCleared == 4) score += 800;
        else score += 1000; // in case of more than 4, though impossible in standard tetris
        
        totalLines += linesCleared;
        int newLevel = 1 + (totalLines / 10);
        if (newLevel > level) {
            level = newLevel;
            dropSpeed = 500 - (level - 1) * 50;
            if (dropSpeed < 50) dropSpeed = 50;
        }
    }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= 0x0004; // Bật ENABLE_VIRTUAL_TERMINAL_PROCESSING
    SetConsoleMode(hOut, dwMode);
    
    // Ẩn con trỏ chuột nhấp nháy trên Console
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    srand(time(0));
    x = 5; y = 1; b = getNextBlockType();
    loadCurrent();
    next_b = getNextBlockType();
    loadNext();
    initBoard();

    int timer = 0;
    system("cls"); // Clear screen once at the beginning
    while (1){
        boardDelBlock();
        boardDelGhost();
        
        // Handle input smoothly
        while (kbhit()){
            char c = getch();
            if (c == 'a' && canMove(-1,0)) x--;
            else if (c == 'd' && canMove( 1,0)) x++;
            else if (c == 'x' && canMove( 0,1)) y++;
            else if (c == 'w') rotate(); // Xử lý phím w gọi thử xoay (Wall Kicks)
            else if (c == ' ') {
                while (canMove(0, 1)) y++;
                timer = dropSpeed;
            }
            else if (c == 'p' || c == 'P' || c == 27) {
                system("cls");
                cout << "\n\n\n\n\n\n\t\t   ==== PAUSED ====\n";
                cout << "\t\tNhan phim bat ky de tiep tuc...";
                while(!kbhit()) Sleep(100);
                getch(); // clear the pressed key
                system("cls");
            }
            else if (c == 'q') return 0;
        }
        
        timer += 30; // 30ms per frame
        if (timer >= dropSpeed) {
            if (canMove(0,1)) {
                y++;
            } else {
                block2Board();
                removeLine();
                x = 5; y = 1; 
                b = next_b;
                
                // Giải phóng bộ nhớ khối cũ trước khi cấp phát khối mới (Người 1)
                if (currentBlock != nullptr) {
                    delete currentBlock;
                    currentBlock = nullptr;
                }
                
                loadCurrent();
                next_b = getNextBlockType();
                loadNext();
                if (!canPlace(currentBlock, x, y)) {
                    system("cls");
                    cout << "\n\n\tGAME OVER!\n\tDiem so: " << score << "\n\n";
                    break;
                }
            }
            timer = 0;
        }

        int gy = y;
        while (canPlace(currentBlock, x, gy + 1)) gy++;
        for (int i = 0; i < 4; i++ )
            for (int j = 0; j < 4; j++ )
                if (currentBlock->shape[i][j] != ' ' && board[gy+i][x+j] == ' ')
                    board[gy+i][x+j] = '.';

        block2Board();
        draw();
        Sleep(30);
    }
    
    if (currentBlock != nullptr) {
        delete currentBlock;
    }
    if (nextBlock != nullptr) {
        delete nextBlock;
    }
    return 0;
}