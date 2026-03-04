#include <stdio.h>

char board[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
char player = 'X';

// Display Board
void drawBoard() {
    printf("\n\n   Tic Tac Toe\n\n");
    printf(" Player 1 (X)  -  Player 2 (O)\n\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", board[0][0], board[0][1], board[0][2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", board[1][0], board[1][1], board[1][2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", board[2][0], board[2][1], board[2][2]);
    printf("     |     |     \n\n");
}

// Winning Conditions
int checkWin() {
    // Rows aur Columns check karne ke liye
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return 1;
    }
    // Diagonals check 
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return 1;

    // Check if board full (Draw)
    int count = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O') count++;
    
    if (count == 0) return -1; 
    return 0;
}

int main() {
    int choice, status;
    
    do {
        drawBoard();
        printf("Player %c, enter position (1-9): ", player);
        scanf("%d", &choice);

        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;

        if (choice < 1 || choice > 9 || board[row][col] == 'X' || board[row][col] == 'O') {
            printf("Invalid move! Try again.\n");
            continue;
        }

        board[row][col] = player;
        status = checkWin();

        if (status == 0) {
            player = (player == 'X') ? 'O' : 'X';
        }
    } while (status == 0);

    drawBoard();
    if (status == 1)
        printf("==>\a Player %c wins! \n", player);
    else
        printf("==>\a Game Draw! \n");

    return 0;
}
