#include <SDL2/SDL.h>
#include <iostream>
#include <limits> // <int> max, <int> min
#include <string>
#include <vector>
#include "Board.h"
#include "CommunicatorUCI.h"
#include "GraphicsWindow.h"
#include "MoveEvaluator.h"
#include "MoveGenerator.h"

int main( int argc, char* args[] )
{
    // GraphicsWindow window = GraphicsWindow();
    // window.loop();

    // Board board = Board();
    // MoveGenerator moveGen = MoveGenerator();
    // MoveEvaluator moveEval = MoveEvaluator();

    CommunicatorUCI uciComs = CommunicatorUCI();

    std::string tmp;
    getline(std::cin, tmp);
    if ( tmp == "uci" ) {
        uciComs.run();
    }

	return 0;
}
