#include "MoveEvaluator.h"
#include <algorithm> // min, max
#include <iostream>
#include <limits> // <int> max, <int> min

MoveEvaluator::MoveEvaluator() {
    std::cout << "Created MoveEvaluator" << std::endl;
}

MoveEvaluator::~MoveEvaluator() {
    std::cout << "Destroyed MoveEvaluator" << std::endl;
}

std::pair< std::string, int > MoveEvaluator::alphaBeta( int depth, int alpha, int beta, bool maximizingPlayer, Board& board) {
    // Base case
    if ( depth == 0 ) {
        return std::make_pair(board.getLastMove(), this->evaluateBoard(board) );
    }
    std::pair<std::string, int> bestMove;
    int numOfChildren;
    std::cout << "Number of children: ";
    std::cin >> numOfChildren;
    // TODO: Generate moves
    if ( maximizingPlayer ) {
        bestMove.first = "";
        bestMove.second = std::numeric_limits<int>::min();
        for ( int i = 0; i < numOfChildren; i++ ) {
            // TODO: Make move
            // Call alphaBeta with new child-boardstate
            std::pair< std::string, int > newMove = this->alphaBeta(depth-1, alpha, beta, false, board);
            // TODO: Undo move to return to parent-boardstate
            // If new move is better (higher score) then previously best move update best move
            if ( bestMove.second < newMove.second ) {
                bestMove = newMove;
            }
            // Update lower bound
            alpha = std::max(alpha, bestMove.second);
            // Moves FROM this boardstate will only result in a value greater than alpha and the previous
            // boardstate have moves that will result in a value less than beta. Therefore if
            // alpha is greater than beta this boardstate will not be chosen and we can ignore its
            // remaining children.
            if ( beta <= alpha ) break;
        }
        return bestMove;
    } else {
        bestMove.first = "";
        bestMove.second = std::numeric_limits<int>::max();
        for ( int i = 0; i < numOfChildren; i++ ) {
            // TODO: Make move
            // Call alphaBeta with new child-boardstate
            std::pair< std::string, int > newMove = this->alphaBeta(depth-1, alpha, beta, true, board);
            // TODO: Undo move to return to parent-boardstate
            // If new move is better (lower score) then previously best move update best move
            if ( bestMove.second > newMove.second ) {
                bestMove = newMove;
            }
            // Update upper bound
            beta = std::min(beta, bestMove.second);
            // Moves FROM this boardstate will only result in a value less than beta and the previous
            // boardstate have moves that will result in a value greater than alpha. Therefore if
            // beta is less than alpha this boardstate will not be chosen and we can ignore its
            // remaining children.
            if ( beta <= alpha ) break;
        }
        return bestMove;
    }
}

int MoveEvaluator::evaluateBoard( Board& board ) {
    int score;
    std::cout << "Node score: ";
    std::cin >> score;
    return score;
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
