#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

int width = 40;  
int height = 20; 
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100], nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN } dir;

// cursor return back (No Flickering!)
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// to hide blinking cursor
void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void Setup() {
    hideCursor(); 
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    gotoxy(0, 0); //use gotoxy
    
    for (int i = 0; i < width + 2; i++) printf("#");
    printf("\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) printf("#");
            
            if (i == y && j == x) printf("O"); // Snake Head
            else if (i == fruitY && j == fruitX) printf("F"); // Fruit
            else {
                int print = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o"); 
                        print = 1; // Snake Tail
                    }
                }
                if (!print) printf(" ");
            }
            
            if (j == width - 1) printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < width + 2; i++) printf("#");
    printf("\nScore: %d \n", score);
    printf("Use W, A, S, D to move!"); // Instructions
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': dir = LEFT; break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = UP; break;
            case 's': dir = DOWN; break;
            case 'x': exit(0); // Exit game
        }
    }
}

void Logic() {
    int prevX = tailX[0]; 
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x; 
    tailY[0] = y;
    
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i]; prev2Y = tailY[i];
        tailX[i] = prevX; tailY[i] = prevY;
        prevX = prev2X; prevY = prev2Y;
    }
    
    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
    }
    
    // Wall collision (come from other side)
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;
    
    // logic of eat Fruit 
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main() {
    Setup();
    while (1) {
        Draw();
        Input();
        Logic();
        Sleep(60); // Speed control (less number high speed)
    }
    return 0;
}
