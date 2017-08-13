#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include "Board.h"

class MoveGenerator {
public:
    MoveGenerator();
    ~MoveGenerator();

    /*
     * generateMoves()
     */
    std::vector< std::string > generateMoves( Board& board, bool white );
    /*
     * generatePawnMoves()
     */
    std::vector< std::string > generatePawnMoves( Board& board, int column, int row, bool onlyCaptures );
    /*
     * generateKnightMoves()
     */
    std::vector< std::string > generateKnightMoves( Board& board, int column, int row, bool onlyCaptures );
    /*
     * generateBishopMoves()
     */
    std::vector< std::string > generateBishopMoves( Board& board, int column, int row, bool onlyCaptures );
    /*
     * generateRookMoves()
     */
    std::vector< std::string > generateRookMoves( Board& board, int column, int row, bool onlyCaptures );
    /*
     * generateQueenMoves()
     */
    std::vector< std::string > generateQueenMoves( Board& board, int column, int row, bool onlyCaptures );
    /*
     * generateKingMoves()
     */
    std::vector< std::string > generateKingMoves( Board& board, int column, int row, bool onlyCaptures );

private:

};

#endif
