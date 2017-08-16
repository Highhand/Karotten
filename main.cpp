#include <SDL2/SDL.h>
#include <iostream>
#include <limits> // <int> max, <int> min
#include <string>
#include <vector>
#include "Board.h"
#include "GraphicsWindow.h"
#include "MoveEvaluator.h"
#include "MoveGenerator.h"

void printMoves(std::vector<std::string> list, Board& board, MoveGenerator& moveGen, MoveEvaluator& moveEval) {
    std::cout << "Number of moves: " << list.size() << std::endl;
    std::cout << "Moves: " << std::endl;
    for (int i = 0; i <  list.size(); i++) {
        std::cout << list.at(i);
        if ( !moveEval.kingIsSafe(board, moveGen, list.at(i)) ) {
            std::cout << " places own kings in check" << std::endl;
        }
        else {
            std::cout << " is a safe move" << std::endl;
        }
    }
    std::cout << std::endl;
}

int main( int argc, char* args[] )
{
    GraphicsWindow window = GraphicsWindow();
    window.loop();

    // Board board = Board();
    // MoveGenerator moveGen = MoveGenerator();
    // MoveEvaluator moveEval = MoveEvaluator();

	return 0;
}
