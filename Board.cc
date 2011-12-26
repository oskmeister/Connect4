#include "Board.hh"

#include <cstdio>

#define COLS 7LL
#define ROWS 6LL

Board::Board() {
    bricks[0] = 0;
    bricks[1] = 0;
}

std::vector<int> Board::validMoves() {
    std::vector<int> result;
    long long all = bricks[0] | bricks[1];
    for (int i = 0; i < COLS; ++i) if (!(all & (1<<i))) result.push_back(i);
    return result;
}

bool Board::validMove(int c) {
    if (c < 0 || c >= COLS) return false;
    return !((bricks[0] | bricks[1]) & (1<<c));
}

void Board::makeMove(int c, int p) {
    long long bit = 1LL<<(c+(COLS+1)*(ROWS-1));
    long long all = bricks[0] | bricks[1];
    while (all & bit) {
        bit >>= (COLS+1);
    }   
    bricks[p] |= bit;
}

void Board::plot() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            bool printed = false;
            for (int p = 0; p < 2; ++p) {
                if (bricks[p] & (1LL<<((COLS+1)*i+j))) {
                    printed = true;
                    printf("%c ",p?'X':'O');
                }   
            }
            if (!printed) printf(". ");
        }
        printf("\n");
    }
}

int Board::result() {
    unsigned long long temp;
    for (int p = 0; p < 2; ++p) {
        temp = bricks[p] & (bricks[p]<<1);
        if (temp & (temp<<2)) return p;
        temp = bricks[p] & (bricks[p]<<(COLS+1));
        if (temp & (temp<<(2*(COLS+1)))) return p;
        temp = bricks[p] & (bricks[p]<<(COLS+1+1));
        if (temp & (temp<<(2*(COLS+1+1)))) return p;
        temp = bricks[p] & (bricks[p]<<(COLS+1-1));
        if (temp & (temp<<(2*(COLS+1-1)))) return p;
    }
    return -1;
}
