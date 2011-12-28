#ifndef MINIMAXPLAYER_HH
#define MINIMAXPLAYER_HH

#include "Player.hh"
#include "Board.hh"

class MiniMaxPlayer: public Player {
    public:
        int getMove(Board& board) {
            for (int i = 0; i < 7; ++i) {
                if (board.validMove(i)) {
                    return i;
                }
            }
            return -1;
        }
};

#endif // MINIMAXPLAYER_HH
