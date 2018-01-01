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

    std::pair<std::string, int> best_move;
    if ( maximizing_player ) {
        best_move.first = "";
        best_move.second = std::numeric_limits<int>::min();
        for ( size_t i = 0; i < moves.size(); i++ ) {
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
        for ( size_t i = 0; i < moves.size(); i++ ) {
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
