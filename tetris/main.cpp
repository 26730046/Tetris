#include <iostream>
#include <conio.h>
#include <windows.h>   // cho Sleep()/_sleep(), SetConsoleOutputCP
#include <cstdlib>     // cho rand(), srand(), system()
#include <ctime>       // cho time()

using namespace std;
#define H 20
#define W 15
char board[H][W] = {};

int x, y, b;
int dropSpeed = 500;
int score = 0;
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
    else cout << "[]";
}
void draw(){
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    cout << "  Điểm số: " << score << "        \n";

    for (int i = 0 ; i < H ; i++, cout<<endl)
        for (int j = 0 ; j < W ; j++) drawCell(board[i][j]);
}

void removeLine(){
    for (int i = H-2; i > 0; i--){
        bool full = true;
        for (int j = 1; j < W-1; j++){
            if (board[i][j] == ' '){
                full = false;
                break;
            }
        }
        if (full){
            score += 100;
            for (int ii = i; ii > 1; ii--)
                for (int jj = 1; jj < W-1; jj++)
                    board[ii][jj] = board[ii-1][jj];
            for (int jj = 1; jj < W-1; jj++)
                board[1][jj] = ' ';

            draw();
            Sleep(200);

            if (dropSpeed > 100) dropSpeed -= 50;

            i++; // kiểm tra lại dòng i vì vừa dịch xuống
        }
    }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    
    // Ẩn con trỏ chuột nhấp nháy trên Console
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    srand(time(0));
    x = 5; y = 0; b = rand() % 7;
    loadCurrent();
    initBoard();

    int timer = 0;
    system("cls"); // Clear screen once at the beginning
    while (1){
        boardDelBlock();
        
        // Handle input smoothly
        while (kbhit()){
            char c = getch();
            if (c == 'a' && canMove(-1,0)) x--;
            else if (c == 'd' && canMove( 1,0)) x++;
            else if (c == 'x' && canMove( 0,1)) y++;
            else if (c == 'w') rotate(); // Xử lý phím w gọi thử xoay (Wall Kicks)
            else if (c == 'q') return 0;
        }
        
        timer += 30; // 30ms per frame
        if (timer >= dropSpeed) {
            if (canMove(0,1)) {
                y++;
            } else {
                block2Board();
                removeLine();
                x = 5; y = 0; b = rand() % 7;
                
                // Giải phóng bộ nhớ khối cũ trước khi cấp phát khối mới (Người 1)
                if (currentBlock != nullptr) {
                    delete currentBlock;
                    currentBlock = nullptr;
                }
                
                loadCurrent();
                if (!canPlace(currentBlock, x, y)) {
                    system("cls");
                    cout << "\n\n\tGAME OVER!\n\tDiem so: " << score << "\n\n";
                    break;
                }
            }
            timer = 0;
        }

        block2Board();
        draw();
        Sleep(30);
    }
    
    if (currentBlock != nullptr) {
        delete currentBlock;
    }
    return 0;
}