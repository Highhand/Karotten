#include "GraphicsWindow.h"
#include <iostream>
#include <string>
#include <SDL2/SDL_image.h>

GraphicsWindow::GraphicsWindow() {
    //Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		//Create window and renderer
		if( SDL_CreateWindowAndRenderer( WINDOW_WIDTH, WINDOW_HEIGHT, 0, &this->window, &this->renderer ) == -1 )
		{
			std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
		}
	}
    //Initialize PNG loading and check if PNG Init flag was set
    if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
    {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else {
        this->sprite = new Sprite( this->renderer, "chess.png" );
    }
}

GraphicsWindow::~GraphicsWindow() {
    delete(this->sprite);
    SDL_DestroyRenderer( this->renderer );
    SDL_DestroyWindow( this->window );
    IMG_Quit();
    SDL_Quit();
}

void GraphicsWindow::update( Board board ) {
    std::cout << "update window" << std::endl;
    // Draw board
    this->drawBackground();
    this->drawBoard( board );
    SDL_RenderPresent( this->renderer );
}

void GraphicsWindow::drawBackground() {
    SDL_SetRenderDrawColor( this->renderer, 0xF5, 0xF5, 0xDC, 0xFF );
    SDL_RenderClear( this->renderer );
    SDL_SetRenderDrawColor( this->renderer, 0x8E, 0x6B, 0x23, 0xFF );
    for ( int row = 0; row < 8; row++ ) {
        for ( int column = 0; column < 8; column++ ) {
            // If not even draw rect
            if ( (column + row) % 2 != 0 ) {
                SDL_Rect square;
                square.x = column*(WINDOW_WIDTH/8);
                square.y = row*(WINDOW_HEIGHT/8);
                square.w = (WINDOW_WIDTH/8);
                square.h = (WINDOW_HEIGHT/8);
                SDL_RenderFillRect( this->renderer, &square );
            }
        }
    }
}

void GraphicsWindow::drawBoard(Board board) {
    auto currBoard = board.getCurrentBoard();
    for ( int row = 0; row < currBoard.size() ; row++ ) {
        for ( int column = 0; column < currBoard[row].size() ; column++ ) {
            char currPos = currBoard[row][column];

            // Empty position
            if ( currPos == 0 ) continue;

            Color color;
            Piece piece;
            currPos < 0 ? color = Color::Black : color = Color::White;

            switch ( abs(currPos) ) {
                case 1:
                    piece = Piece::Pawn;
                    break;
                case 2:
                    piece = Piece::Knight;
                    break;
                case 3:
                    piece = Piece::Bishop;
                    break;
                case 4:
                    piece = Piece::Rook;
                    break;
                case 5:
                    piece = Piece::Queen;
                    break;
                case 6:
                    piece = Piece::King;
                    break;
                default:
                    piece = Piece::Pawn;
                    break;
            }

            // Draw piece on current position
            this->sprite->drawSprite( column, row, WINDOW_WIDTH/8, WINDOW_HEIGHT/8, piece, color );
        }
    }
}
