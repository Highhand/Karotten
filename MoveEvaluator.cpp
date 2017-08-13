#include "MoveEvaluator.h"
#include <iostream>

MoveEvaluator::MoveEvaluator() {
    std::cout << "Created MoveEvaluator" << std::endl;
}

MoveEvaluator::~MoveEvaluator() {
    std::cout << "Destroyed MoveEvaluator" << std::endl;
}

bool MoveEvaluator::kingIsSafe( Board& board, MoveGenerator& moveGen, std::string move ) {
    std::vector< std::string > moves;
    std::string from = move.substr(0,2);
    std::string to = move.substr(2,2);
    bool isWhite = board.getPieceAt(from) > 0;
    int colorModifier = isWhite ? 1 : -1;
    int kingColumn, kingRow;
    int oldPiece = board.getPieceAt(to);
    int columnTo = board.columnToInt(to.at(0));
    int rowTo = board.rowToInt(to.at(1));
    // make move
    board.makeMove( move );
    // gen all diff moves for King
    for ( int row = 0; row < BOARD_HEIGHT; row++ ) {
        for ( int column = 0; column < BOARD_WIDTH; column++ ) {
            if ( board.getPieceAt(column, row) == 6*colorModifier ) {
                kingColumn = column;
                kingRow = row;
            }
        }
    }
    // knight
    moves = moveGen.generateKnightMoves( board, kingColumn, kingRow, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opposing colors piece
        if (board.getPieceAt(moves[i].substr(2,2)) == 2*colorModifier*-1 ) {
            board.makeMove( to + from );
            board.setPieceAt(columnTo, rowTo, oldPiece);
            // std::cout << "King threatend by piece at: " << moves.at(i).substr(2,2) << std::endl;
            return false;
        }
    }
    // Rook or Queen
    moves = moveGen.generateRookMoves( board, kingColumn, kingRow, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opposing colors piece
        int piece =board.getPieceAt(moves[i].substr(2,2));
        if ( piece == 4*colorModifier*-1 || piece == 5*colorModifier*-1 ) {
            board.makeMove( to + from );
            board.setPieceAt(columnTo, rowTo, oldPiece);
            // std::cout << "King threatend by piece at: " << moves.at(i).substr(2,2) << std::endl;
            return false;
        }
    }
    // Bishop or Queen
    moves = moveGen.generateBishopMoves( board, kingColumn, kingRow, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opposing colors piece
        int piece =board.getPieceAt(moves[i].substr(2,2));
        if ( piece == 3*colorModifier*-1 || piece == 5*colorModifier*-1 ) {
            board.makeMove( to + from );
            board.setPieceAt(columnTo, rowTo, oldPiece);
            // std::cout << "King threatend by piece at: " << moves.at(i).substr(2,2) << std::endl;
            return false;
        }
    }
    // Pawn
    moves = moveGen.generatePawnMoves( board, kingColumn, kingRow, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opposing colors pawn
        if (board.getPieceAt(moves[i].substr(2,2)) == 1*colorModifier*-1 ) {
            board.makeMove( to + from );
            board.setPieceAt(columnTo, rowTo, oldPiece);
            // std::cout << "King threatend by piece at: " << moves.at(i).substr(2,2) << std::endl;
            return false;
        }
    }
    // King
    moves = moveGen.generateKingMoves( board, kingColumn, kingRow, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opposing colors piece
        if (board.getPieceAt(moves[i].substr(2,2)) == 6*colorModifier*-1 ) {
            board.makeMove( to + from );
            board.setPieceAt(columnTo, rowTo, oldPiece);
            // std::cout << "King threatend by piece at: " << moves.at(i).substr(2,2) << std::endl;
            return false;
        }
    }
    board.makeMove( to + from );
    board.setPieceAt(columnTo, rowTo, oldPiece);
    return true;
}
