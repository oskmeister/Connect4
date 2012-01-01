/**
 *  Board.cc
 *  Author: Oskar Werkelin Ahlin
 */
#include "Board.hh"
#include <cstdio>
#include <cstdlib>

#define COLS 7LL
#define ROWS 6LL

#define ROW_SHIFT 1
#define COL_SHIFT 8
#define DIAG_SHIFT1 7
#define DIAG_SHIFT2 9

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
        else return -(1<<15);
    }

    int ret = 0;
    long long all = bricks[0] | bricks[1];
    long long tmp1,tmp2,tmp3;

    int shifts[3] = {ROW_SHIFT,DIAG_SHIFT1,DIAG_SHIFT2}; // ignore vertical
    
    for (int p = 0; p < 2; ++p) {
        for (int ss = 0; ss < 3; ++ss) {
            
            // O--O
            tmp1 = bricks[p]&(bricks[p] << 3*shifts[ss]);
            tmp2 = ~bricks[!p];
            tmp2 &= (tmp2<<shifts[ss]);
            tmp2 &= (tmp2<<shifts[ss]);
            tmp2 &= (tmp2<<shifts[ss]);
            tmp2 &= tmp1;
            ret += 3*(p?-1:1)*__builtin_popcountll(tmp2);

            // OO
            tmp3 = bricks[p] & (bricks[p]<<(1*shifts[ss]));
            ret += 2*(p?-1:1)*__builtin_popcountll(tmp3);
            
            // OOO
            tmp3 = bricks[p] & (bricks[p]<<(1*shifts[ss])) & (bricks[p]<<(2*shifts[ss]));
            ret += 7*(p?-1:1)*__builtin_popcountll(tmp3);
            
            // O-OO / OO-O
            tmp1 = bricks[p]&(bricks[p] << 3*shifts[ss]);
            tmp2 = ~bricks[!p];
            tmp2 &= (tmp2<<shifts[ss]);
            tmp2 &= (tmp2<<shifts[ss]);
            tmp2 &= (tmp2<<shifts[ss]);
            tmp2 &= tmp1;
            tmp2 &= (bricks[p]<<(2*shifts[ss])|bricks[p]<<(shifts[ss]));
            ret += 10*(p?-1:1)*__builtin_popcountll(tmp2);
            
        }
    }
    return ret;
}

