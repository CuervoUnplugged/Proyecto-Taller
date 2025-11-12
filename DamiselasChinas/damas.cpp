#include "damas.h"
#include "clear_window.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cctype>
#include <cmath>

const int SIZE = 10;
char board[SIZE][SIZE];
bool highlight[SIZE][SIZE];

bool isKing(char p) { return std::isupper(static_cast<unsigned char>(p)); }

bool isOpponent(char p, char player) {
    if (player == 'y') return p == 'a' || p == 'A';
    else return p == 'y' || p == 'Y';
}

void printBoard(int cursorRow = -1, int cursorCol = -1) {
    clearScreen();
    std::cout << "    ";
    for (int i = 0; i < SIZE; ++i)
        std::cout << " " << static_cast<char>('A' + i) << " ";
    std::cout << "\n";
    for (int i = 0; i < SIZE; ++i) {
        std::cout << " " << i << " ";
        for (int j = 0; j < SIZE; ++j) {
            char display = board[i][j];
            if (highlight[i][j] && (display == 'y' || display == 'a' || display == 'Y' || display == 'A'))
                display = '*';
            if (i == cursorRow && j == cursorCol)
                std::cout << '[' << '#' << ']';
            else
                std::cout << '[' << display << ']';
        }
        std::cout << "\n";
    }
}

void initBoard() {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = ((i + j) % 2 == 1) ? '.' : ' ';
            highlight[i][j] = false;
        }

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < SIZE; ++j)
            if ((i + j) % 2 == 1) board[i][j] = 'a';

    for (int i = 6; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if ((i + j) % 2 == 1) board[i][j] = 'y';
}

bool isGameOver(char& winner) {
    int y = 0, a = 0;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 'y' || board[i][j] == 'Y') y++;
            if (board[i][j] == 'a' || board[i][j] == 'A') a++;
        }
    if (y == 0) { winner = 'a'; return true; }
    if (a == 0) { winner = 'y'; return true; }
    return false;
}

bool canCaptureFrom(int r, int c, char player) {
    char piece = board[r][c];
    if (piece == '.' || piece == ' ') return false;

    int dirs[4][2];
    int dirCount = 0;

    if (isKing(piece)) {
        int tmp[4][2] = { {1,1}, {1,-1}, {-1,1}, {-1,-1} };
        for (int i = 0; i < 4; ++i) {
            dirs[i][0] = tmp[i][0];
            dirs[i][1] = tmp[i][1];
        }
        dirCount = 4;
    } 
    else if (player == 'y') {
        int tmp[2][2] = { {-1,1}, {-1,-1} };
        for (int i = 0; i < 2; ++i) {
            dirs[i][0] = tmp[i][0];
            dirs[i][1] = tmp[i][1];
        }
        dirCount = 2;
    } 
    else {
        int tmp[2][2] = { {1,1}, {1,-1} };
        for (int i = 0; i < 2; ++i) {
            dirs[i][0] = tmp[i][0];
            dirs[i][1] = tmp[i][1];
        }
        dirCount = 2;
    }

    for (int i = 0; i < dirCount; ++i) {
        int dr = dirs[i][0], dc = dirs[i][1];
        int midR = r + dr, midC = c + dc;
        int landR = r + 2 * dr, landC = c + 2 * dc;

        if (midR < 0 || midR >= SIZE || midC < 0 || midC >= SIZE) continue;
        if (landR < 0 || landR >= SIZE || landC < 0 || landC >= SIZE) continue;

        if (isOpponent(board[midR][midC], player) && board[landR][landC] == '.')
            return true;
    }
    return false;
}

bool playerHasCapture(char player) {
    bool hasCapture = false;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j) {
            highlight[i][j] = false;
            if ((player == 'y' && (board[i][j] == 'y' || board[i][j] == 'Y')) ||
                (player == 'a' && (board[i][j] == 'a' || board[i][j] == 'A'))) {
                if (canCaptureFrom(i, j, player)) {
                    highlight[i][j] = true;
                    hasCapture = true;
                }
            }
        }
    return hasCapture;
}

