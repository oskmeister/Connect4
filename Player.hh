#ifndef PLAYER_HH
#define PLAYER_HH

#include "Board.hh"

class Player {
    public:
        int playerid;
        virtual int getMove(Board& board)=0;
};

#endif // PLAYER_HH
