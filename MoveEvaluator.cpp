#include "MoveEvaluator.h"
#include <algorithm> // min, max
#include <iostream>
#include <limits> // <int> max, <int> min
#include <vector>

MoveEvaluator::MoveEvaluator() {
    // std::cout << "Created MoveEvaluator" << std::endl;
}

MoveEvaluator::~MoveEvaluator() {
    // std::cout << "Destroyed MoveEvaluator" << std::endl;
}

std::pair< std::string, int > MoveEvaluator::findBestMove( Board& board, bool whiteTurn ) {
    return this->alphaBeta(4, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), whiteTurn, board);
}

std::pair< std::string, int > MoveEvaluator::alphaBeta(int depth, int alpha, int beta, bool maximizingPlayer, Board& board) {
    // Base case
    if ( depth == 0 ) {
        return std::make_pair(board.getLastMove(), this->evaluateBoard(board) );
    }
    // Generate moves
    std::vector< std::string > moves = moveGen.generateMoves(board, maximizingPlayer);
    // TODO: Sort moves
    // Remove moves that places own king in check
    for ( int i = 0; i < moves.size(); i++ ) {
        if ( !this->kingIsSafe(board, this->moveGen, moves.at(i)) ) {
            moves.erase(moves.begin()+i);
            i--;
        }
    }
    std::pair<std::string, int> bestMove;
    if ( maximizingPlayer ) {
        bestMove.first = "";
        bestMove.second = std::numeric_limits<int>::min();
        for ( int i = 0; i < moves.size(); i++ ) {
            // Make move
            int capturedPiece = board.makeMove(moves.at(i));
            // Call alphaBeta with new child-boardstate
            std::pair< std::string, int > newMove = this->alphaBeta(depth-1, alpha, beta, false, board);
            // Undo move to return to parent-boardstate
            board.undoMove(moves.at(i), capturedPiece);
            // If new move is better (higher score) then previously best moves score update best move
            if ( bestMove.second < newMove.second ) {
                bestMove.first = moves.at(i); // New optimal move
                bestMove.second = newMove.second; // New score for move
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
        for ( int i = 0; i < moves.size(); i++ ) {
            // Make move
            int capturedPiece = board.makeMove(moves.at(i));
            // Call alphaBeta with new child-boardstate
            std::pair< std::string, int > newMove = this->alphaBeta(depth-1, alpha, beta, true, board);
            // Undo move to return to parent-boardstate
            board.undoMove(moves.at(i), capturedPiece);
            // If new move is better (lower score) then previously best move update best move
            if ( bestMove.second > newMove.second ) {
                bestMove.first = moves.at(i); // New optimal move
                bestMove.second = newMove.second; // New score for move
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
    int score = 0;
    for ( int row = 0; row < Board::HEIGHT; row++ ) {
        for ( int column = 0; column < Board::WIDTH; column++ ) {
            score += board.getPieceAt(column, row);
        }
    }
    return score;
}

bool MoveEvaluator::kingIsSafe( Board& board, MoveGenerator& moveGen, std::string move ) {
    std::vector< std::string > moves;
    bool isWhite = board.getPieceAt(move.substr(0,2)) > 0;
    int colorModifier = isWhite ? 1 : -1;
    int kingColumn, kingRow;
    // make move
    int oldPiece = board.makeMove( move );
    // Find the Kings position
    for ( int row = 0; row < Board::HEIGHT; row++ ) {
        for ( int column = 0; column < Board::WIDTH; column++ ) {
            if ( board.getPieceAt(column, row) == 6*colorModifier ) {
                kingColumn = column;
                kingRow = row;
            }
        }
    }
    // Generate Knight moves
    moves = moveGen.generateKnightMoves( board, kingColumn, kingRow, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opponents Knight can be captured from Kings position
        if (board.getPieceAt(moves[i].substr(2,2)) == 2*colorModifier*-1 ) {
            board.undoMove( move, oldPiece );
            return false;
        }
    }
    // Generate Rook moves
    moves = moveGen.generateRookMoves( board, kingColumn, kingRow, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opponents Rook or Queen can be captured from Kings position
        int piece =board.getPieceAt(moves[i].substr(2,2));
        if ( piece == 4*colorModifier*-1 || piece == 5*colorModifier*-1 ) {
            board.undoMove( move, oldPiece );
            return false;
        }
    }
    // Generate Bishop moves
    moves = moveGen.generateBishopMoves( board, kingColumn, kingRow, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opponents Bishop or Queen can be captured from Kings position
        int piece = board.getPieceAt(moves[i].substr(2,2));
        if ( piece == 3*colorModifier*-1 || piece == 5*colorModifier*-1 ) {
            board.undoMove( move, oldPiece );
            return false;
        }
    }
    // Generate Pawn moves
    moves = moveGen.generatePawnMoves( board, kingColumn, kingRow, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opponents Pawn can be captured from Kings position
        if (board.getPieceAt(moves[i].substr(2,2)) == 1*colorModifier*-1 ) {
            board.undoMove( move, oldPiece );
            return false;
        }
    }
    // Generate King moves
    moves = moveGen.generateKingMoves( board, kingColumn, kingRow, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opponents King can be captured from Kings position
        if (board.getPieceAt(moves[i].substr(2,2)) == 6*colorModifier*-1 ) {
            board.undoMove( move, oldPiece );
            return false;
        }
    }
    board.undoMove( move, oldPiece );
    return true;
}
