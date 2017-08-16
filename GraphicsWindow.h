#ifndef GRAPHICS_WINDOW_H
#define GRAPHICS_WINDOW_H

#include <SDL2/SDL.h>
#include <string>
#include "Board.h"
#include "Sprite.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

class GraphicsWindow {
public:
    GraphicsWindow();
    ~GraphicsWindow();

    void loop();
    void update( Board& board );
private:
    void drawBackground();
    void drawBoard( Board& board);

    SDL_Window* window;
    SDL_Renderer* renderer;
    Sprite* sprite;
};

#endif
