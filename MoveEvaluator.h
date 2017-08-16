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

    /*
     * evaluateBoard(). Returns an int that represents the boardstate value where a
     * higher value indicates a better state for white and a lower value indicates
     * a better state for black.
     */
    int evaluateBoard( Board& board );

    /*
     * kingIsSafe(). Controls that a move will not place your own king in check.
     * Generetes moves for all pieces from the kings position and then checks if the
     * king can capture a piece using that piece's moves. If the king can capture the piece
     * then the piece can also capture the king i.e. the king is checked. Returns false
     * as soon as one instance of these kind of moves and piece combination is found.
     */
    bool kingIsSafe( Board& board, MoveGenerator& moveGen, std::string move );
private:
    MoveGenerator moveGen;
};

#endif
