#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include "Board.h"

class MoveGenerator {
  public:
    MoveGenerator();
    ~MoveGenerator();

    /*
     * perft(). Generates all moves to given depth
     */
    int Perft(int depth, Board board);

    /*
     * GenerateMoves(). Generate all possible pseudo-legal moves for provided color.
     * (Pseudo-legal as in moves that can place your own king in check and are therefore not legal)
     */
    std::vector< std::string > GenerateMoves( Board& board, bool white );
    /*
     * GeneratePawnMoves()
     */
    std::vector< std::string > GeneratePawnMoves( Board& board, int column, int row, bool only_captures );
    /*
     * GenerateKnightMoves()
     */
    std::vector< std::string > GenerateKnightMoves( Board& board, int column, int row, bool only_captures );
    /*
     * GenerateBishopMoves()
     */
    std::vector< std::string > GenerateBishopMoves( Board& board, int column, int row, bool only_captures );
    /*
     * GenerateRookMoves()
     */
    std::vector< std::string > GenerateRookMoves( Board& board, int column, int row, bool only_captures );
    /*
     * GenerateQueenMoves()
     */
    std::vector< std::string > GenerateQueenMoves( Board& board, int column, int row, bool only_captures );
    /*
     * GenerateKingMoves()
     */
    std::vector< std::string > GenerateKingMoves( Board& board, int column, int row, bool only_captures );
  private:
};

#endif
