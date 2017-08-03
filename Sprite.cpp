#include "Sprite.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Sprite::Sprite() {}

Sprite::Sprite( SDL_Renderer* renderer, std::string filepath ) {
    this->renderer = renderer;
    SDL_Surface* surface = IMG_Load( filepath.c_str() );
    if ( surface == nullptr ) {
        std::cout << "Unable to load image SDL_image Error: " << IMG_GetError() << std::endl;
    }
    this->texture = SDL_CreateTextureFromSurface( this->renderer, surface );

    this->width = surface->w;
    this->height = surface->h;

    SDL_FreeSurface( surface );
}

Sprite::~Sprite() {
    SDL_DestroyTexture( this->texture );
}

void Sprite::drawSprite( int column, int row, int width, int height, Piece piece, Color color ) {
    SDL_Rect _srcRect;

    switch ( piece ) {
        case Piece::Knight:
            _srcRect.x = (this->width)/6*0;
            break;
        case Piece::Pawn:
            _srcRect.x = (this->width)/6*1;
            break;
        case Piece::Rook:
            _srcRect.x = (this->width)/6*2;
            break;
        case Piece::Bishop:
            _srcRect.x = (this->width)/6*3;
            break;
        case Piece::King:
            _srcRect.x = (this->width)/6*4;
            break;
        case Piece::Queen:
            _srcRect.x = (this->width)/6*5;
            break;
        default:
            _srcRect.x = 0;
            break;
    }

    switch ( color ) {
        case Color::White:
            _srcRect.y = (this->height)/2*0;
            break;
        case Color::Black:
            _srcRect.y = (this->height)/2*1;
            break;
        default:
            _srcRect.y = 0;
            break;
    }

    _srcRect.w = (this->width)/6;
    _srcRect.h = (this->height)/2;

    SDL_Rect _destRect;
    _destRect.x = column*width;
    _destRect.y = row*height;
    _destRect.w = width;
    _destRect.h = height;
    SDL_RenderCopy( this->renderer, this->texture, &_srcRect, &_destRect );
}
