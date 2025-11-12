#include "damas.h"
#include "clear_window.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cctype>
#include <cmath>
#include <string>
#include <vector>

const int SIZE = 10;
char board[SIZE][SIZE];

int letterToColumn(char letter) {
    letter = std::toupper(static_cast<unsigned char>(letter));
    if (letter >= 'A' && letter <= 'J') return letter - 'A';
    return -1;
}

bool isKing(char p) {
    return std::isupper(static_cast<unsigned char>(p));
}

bool isOpponent(char p, char player) {
    if (player == 'y') return p == 'a' || p == 'A';
    else return p == 'y' || p == 'Y';
}

void printBoard() {
    clearScreen();
    std::cout << "    ";
    for (int i = 0; i < SIZE; ++i)
        std::cout << " " << static_cast<char>('A' + i) << " ";
    std::cout << "\n";

    for (int i = 0; i < SIZE; ++i) {
        std::cout << " " << i << " ";
        for (int j = 0; j < SIZE; ++j)
            std::cout << '[' << board[i][j] << ']';
        std::cout << "\n";
    }
}

void initBoard() {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = ((i + j) % 2 == 1) ? '.' : ' ';

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < SIZE; ++j)
            if ((i + j) % 2 == 1) board[i][j] = 'a';

    for (int i = 6; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if ((i + j) % 2 == 1) board[i][j] = 'y';
}

bool canCaptureFrom(int r, int c, char player) {
    char piece = board[r][c];
    if (piece == '.' || piece == ' ') return false;

    int dirs[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

    for (auto& d : dirs) {
        int dr = d[0], dc = d[1];
        int nr = r + dr, nc = c + dc;
        int jumpR = r + 2 * dr, jumpC = c + 2 * dc;

        if (isKing(piece)) {
            nr = r + dr; nc = c + dc;
            bool foundEnemy = false;
            while (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE) {
                if (board[nr][nc] == '.' || board[nr][nc] == ' ') {
                    nr += dr; nc += dc;
                    continue;
                }
                if (isOpponent(board[nr][nc], player) && !foundEnemy) {
                    foundEnemy = true;
                    int afterR = nr + dr, afterC = nc + dc;
                    while (afterR >= 0 && afterR < SIZE && afterC >= 0 && afterC < SIZE) {
                        if (board[afterR][afterC] == '.') return true;
                        if (board[afterR][afterC] != '.') break;
                        afterR += dr; afterC += dc;
                    }
                    break;
                } else break;
            }
        } else {
            if (jumpR >= 0 && jumpR < SIZE && jumpC >= 0 && jumpC < SIZE)
                if (isOpponent(board[nr][nc], player) && board[jumpR][jumpC] == '.')
                    return true;
        }
    }
    return false;
}
