#ifndef BOARD_HH
#define BOARD_HH

#include <vector>

class Board {
    private:
        long long bricks[2];
    public:
        Board();
        int result();
        bool validMove(int);
        std::vector<int> validMoves();
        void makeMove(int,int);
        void plot();
};

#endif // BOARD_HH
