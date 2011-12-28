/**
 * Player.hh
 * Author: Oskar Werkelin Ahlin
 **/

#ifndef PLAYER_HH
#define PLAYER_HH

#include "Board.hh"

/**
 * Player is an abstract class which represents a player objects. All
 * inheriting classes must implement getMove().
 **/
class Player {
    public:
        /*
         * Id of the player (0/1).
         */
        int playerid;

        /**
         * Returns a move.
         *
         * @param Board Current board.
         * @return Move Decided move.
         */
        virtual int getMove(Board& board)=0;
};

#endif // PLAYER_HH
