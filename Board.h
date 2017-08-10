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
    /*
     * makeMove() Generetas possible moves and executes one
     */
    void makeMove();
    /*
     * registerMove() Updates current board based on input
     */
    void registerMove( std::string move );
private:


    /*
     * kingIsSafe(), check if provided move places own king in check
     */
    bool kingIsSafe( std::string move );
    /*
     * generatePawnMoves()
     */
    std::vector< std::string > generatePawnMoves( int column, int row, bool onlyCaptures );
    /*
     * generateKnightMoves()
     */
    std::vector< std::string > generateKnightMoves( int column, int row, bool onlyCaptures );
    /*
     * generateBishopMoves()
     */
    std::vector< std::string > generateBishopMoves( int column, int row, bool onlyCaptures );
    /*
     * generateRookMoves()
     */
    std::vector< std::string > generateRookMoves( int column, int row, bool onlyCaptures );
    /*
     * generateQueenMoves()
     */
    std::vector< std::string > generateQueenMoves( int column, int row, bool onlyCaptures );
    /*
     * generateKingMoves()
     */
    std::vector< std::string > generateKingMoves( int column, int row, bool onlyCaptures );

    /* Helper functions */
    /*
     * getPieceAt(), Returns value at pos provided as arg
     */
    char getPieceAt( std::string );
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

    std::array< std::array< char, BOARD_WIDTH >, BOARD_HEIGHT > currentBoard;
};

#endif