bool makeMove(int fromRow, int fromCol, int toRow, int toCol, char player, bool& captured) {
    char piece = board[fromRow][fromCol];
    if (piece == '.' || piece == ' ') return false;
    if (board[toRow][toCol] != '.') return false;

    int dr = toRow - fromRow;
    int dc = toCol - fromCol;
    if (std::abs(dr) != std::abs(dc)) return false;

    captured = false;

    if (std::abs(dr) == 2 && std::abs(dc) == 2) {
        int midR = (fromRow + toRow) / 2;
        int midC = (fromCol + toCol) / 2;
        if (!isKing(piece)) {
            int dir = (player == 'y') ? -1 : 1;
            if (dr != 2 * dir) return false;
        }
        if (isOpponent(board[midR][midC], player)) {
            board[midR][midC] = '.';
            captured = true;
        } else return false;
    } 
    else {
        if (playerHasCapture(player)) return false;
        if (!isKing(piece)) {
            int dir = (player == 'y') ? -1 : 1;
            if (dr != dir || std::abs(dc) != 1) return false;
        } else {
            if (std::abs(dr) != 1 || std::abs(dc) != 1) return false;
        }
    }

    board[toRow][toCol] = piece;
    board[fromRow][fromCol] = '.';

    if (player == 'y' && toRow == 0) board[toRow][toCol] = 'Y';
    if (player == 'a' && toRow == SIZE - 1) board[toRow][toCol] = 'A';

    return true;
}

void jugarDamas() {
    initBoard();
    char player = 'y';
    char winner;
    int cursorRow = 0, cursorCol = 0;
    int selectedRow = -1, selectedCol = -1;
    bool selecting = false;

    while (true) {
        bool mustCapture = playerHasCapture(player);
        printBoard(cursorRow, cursorCol);
        std::cout << "\nTurno de " << player << "\n";
        if (mustCapture) std::cout << "(*) Piezas marcadas pueden capturar\n";
        if (selecting)
            std::cout << "Seleccionada: " << selectedRow << "," << selectedCol << "\n";
        std::cout << "Usa flechas para moverte, Enter para seleccionar/mover.\n";

        int key = _getch();
        if (key == 224) key = _getch();

        switch (key) {
        case 72: if (cursorRow > 0) cursorRow--; break;
        case 80: if (cursorRow < SIZE - 1) cursorRow++; break;
        case 75: if (cursorCol > 0) cursorCol--; break;
        case 77: if (cursorCol < SIZE - 1) cursorCol++; break;
        case 13:
            if (!selecting) {
                if ((player == 'y' && (board[cursorRow][cursorCol] == 'y' || board[cursorRow][cursorCol] == 'Y')) ||
                    (player == 'a' && (board[cursorRow][cursorCol] == 'a' || board[cursorRow][cursorCol] == 'A'))) {
                    selecting = true;
                    selectedRow = cursorRow;
                    selectedCol = cursorCol;
                }
            } else {
                bool captured = false;
                if (makeMove(selectedRow, selectedCol, cursorRow, cursorCol, player, captured)) {
                    if (captured && canCaptureFrom(cursorRow, cursorCol, player)) {
                        printBoard(cursorRow, cursorCol);
                        std::cout << "\nCaptura adicional disponible. Mismo turno.\n";
                        _getch();
                        selecting = true;
                        selectedRow = cursorRow;
                        selectedCol = cursorCol;
                        continue;
                    } else {
                        player = (player == 'y') ? 'a' : 'y';
                        selecting = false;
                    }

                    if (isGameOver(winner)) {
                        printBoard();
                        std::cout << "\nJuego terminado. Gana " << winner << ".\n";
                        _getch();
                        return;
                    }
                } else {
                    std::cout << "Movimiento invalido.\n";
                    _getch();
                    selecting = false;
                }
            }
            break;
        }
    }
}