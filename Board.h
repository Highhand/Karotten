#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <string>
#include <vector>

const int BOARD_WIDTH = 8;
const int BOARD_HEIGHT = 8;

class Board {
public:
    Board();
    ~Board();

    std::array< std::array< char, BOARD_WIDTH >, BOARD_HEIGHT > getCurrentBoard();
    std::string getLastMove();
    /*
     * makeMove() Updates current board based on input and returns captured piece
     */
    char makeMove( std::string move );
    /*
     * undoMove() Updates current board based on input
     */
    void undoMove( std::string move, char capturedPiece );
    /*
     * getPieceAt(), Returns value at pos provided as arg
     */
    char getPieceAt( std::string );
    char getPieceAt( int column, int row );
    /*
     * setPieceAt(), Writes value to pos provided as arg
     */
    void setPieceAt( std::string, char piece );
    void setPieceAt( int column, int row, char piece );
    /*
     * Converts a position to a string in UCI-format i.e. (3,3) -> "d4"
     */
    std::string positionToString(int column, int row );

    /*
     * Converts a character a-h to corresponding number i.e. b -> 1
     */
    int columnToInt( char );
    int rowToInt( char );

    bool isValidColumn( int );
    bool isValidRow( int );

    bool isValidPos( int column, int row );
    bool isCapture( int column, int row, bool isWhite );
    bool isFree( int column, int row );
    /* --- */
private:
    std::array< std::array< char, BOARD_WIDTH >, BOARD_HEIGHT > currentBoard;
    std::string lastMove;
};

#endif
