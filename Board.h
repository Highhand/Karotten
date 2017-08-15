#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <string>
#include <vector>

class Board {
public:
    Board();
    ~Board();

    static const int WIDTH = 8;
    static const int HEIGHT = 8;

    std::array< std::array< char, WIDTH >, HEIGHT > getCurrentBoard();
    /*
     * getPieceAt(). Returns piece at given position. If invalid position
     * return 0.
     */
    char getPieceAt( std::string );
    char getPieceAt( int column, int row );

    void setPieceAt( std::string, char piece );
    void setPieceAt( int column, int row, char piece );

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
     * Converts a position to a string in UCI-format i.e. (3,3) -> "d4"
     */
    std::string positionToString(int column, int row );

    int columnToInt( char );
    int rowToInt( char );

    bool isValidColumn( int );
    bool isValidRow( int );
    bool isValidPos( int column, int row );

    bool isCapture( int column, int row, bool isWhite );
    bool isFree( int column, int row );
private:
    // enum { WIDTH = 8, HEIGHT = 8 };
    std::array< std::array< char, WIDTH >, HEIGHT > currentBoard;
    // Hold the last valid move sent to makeMove(). undoMove() does not affect this var.
    std::string lastMove;
};

#endif
