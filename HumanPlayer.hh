/**
 * HumanPlayer.hh
 * Author: Oskar Werkelin Ahlin
 **/

#ifndef HUMANPLAYER_HH
#define HUMANPLAYER_HH

#include "Player.hh"
#include "Board.hh"

#include <cstdio>

/** 
 * Simple class that makes moves by reading from stdin. Also
 * checks that the given moves are valid. 
 */
class HumanPlayer: public Player {
    public:
        /** 
         * Get a move. Read from stdin.
         *
         * @param Board current board
         * @return Desired move.
         **/
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
