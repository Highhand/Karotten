#ifndef MOVE_EVALUATOR_H
#define MOVE_EVALUATOR_H

#include <string>
#include "Board.h"
#include "MoveGenerator.h"

class MoveEvaluator {
public:
    MoveEvaluator();
    ~MoveEvaluator();

    bool kingIsSafe( Board& board, MoveGenerator& moveGen, std::string move );
private:
};

#endif
