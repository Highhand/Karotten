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
    Board board = Board();
    MoveGenerator moveGen = MoveGenerator();
    MoveEvaluator moveEval = MoveEvaluator();

    // std::pair<std::string, int> pr = moveEval.alphaBeta(4, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), true, board);
    // std::cout << "Score:" << pr.second << std::endl;

	//Event handler
	SDL_Event event;

    SDL_StartTextInput();

    std::string command = "";
    window.update( board );
    bool loop = true;
	//While application is running
    char lastCaptPiece = 0;
	while ( loop ) {
		//Handle events on queue
		while ( SDL_PollEvent( &event ) != 0 ) {
			//User requests quit
			if( event.type == SDL_QUIT ) {
				loop = false;
			}
            else if ( event.type == SDL_TEXTINPUT ) {
                command += event.text.text;
                std::cout << command << std::endl;
            }
            else if ( event.type == SDL_KEYUP ) {
                if ( event.key.keysym.sym == SDLK_RETURN ) {
                    std::cout << "enter: " << command << std::endl;
                    // TODO: Debugging
                    if (!command.empty() && command.at(0) == 'z') {
                        std::cout << "Undoing: " << command.substr(1,4) << std::endl;
                        board.undoMove(command.substr(1,4), lastCaptPiece);
                    } else {
                        std::cout << "Making: " << command << std::endl;
                        lastCaptPiece = board.makeMove ( command );
                    }
                    // board.makeMove();
                    std::cout << "White moves: " << std::endl;
                    printMoves(moveGen.generateMoves(board, true), board, moveGen, moveEval);
                    std::cout << "Black moves: " << std::endl;
                    printMoves(moveGen.generateMoves(board, false), board, moveGen, moveEval);
                    window.update( board );

                    command = "";
                }
                else if ( event.key.keysym.sym == SDLK_BACKSPACE ) {
                    if ( !command.empty() ) {
                        command.pop_back();
                    }
                    std::cout << "backspace: " << command << std::endl;
                }
            }
		}
	}

	return 0;
}
