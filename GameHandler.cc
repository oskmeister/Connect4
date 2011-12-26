#include "GameHandler.hh"

#include "Player.hh"
#include "HumanPlayer.hh"

void GameHandler::play() {
    Player* p[2];
    p[0] = new HumanPlayer();
    p[1] = new HumanPlayer();
    int turn = 0,move;
    board.plot();
    while (board.result() == -1) {
        move = p[turn%2]->getMove(board);
        printf("GameHandler: Player %d played %d.\n", turn%2, move);
        board.makeMove(move, turn%2);
        board.plot();
        ++turn;
    }
    int res;
    if ((res=board.result()) == 2) printf("Draw!\n");
    else printf("Player %d won!\n",res);
}
