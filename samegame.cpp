#include <iostream>
#include "BoardState.h"
#include "SearchUtils.h"

using namespace std;



int main() {
    int total_top_score = 0;
    double total_avg_score = 0.0;

    for (int i = 0; i < 250; i++) {
        cout << "board index: " << i << endl;

        BoardState gameBoardState(i);  // The board state of the game

        cout << "init board: " << endl;
        gameBoardState.printBoard();

        MCTS mcts = MCTS(gameBoardState);

        int topscore;
        double avg_score;

        mcts.search(topscore, avg_score);

        total_top_score += topscore;
        total_avg_score += avg_score;
    }

    cout << "total_top_score: " << total_top_score << endl;
    cout << "total_avg_score: " << total_avg_score << endl;

    return 0;
}
