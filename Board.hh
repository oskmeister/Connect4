/**
 *  Board.hh
 *  Author: Oskar Werkelin Ahlin
 */
#ifndef BOARD_HH
#define BOARD_HH

#include <vector>

/**
 *  A Board represents the current state of the game. It is
 *  implemented using so called bitboards, with which we store
 *  the entire state of the game in two 64-bit longs.
 **/
class Board {
    private:
        long long bricks[2];
    public:
        /**
         * Default constructor.
         **/
        Board();
        /** 
         * Secondary constructor. Allows you to create a new 
         * board given a board, a player and a move. It basically 
         * takes the given board and makes the specified move
         * for the specified player.
         *
         * @param Board The board on which to make the move.
         * @param Column The move to make.
         * @param Player The player who makes the move (0/1).
         **/
        Board(Board &,int,int);

        /**
         * Returns the result of the game. Returns -1 if the game
         * didn't end. 0 means first player won, 1 means second 
         * player won and 2 means the game ended in a draw.
         *
         * @return Game result.
         **/
        int result();

        /**
         * Checks if the specified move is valid, basically
         * if there's at least one empty slot in the specified 
         * column.
         *
         * @param Move
         * @return If the move is valid.
         **/
        bool validMove(int);

        /**
         * Returns a vector of possible moves.
         *
         * @return A vector<int> of possible moves.
         **/
        std::vector<int> validMoves();

        /**
         * Makes a move for this board, and thus changes
         * the state of it.
         *
         * @param Move column
         * @param Player The player who made the move.
         **/
        void makeMove(int,int);

        /**
         * Plots the current board to the terminal, with 'X' and
         * 'O' for player 1 and 0 respectively.
         **/
        void plot();

        /** 
         * Returns a heuristic score for the current board position. 
         * Positive score means advantage for player 0, and 
         * negative score means advantage for player 1.
         *
         * @return board evaluation
         */
        int score();
};

#endif // BOARD_HH
