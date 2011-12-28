/**
 *  AlphaBetaPlayer.hh
 *  Author: Oskar Werkelin Ahlin
 *
 *  An AI player using alpha-beta pruning for finding good moves. 
 *  Instantiate the class with a board, then use getMove to retrieve
 *  moves.
 **/
#ifndef ALPHABETAPLAYER_HH
#define ALPHABETAPLAYER_HH

#include "Player.hh"
#include "Board.hh"

#include <vector>
#include <cstdio>
#include <algorithm>

#define MAXDEPTH 8

class AlphaBetaPlayer: public Player {
    public:
        /**
         * The main function for alpha-beta pruning.
         *
         * @param cur The current board.
         * @param d Current number of max depth steps left.
         * @param alpha Alpha in 'alpha-beta pruning'.
         * @param beta Beta in 'alpha-beta pruning'.
         * @param turn The current turn.
         * @return Best evaluation for sub tree.
         */
        int alphaBeta(Board cur, int d, int alpha, int beta, int turn) {
            if (!d || cur.result() != -1) { 
                int ret = cur.score()*(playerid?-1:1);
                return ret; 
            }
            std::vector<int> possibleMoves = cur.validMoves();
            if ((playerid&&turn)||(!playerid&&(!turn))) { /* maximizing player */
                for (int i = 0; i < (int)possibleMoves.size(); ++i) {
                    Board newBoard(cur, possibleMoves[i], turn);
                    alpha = std::max(alpha, alphaBeta(newBoard, d-1, alpha, beta, turn^1));
                    if (beta <= alpha) break;
                }
                return alpha;
            } else { /* minimizing player */
                for (int i = 0; i < (int)possibleMoves.size(); ++i) {
                    Board newBoard(cur, possibleMoves[i], turn);
                    beta = std::min(beta, alphaBeta(newBoard, d-1, alpha, beta, turn^1));
                    if (beta <= alpha) break;
                }
                return beta;
            }
            return 0;
        }

        /** 
         * getMove uses alpha-beta pruning for calculating evaluation
         * for possible moves, and makes the move which most benefits 
         * the agent. Also prints the evaluation of the best possible move.
         *
         * See Player.hh
         *
         * @param Board The current game board.
         * @return The decided move.
         **/
        int getMove(Board& curboard) {
            std::vector<int> moves = curboard.validMoves();
            std::vector<int> candMoves;
            int bestScore = playerid?-(1<<25):-(1<<25);
            for (int i = (int)moves.size()-1; i+1; --i) {
                Board newboard = Board(curboard, moves[i], playerid);
                int curScore = alphaBeta(newboard, MAXDEPTH, -(1<<15), 1<<15, playerid^1);
                if (curScore > bestScore) {
                    candMoves.clear();
                    bestScore = curScore;
                    candMoves.push_back(moves[i]);
                } else if (curScore == bestScore) {
                    candMoves.push_back(moves[i]);
                }
            }
            printf("AlphaBetaPlayer (player %d) eval: %d\n",playerid,bestScore);
            return candMoves[(rand()%((int)candMoves.size()))];
        }
};

#endif // ALPHABETAPLAYER_HH
