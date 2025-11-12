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

// ---------- UTILIDADES ----------
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

// ---------- IMPRESIÓN DEL TABLERO ----------
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
