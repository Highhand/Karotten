#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "Board.h"
#include "GraphicsWindow.h"

int main( int argc, char* args[] )
{
    GraphicsWindow window = GraphicsWindow();
    Board board = Board();
	//Event handler
	SDL_Event event;

    std::string test = "";
    true ? test = "1" : test = "2";
    std::cout << test << std::endl;

    SDL_StartTextInput();

    std::string command = "";
    window.update( board );
    bool loop = true;
	//While application is running
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
                    board.registerMove ( command );
                    board.makeMove();
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
