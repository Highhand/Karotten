#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL2/SDL.h>

enum class Piece { Knight, Pawn, Rook, Bishop, King, Queen };
enum class Color { White, Black };

class Sprite {
public:
    Sprite();
    Sprite( SDL_Renderer* renderer, std::string path );
    ~Sprite();

    /*
     * Draws sprite
     */
    void drawSprite( int column, int row , int width, int height, Piece piece, Color color );
private:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    int width;
    int height;
};

#endif
