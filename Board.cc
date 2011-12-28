#include "Board.hh"

#include <cstdio>
#include <cstdlib>

#define COLS 7LL
#define ROWS 6LL

Board::Board() {
    bricks[0] = 0;
    bricks[1] = 0;
}

Board::Board(Board& b, int c, int p) {
    bricks[0] = b.bricks[0];
    bricks[1] = b.bricks[1];
    makeMove(c,p);
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
    if (validMoves().size() == 0) return 2;
    return -1;
}

int Board::score() {
    int result_check = result();
    if (result_check != -1) {
        if (result_check == 2) return 0;
        if (result_check == 0) return 1<<15;
        if (result_check == 1) return -(1<<15);
    }
    return 0;
}

