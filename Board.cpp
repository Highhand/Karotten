#include "Board.h"
#include <iostream>

Board::Board() {
    this->currentBoard[0] = { 4, 2, 3, 5, 6, 3, 2, 4 };
    this->currentBoard[1] = { 1, 1, 1, 1, 1, 1, 1, 1 };
    this->currentBoard[2] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    this->currentBoard[3] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    this->currentBoard[4] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    this->currentBoard[5] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    this->currentBoard[6] = { -1, -1, -1, -1, -1, -1, -1, -1 };
    this->currentBoard[7] = { -4, -2, -3, -5, -6, -3, -2, -4 };
    std::cout << "Created Board" << std::endl;
}

Board::~Board() {
    std::cout << "Destroyed Board" << std::endl;
}

std::array< std::array< char, BOARD_WIDTH >, BOARD_HEIGHT > Board::getCurrentBoard() {
    return this->currentBoard;
}

char Board::makeMove( std::string move ) {
    if ( move.size() != 4 ) return 0;
    int columnFrom, rowFrom, columnTo, rowTo;
    char capturedPiece = 0;
    columnFrom = this->columnToInt( move.at(0) );
    rowFrom = this->rowToInt( move.at(1) );
    columnTo = this->columnToInt( move.at(2) );
    rowTo = this->rowToInt( move.at(3) );
    // Update board and check if valid pos to avoid segmentation error
    if ( this->isValidPos(columnFrom, rowFrom) && this->isValidPos(columnTo, rowTo) &&
         !this->isFree(columnFrom, rowFrom) )
    {
        // std::cout << "Move " << this->positionToString(columnFrom, rowFrom) << " to "
        //           << this->positionToString(columnTo, rowTo) << " and capturing: "
        //           << (int)this->getPieceAt(columnTo, rowTo) << std::endl;

        capturedPiece = this->getPieceAt(columnTo, rowTo);
        this->setPieceAt(columnTo, rowTo, this->getPieceAt(columnFrom, rowFrom));
        this->setPieceAt(columnFrom, rowFrom, 0);
    }
    return capturedPiece;
}

void Board::undoMove( std::string move, char capturedPiece ) {
    if ( move.size() != 4 ) return;
    int columnFrom, rowFrom, columnTo, rowTo;
    columnFrom = this->columnToInt( move.at(2) );
    rowFrom = this->rowToInt( move.at(3) );
    columnTo = this->columnToInt( move.at(0) );
    rowTo = this->rowToInt( move.at(1) );
    // Update board and check if valid pos to avoid segmentation error
    if ( this->isFree(columnTo, rowTo) )
    {
        // std::cout << "Move " << this->positionToString(columnFrom, rowFrom) << " to "
        //           << this->positionToString(columnTo, rowTo) << " and uncapturing: "
        //           << (int)capturedPiece << std::endl;

        this->setPieceAt(columnTo, rowTo, this->getPieceAt(columnFrom, rowFrom));
        this->setPieceAt(columnFrom, rowFrom, capturedPiece);
    }
}

/* Helper functions */

char Board::getPieceAt( std::string pos ) {
    if ( pos.size() != 2 ) return -1;
    int column, row;
    column = this->columnToInt( pos.at(0) );
    row = this->rowToInt( pos.at(1) );
    return this->currentBoard[row][column];
}

char Board::getPieceAt( int column, int row ) {
    return this->currentBoard[row][column];
}

void Board::setPieceAt( std::string pos, char piece ) {
    // std::cout << "M1, Setting pos " << pos
    //           << " to " << (int)piece << std::endl;
    if ( pos.size() != 2 ) return;
    int column, row;
    column = this->columnToInt( pos.at(0) );
    row = this->rowToInt( pos.at(1) );
    if ( piece >= -6 && piece <= 6 ) {
        this->currentBoard[row][column] = piece;
    }
    else {
        this->currentBoard[row][column] = 0;
    }
}

void Board::setPieceAt( int column, int row, char piece ) {
    // std::cout << "M2, Setting pos " << this->positionToString(column, row)
    //           << " to " << (int)piece << std::endl;
    if ( piece >= -6 && piece <= 6 ) {
        this->currentBoard[row][column] = piece;
    }
    else {
        this->currentBoard[row][column] = 0;
    }
}

std::string Board::positionToString( int column, int row ) {
    std::string res = "";
    switch ( column ) {
        case 0:
            res += "a";
            break;
        case 1:
            res += "b";
            break;
        case 2:
            res += "c";
            break;
        case 3:
            res += "d";
            break;
        case 4:
            res += "e";
            break;
        case 5:
            res += "f";
            break;
        case 6:
            res += "g";
            break;
        case 7:
            res += "h";
            break;
        default:
            res += "x";
            break;
    }
    res += std::to_string(row+1);
    return res;
}

int Board::columnToInt( char column ) {
    int res;
    switch ( column ) {
        case 'a':
            res = 0;
            break;
        case 'b':
            res = 1;
            break;
        case 'c':
            res = 2;
            break;
        case 'd':
            res = 3;
            break;
        case 'e':
            res = 4;
            break;
        case 'f':
            res = 5;
            break;
        case 'g':
            res = 6;
            break;
        case 'h':
            res = 7;
            break;
        default:
            res = -1;
            break;
    }
    return res;
}

int Board::rowToInt( char row ) {
    int res = row - '1';
    if ( this->isValidRow( res ) ) {
        return res;
    }
    else {
        return -1;
    }
}

bool Board::isValidRow( int row ) {
    return row >= 0 && row < BOARD_HEIGHT;
}

bool Board::isValidColumn( int column ) {
    return column >= 0 && column < BOARD_WIDTH;
}

bool Board::isValidPos( int column, int row ) {
    return isValidColumn(column) && isValidRow(row);
}

bool Board::isCapture( int column, int row, bool isWhite ) {
    if ( isValidPos(column, row) ) {
        return (this->currentBoard[row][column] > 0 && !isWhite) ||
               (this->currentBoard[row][column] < 0 && isWhite);
    }
    return false;
}

bool Board::isFree( int column, int row ) {
    return isValidPos(column, row) && this->currentBoard[row][column] == 0;
}
/* --- */
