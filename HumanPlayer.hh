#ifndef HUMANPLAYER_HH
#define HUMANPLAYER_HH

#include "Player.hh"
#include "Board.hh"

#include <cstdio>

class HumanPlayer: public Player {
    public:
        int getMove(Board& board) {
            int move;
            for (;;) {
                scanf("%d",&move);
                if (board.validMove(move)) break;
                printf("HumanPlayer: Invalid move.\n");
            }
            return move;
        }
};

#endif // HUMANPLAYER_HH
