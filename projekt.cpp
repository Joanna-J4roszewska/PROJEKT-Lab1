#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 25;
const int height = 25;
int x, y;
int fruitX, fruitY;
int score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;

    nTail = 2;
    tailX[0] = x - 1;
    tailY[0] = y;
    tailX[1] = x - 2;
    tailY[1] = y;

}

void Draw() {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
    for (int i = 0; i < width + 27; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "|";
            if (i == y && j == x)
                cout << "@";
            else if (i == fruitY && j == fruitX)
                cout << "O";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {

                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "#";
                        print = true;
                    }

                }
                if (!print)
                    cout << " ";

            }
            cout << " ";
            if (j == width - 1)
                cout << "|";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 27; i++)
        cout << "-";
    cout << endl;

    
    
}

void Input() {
    if (_kbhit()) {
        int key = _getch();


        if (key == 224) { 
            key = _getch(); 
            switch (key) {
            case 72: 
                dir = UP;
                break;
            case 80: 
                dir = DOWN;
                break;
            case 75: 
                dir = LEFT;
                break;
            case 77:
                dir = RIGHT;
                break;
            }
        }
        else if (key == 'x') {
            gameOver = true;
           
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X;
    int prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

   
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;
  
    for (int i = 2; i < nTail; i++)//i=2 zeby te segmenty z ktorymi pojawia sie glowa nie tworzyly kolizji
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    
  
    if (x == fruitX && y == fruitY) {
        score += 1;
        nTail++; 
        
        bool validPosition = false;
        while (!validPosition) {
            validPosition = true;
            fruitX = rand() % width;
            fruitY = rand() % height;

           
            for (int i = 0; i < nTail; i++) {
                if (tailX[i] == fruitX && tailY[i] == fruitY) {
                    validPosition = false; 
                    break;
                }
            }
        }
    }
}


int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }

    cout << "Game Over!" << endl;
    cout << "Your Score: " << score << endl;


    return 0;
}