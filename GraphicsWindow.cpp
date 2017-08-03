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
                SDL_Rect _square;
                _square.x = column*(WINDOW_WIDTH/8);
                _square.y = row*(WINDOW_HEIGHT/8);
                _square.w = (WINDOW_WIDTH/8);
                _square.h = (WINDOW_HEIGHT/8);
                SDL_RenderFillRect( this->renderer, &_square );
            }
        }
    }
}

void GraphicsWindow::drawBoard(Board board) {
    auto _currBoard = board.getCurrentBoard();
    for ( int row = 0; row < _currBoard.size() ; row++ ) {
        for ( int column = 0; column < _currBoard[row].size() ; column++ ) {
            char _currPos = _currBoard[row][column];

            // Empty position
            if ( _currPos == 0 ) continue;

            Color _color;
            Piece _piece;
            _currPos < 0 ? _color = Color::Black : _color = Color::White;

            switch ( abs(_currPos) ) {
                case 1:
                    _piece = Piece::Pawn;
                    break;
                case 2:
                    _piece = Piece::Knight;
                    break;
                case 3:
                    _piece = Piece::Bishop;
                    break;
                case 4:
                    _piece = Piece::Rook;
                    break;
                case 5:
                    _piece = Piece::Queen;
                    break;
                case 6:
                    _piece = Piece::King;
                    break;
                default:
                    _piece = Piece::Pawn;
                    break;
            }

            // Draw piece on current position
            this->sprite->drawSprite( column, row, WINDOW_WIDTH/8, WINDOW_HEIGHT/8, _piece, _color );
        }
    }
}
