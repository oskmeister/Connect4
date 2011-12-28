#ifndef ALPHABETAPLAYER_HH
#define ALPHABETAPLAYER_HH

#include "Player.hh"
#include "Board.hh"

#include <vector>
#include <cstdio>
#include <algorithm>

#define MAXDEPTH 10

class AlphaBetaPlayer: public Player {
    public:
        int alphaBeta(Board cur, int d, int alpha, int beta, int turn) {
            if (!d || cur.result() != -1) { 
                int ret = cur.score()*(playerid?-1:1);
                return ret; 
            }
            std::vector<int> possibleMoves = cur.validMoves();
            if (playerid&&turn||!playerid&&(!turn)) { /* maximizing player */
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
