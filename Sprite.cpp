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
    SDL_Rect srcRect;

    switch ( piece ) {
        case Piece::Knight:
            srcRect.x = (this->width)/6*0;
            break;
        case Piece::Pawn:
            srcRect.x = (this->width)/6*1;
            break;
        case Piece::Rook:
            srcRect.x = (this->width)/6*2;
            break;
        case Piece::Bishop:
            srcRect.x = (this->width)/6*3;
            break;
        case Piece::King:
            srcRect.x = (this->width)/6*4;
            break;
        case Piece::Queen:
            srcRect.x = (this->width)/6*5;
            break;
        default:
            srcRect.x = 0;
            break;
    }

    switch ( color ) {
        case Color::White:
            srcRect.y = (this->height)/2*0;
            break;
        case Color::Black:
            srcRect.y = (this->height)/2*1;
            break;
        default:
            srcRect.y = 0;
            break;
    }

    srcRect.w = (this->width)/6;
    srcRect.h = (this->height)/2;

    SDL_Rect destRect;
    destRect.x = column*width;
    destRect.y = row*height;
    destRect.w = width;
    destRect.h = height;
    SDL_RenderCopy( this->renderer, this->texture, &srcRect, &destRect );
}
