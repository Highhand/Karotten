#include "Board.h"

Board::Board() {
    this->currentBoard[0] = { 4, 2, 3, 5, 6, 3, 2, 4 };
    this->currentBoard[1] = { 1, 1, 1, 1, 1, 1, 1, 1 };
    this->currentBoard[2] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    this->currentBoard[3] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    this->currentBoard[4] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    this->currentBoard[5] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    this->currentBoard[6] = { -1, -1, -1, -1, -1, -1, -1, -1 };
    this->currentBoard[7] = { -4, -2, -3, -5, -6, -3, -2, -4 };
}

Board::~Board() {}

std::array< std::array< char, 8 >, 8 > Board::getCurrentBoard() {
    return this->currentBoard;
}
