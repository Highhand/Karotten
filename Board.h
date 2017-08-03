#ifndef BOARD_H
#define BOARD_H

#include <array>

class Board {
public:
    Board();
    ~Board();
    std::array< std::array< char, 8 >, 8 > getCurrentBoard();
private:
    std::array< std::array< char, 8 >, 8 > currentBoard;
};

#endif
