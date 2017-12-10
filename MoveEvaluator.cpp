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

std::pair< std::string, int > MoveEvaluator::FindBestMove( Board& board, bool white_turn ) {
    return AlphaBeta(4, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), white_turn, board);
}

std::pair< std::string, int > MoveEvaluator::AlphaBeta(int depth, int alpha, int beta, bool maximizing_player, Board& board) {
    // Base case
    if ( depth == 0 ) {
        return std::make_pair(board.GetLastMove(), EvaluateBoard(board) );
    }
    // Generate moves
    std::vector< std::string > moves = move_generator.GenerateMoves(board, maximizing_player);
    // TODO: Sort moves
    // Remove moves that places own king in check
    for ( int i = 0; i < moves.size(); i++ ) {
        if ( !KingIsSafe(board, move_generator, moves.at(i)) ) {
            moves.erase(moves.begin()+i);
            i--;
        }
    }
    std::pair<std::string, int> best_move;
    if ( maximizing_player ) {
        best_move.first = "";
        best_move.second = std::numeric_limits<int>::min();
        for ( int i = 0; i < moves.size(); i++ ) {
            // Make move
            int captured_piece = board.MakeMove(moves.at(i));
            // Call AlphaBeta with new child-boardstate
            std::pair< std::string, int > new_move = AlphaBeta(depth-1, alpha, beta, false, board);
            // Undo move to return to parent-boardstate
            board.UndoMove(moves.at(i), captured_piece);
            // If new move is better (higher score) then previously best moves score update best move
            if ( best_move.second < new_move.second ) {
                best_move.first = moves.at(i); // New optimal move
                best_move.second = new_move.second; // New score for move
            }
            // Update lower bound
            alpha = std::max(alpha, best_move.second);
            // Moves FROM this boardstate will only result in a value greater than alpha and the previous
            // boardstate have moves that will result in a value less than beta. Therefore if
            // alpha is greater than beta this boardstate will not be chosen and we can ignore its
            // remaining children.
            if ( beta <= alpha ) break;
        }
        return best_move;
    } else {
        best_move.first = "";
        best_move.second = std::numeric_limits<int>::max();
        for ( int i = 0; i < moves.size(); i++ ) {
            // Make move
            int captured_piece = board.MakeMove(moves.at(i));
            // Call AlphaBeta with new child-boardstate
            std::pair< std::string, int > new_move = AlphaBeta(depth-1, alpha, beta, true, board);
            // Undo move to return to parent-boardstate
            board.UndoMove(moves.at(i), captured_piece);
            // If new move is better (lower score) then previously best move update best move
            if ( best_move.second > new_move.second ) {
                best_move.first = moves.at(i); // New optimal move
                best_move.second = new_move.second; // New score for move
            }
            // Update upper bound
            beta = std::min(beta, best_move.second);
            // Moves FROM this boardstate will only result in a value less than beta and the previous
            // boardstate have moves that will result in a value greater than alpha. Therefore if
            // beta is less than alpha this boardstate will not be chosen and we can ignore its
            // remaining children.
            if ( beta <= alpha ) break;
        }
        return best_move;
    }
}

int MoveEvaluator::EvaluateBoard( Board& board ) {
    int score = 0;
    for ( int row = 0; row < Board::HEIGHT; row++ ) {
        for ( int column = 0; column < Board::WIDTH; column++ ) {
            score += board.GetPieceAt(column, row);
        }
    }
    return score;
}

bool MoveEvaluator::KingIsSafe( Board& board, MoveGenerator& move_generator, std::string move ) {
    std::vector< std::string > moves;
    bool is_white = board.GetPieceAt(move.substr(0,2)) > 0;
    int color_modifier = is_white ? 1 : -1;
    int king_column, king_row;
    // make move
    int old_piece = board.MakeMove( move );
    // Find the Kings position
    for ( int row = 0; row < Board::HEIGHT; row++ ) {
        for ( int column = 0; column < Board::WIDTH; column++ ) {
            if ( board.GetPieceAt(column, row) == 6*color_modifier ) {
                king_column = column;
                king_row = row;
            }
        }
    }
    // Generate Knight moves
    moves = move_generator.GenerateKnightMoves( board, king_column, king_row, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opponents Knight can be captured from Kings position
        if (board.GetPieceAt(moves[i].substr(2,2)) == 2*color_modifier*-1 ) {
            board.UndoMove( move, old_piece );
            return false;
        }
    }
    // Generate Rook moves
    moves = move_generator.GenerateRookMoves( board, king_column, king_row, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opponents Rook or Queen can be captured from Kings position
        int piece =board.GetPieceAt(moves[i].substr(2,2));
        if ( piece == 4*color_modifier*-1 || piece == 5*color_modifier*-1 ) {
            board.UndoMove( move, old_piece );
            return false;
        }
    }
    // Generate Bishop moves
    moves = move_generator.GenerateBishopMoves( board, king_column, king_row, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opponents Bishop or Queen can be captured from Kings position
        int piece = board.GetPieceAt(moves[i].substr(2,2));
        if ( piece == 3*color_modifier*-1 || piece == 5*color_modifier*-1 ) {
            board.UndoMove( move, old_piece );
            return false;
        }
    }
    // Generate Pawn moves
    moves = move_generator.GeneratePawnMoves( board, king_column, king_row, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opponents Pawn can be captured from Kings position
        if (board.GetPieceAt(moves[i].substr(2,2)) == 1*color_modifier*-1 ) {
            board.UndoMove( move, old_piece );
            return false;
        }
    }
    // Generate King moves
    moves = move_generator.GenerateKingMoves( board, king_column, king_row, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opponents King can be captured from Kings position
        if (board.GetPieceAt(moves[i].substr(2,2)) == 6*color_modifier*-1 ) {
            board.UndoMove( move, old_piece );
            return false;
        }
    }
    board.UndoMove( move, old_piece );
    return true;
}
