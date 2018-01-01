#ifndef MOVE_EVALUATOR_H
#define MOVE_EVALUATOR_H

#include <string>
#include "Board.h"
#include "MoveGenerator.h"

class MoveEvaluator {
public:
    MoveEvaluator();
    ~MoveEvaluator();


    std::pair< std::string, int > FindBestMove( Board& board, bool white_turn );
    /*
     * alphaBeta(). Returns a pair where first item is the optimal move and the second item
     * is its score. The algorithm is a version of the minimax-algorithm where branches that leads to
     * a worse result than previously found are not evaluated (pruned away). Pseudo-code and further explanation
     * can be found on the wikipedia page: https://en.wikipedia.org/wiki/Alpha-beta_pruning
     */
    std::pair< std::string, int > AlphaBeta(int depth, int alpha, int beta, bool maximizing_player, Board& board);

    /*
     * evaluateBoard(). Returns an int that represents the boardstate value where a
     * higher value indicates a better state for white and a lower value indicates
     * a better state for black.
     */
    int EvaluateBoard( Board& board );

private:
    MoveGenerator move_generator;
};

#endif
