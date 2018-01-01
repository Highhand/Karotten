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
    int Perft(int depth, Board board, bool white_turn);

    /*
     * GenerateMoves(). Generate all possible pseudo-legal moves for provided color.
     * (Pseudo-legal as in moves that can place your own king in check and are therefore not legal)
     */
    std::vector<std::string> GenerateMoves(Board& board, bool white);
    /*
     * GeneratePawnMoves()
     */
    std::vector<std::string> GeneratePawnMoves(Board& board, int column, int row);
    /*
     * GenerateKnightMoves()
     */
    std::vector<std::string> GenerateKnightMoves(Board& board, int column, int row);
    /*
     * GenerateBishopMoves()
     */
    std::vector<std::string> GenerateBishopMoves(Board& board, int column, int row);
    /*
     * GenerateRookMoves()
     */
    std::vector<std::string> GenerateRookMoves(Board& board, int column, int row);
    /*
     * GenerateQueenMoves()
     */
    std::vector<std::string> GenerateQueenMoves(Board& board, int column, int row);
    /*
     * GenerateKingMoves()
     */
    std::vector<std::string> GenerateKingMoves(Board& board, int column, int row);
  private:
      /*
       * kingIsSafe(). Controls that a move will not place your own king in check.
       * If the king can capture the piece then the piece can also capture the king
       * i.e. the king is checked. Returns false as soon as one instance of these
       * kind of moves and piece combination is found.
       */
      bool KingIsSafe(Board& board, std::string move);
};

#endif
