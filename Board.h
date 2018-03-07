#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <string>
#include <vector>

class Board {
public:
    Board();

    static const int WIDTH = 8;
    static const int HEIGHT = 8;

    std::array<std::array<char, WIDTH>, HEIGHT> GetCurrentBoard();
    /*
     * GetPieceAt(). Returns piece at given position. If invalid position
     * return 0.
     */
    char GetPieceAt(std::string);
    char GetPieceAt(int column, int row);

    void SetPieceAt(std::string, char piece);
    void SetPieceAt(int column, int row, char piece);

    std::string GetLastMove();
    /*
     * MakeMove() Updates current board based on input and returns captured piece
     */
    char MakeMove(std::string move);
    /*
     * UndoMove() Updates current board based on input
     */
    void UndoMove(std::string move, char captured_piece);
    /*
     * PrintBoard()
     */
    void PrintBoard();
    /*
     * ResetBoard() ReSets current board
     */
    void ResetBoard();
    /*
     * Converts a position to a string in UCI-format i.e. (3,3) -> "d4"
     */
    std::string PositionToString(int column, int row);

    int ColumnToInt(char);
    int RowToInt(char);

    bool IsValidColumn(int);
    bool IsValidRow(int);
    bool IsValidPos(int column, int row);

    bool IsCapture(int column, int row, bool isWhite);
    bool IsFree(int column, int row);
private:
    std::array< std::array< char, WIDTH >, HEIGHT > current_board;
    // Hold the last valid move sent to MakeMove(). UndoMove() does not affect this var.
    std::string last_move{""};
};

#endif
