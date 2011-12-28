/**
 * GameHandler.hh
 * Author: Oskar Werkelin Ahlin
 */

#include "Board.hh"
#include "Player.hh"

#ifndef GAME_HH
#define GAME_HH

/**
 * A GameHandler is responsible for managing a Connect-4 game.
 * It makes sure that players take turns, checks for wins between
 * moves etc. It also specifies what kinds of players should be
 * used.
 */
class GameHandler {
    private:
        Board board;
    public:
        /** 
         * Plays a game.
         **/
        void play(); 
};

#endif // GAME_HH
