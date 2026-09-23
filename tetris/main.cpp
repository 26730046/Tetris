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
char current[4][4];

char blocks[][4][4] = {
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'I','I','I','I'},
         {' ',' ',' ',' '},
         {' ',' ',' ',' '}},
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

void loadCurrent(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            current[i][j] = blocks[b][i][j];
}

bool canPlace(char shape[4][4], int nx, int ny){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (shape[i][j] != ' ') {
                int xt = nx + j;
                int yt = ny + i;
                if (xt < 1 || xt >= W-1 || yt >= H-1 ) return false;
                if (board[yt][xt] != ' ') return false;
            }
    return true;
}

bool canMove(int dx, int dy){
    return canPlace(current, x + dx, y + dy);
}

void block2Board(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (current[i][j] != ' ')
                board[y+i][x+j] = current[i][j];
}

void boardDelBlock(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (current[i][j] != ' ')
                board[y+i][x+j] = ' ';
}

void rotateMatrix(char src[4][4], char dst[4][4]){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            dst[i][j] = src[3-j][i];
}

void rotate(){
    char rotated[4][4];
    rotateMatrix(current, rotated);

    const int kicks[] = {0, -1, 1, -2, 2};
    for (int k = 0; k < 5; k++){
        int nx = x + kicks[k];
        if (canPlace(rotated, nx, y)){
            x = nx;
            for (int i = 0; i < 4; i++ )
                for (int j = 0; j < 4; j++ )
                    current[i][j] = rotated[i][j];
            return;
        }
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
    system("cls");

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
            for (int ii = i; ii > 1; ii--)
                for (int jj = 1; jj < W-1; jj++)
                    board[ii][jj] = board[ii-1][jj];
            for (int jj = 1; jj < W-1; jj++)
                board[1][jj] = ' ';

            draw();
            _sleep(200);

            if (dropSpeed > 100) dropSpeed -= 50;

            i++; // kiểm tra lại dòng i vì vừa dịch xuống
        }
    }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    srand(time(0));
    x = 5; y = 0; b = rand() % 7;
    loadCurrent();
    initBoard();

    while (1){
        boardDelBlock();
        if (kbhit()){
            char c = getch();
            if (c == 'a' && canMove(-1,0)) x--;
            if (c == 'd' && canMove( 1,0)) x++;
            if (c == 'x' && canMove( 0,1)) y++;
            if (c == 'w') rotate();
            if (c == 'q') break;
        }
        if (canMove(0,1)) y++;
        else{
            block2Board();
            removeLine();
            x = 5; y = 0; b = rand() % 7;
            loadCurrent();
        }
        block2Board();
        draw();
        _sleep(dropSpeed);   // SỬA: dùng dropSpeed thay vì số cố định 500, để tốc độ tăng dần có tác dụng
    }
    return 0;
}