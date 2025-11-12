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

bool playerHasCapture(char player) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if ((player == 'y' && (board[i][j] == 'y' || board[i][j] == 'Y')) ||
                (player == 'a' && (board[i][j] == 'a' || board[i][j] == 'A')))
                if (canCaptureFrom(i, j, player))
                    return true;
    return false;
}

bool makeMove(int fromRow, int fromCol, int toRow, int toCol, char player, bool& captured) {
    char piece = board[fromRow][fromCol];
    if (piece == '.' || piece == ' ') return false;
    if (board[toRow][toCol] != '.') return false;

    int dr = toRow - fromRow;
    int dc = toCol - fromCol;
    if (std::abs(dr) != std::abs(dc)) return false;

    if (!playerHasCapture(player)) {
        int dir = (player == 'y') ? -1 : 1;
        if (!isKing(piece) && dr == dir && std::abs(dc) == 1) {
            board[toRow][toCol] = piece;
            board[fromRow][fromCol] = '.';
            if (player == 'y' && toRow == 0) board[toRow][toCol] = 'Y';
            if (player == 'a' && toRow == SIZE - 1) board[toRow][toCol] = 'A';
            captured = false;
            return true;
        }
        if (isKing(piece)) {
            int stepR = (dr > 0) ? 1 : -1;
            int stepC = (dc > 0) ? 1 : -1;
            int r = fromRow + stepR, c = fromCol + stepC;
            while (r != toRow && c != toCol) {
                if (board[r][c] != '.') return false;
                r += stepR; c += stepC;
            }
            board[toRow][toCol] = piece;
            board[fromRow][fromCol] = '.';
            captured = false;
            return true;
        }
        return false;
    }

    if (isKing(piece)) {
        int stepR = (dr > 0) ? 1 : -1;
        int stepC = (dc > 0) ? 1 : -1;
        int r = fromRow + stepR, c = fromCol + stepC;
        bool foundEnemy = false;
        int enemyR = -1, enemyC = -1;

        while (r != toRow && c != toCol) {
            if (board[r][c] == '.' || board[r][c] == ' ') {
                r += stepR; c += stepC;
                continue;
            }
            if (isOpponent(board[r][c], player) && !foundEnemy) {
                foundEnemy = true;
                enemyR = r; enemyC = c;
                r += stepR; c += stepC;
                continue;
            }
            return false;
        }

        if (foundEnemy && board[toRow][toCol] == '.') {
            board[enemyR][enemyC] = '.';
            board[toRow][toCol] = piece;
            board[fromRow][fromCol] = '.';
            captured = true;
            return true;
        }
    } else {
        if (std::abs(dr) == 2 && std::abs(dc) == 2) {
            int midR = (fromRow + toRow) / 2;
            int midC = (fromCol + toCol) / 2;
            if (isOpponent(board[midR][midC], player)) {
                board[midR][midC] = '.';
                board[toRow][toCol] = piece;
                board[fromRow][fromCol] = '.';
                if (player == 'y' && toRow == 0) board[toRow][toCol] = 'Y';
                if (player == 'a' && toRow == SIZE - 1) board[toRow][toCol] = 'A';
                captured = true;
                return true;
            }
        }
    }

    return false;
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

void jugarDamas() {
    initBoard();
    char player = 'y';
    char winner;

    while (true) {
        printBoard();
        std::cout << "\nTurno de " << player << "\n";
        std::cout << "Introduce movimiento (ejemplo: A3 B4): ";

        std::string from, to;
        std::cin >> from >> to;
        if (!std::cin || from.size() < 2 || to.size() < 2) break;

        int fromCol = letterToColumn(from[0]);
        int fromRow = from[1] - '0';
        int toCol = letterToColumn(to[0]);
        int toRow = to[1] - '0';

        if (fromCol == -1 || toCol == -1) continue;

        bool captured = false;
        if (!makeMove(fromRow, fromCol, toRow, toCol, player, captured)) {
            std::cout << "Movimiento inválido.\n";
            _getch();
            continue;
        }

        if (captured) {
            bool cadena = true;
            while (cadena) {
                printBoard();
                if (!canCaptureFrom(toRow, toCol, player)) break;

                std::cout << "\nCaptura adicional disponible. Mismo turno de " << player << ".\n";
                std::cout << "Siguiente destino (ejemplo: C5): ";
                std::string next;
                std::cin >> next;
                if (next.size() < 2) break;
                int nCol = letterToColumn(next[0]);
                int nRow = next[1] - '0';
                bool chainCaptured = false;
                if (!makeMove(toRow, toCol, nRow, nCol, player, chainCaptured) || !chainCaptured) {
                    std::cout << "Movimiento inválido.\n";
                    _getch();
                    break;
                }
                toRow = nRow;
                toCol = nCol;
            }
        }

        if (isGameOver(winner)) {
            printBoard();
            std::cout << "\nJuego terminado. Gana " << winner << ".\n";
            _getch();
            break;
        }

        player = (player == 'y') ? 'a' : 'y';
    }
}
