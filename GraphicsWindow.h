#ifndef GRAPHICS_WINDOW_H
#define GRAPHICS_WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Board.h"
#include "Sprite.h"

const int BOARD_WIDTH = 640;
const int BOARD_HEIGHT = 480;
const int COMMAND_HEIGHT = 20;
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = BOARD_HEIGHT + COMMAND_HEIGHT;

class GraphicsWindow {
public:
    GraphicsWindow();
    ~GraphicsWindow();

    void update( Board board, std::string command );
private:
    void drawBackground();
    void drawBoard( Board board);
    void drawCommand( std::string command );

    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    Sprite* sprite;
};

#endif
