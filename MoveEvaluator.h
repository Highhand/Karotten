#ifndef MOVE_EVALUATOR_H
#define MOVE_EVALUATOR_H

#include <string>
#include "Board.h"
#include "MoveGenerator.h"

class MoveEvaluator {
public:
    MoveEvaluator();
    ~MoveEvaluator();

    /*
     * alphaBeta(). Returns a pair where first item is the optimal move and the second item
     * is its score. The algorithm is a version of the minimax-algorithm where branches that leads to
     * a worse result than previously found are not evaluated (pruned away). Pseudo-code and further explanation
     * can be found on the wikipedia page: https://en.wikipedia.org/wiki/Alpha-beta_pruning
     */
    std::pair< std::string, int > alphaBeta(int depth, int alpha, int beta, bool maximizingPlayer, Board& board);

    int evaluateBoard( Board& board );

    bool kingIsSafe( Board& board, MoveGenerator& moveGen, std::string move );
private:
};

#endif
