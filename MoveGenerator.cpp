#include "MoveGenerator.h"
#include <iostream>

MoveGenerator::MoveGenerator() {
    // std::cout << "Created MoveGenerator" << std::endl;
}

MoveGenerator::~MoveGenerator() {
    // std::cout << "Destroyed MoveGenerator" << std::endl;
}

int MoveGenerator::Perft(int depth, Board board) {
  std::vector<std::string> moves;
  int total_nodes = 0;
  if (depth == 0) {
    return 1;
  }
  moves = GenerateMoves(board, true);
  for (size_t i = 0; i < moves.size(); i++) {
    std::cout << moves[i] << ": ";
    char captured_piece = board.MakeMove(moves[i]);
    int nodes = Perft(depth-1, board);
    total_nodes += nodes;
    board.UndoMove(moves[i], captured_piece);
  }
  return total_nodes;
}

std::vector< std::string > MoveGenerator::GenerateMoves( Board& board, bool white ) {
    std::vector< std::string > moves;
    for ( int row = 0; row < Board::HEIGHT; row++ ) {
        for ( int column = 0; column < Board::WIDTH; column++ ) {
            char piece = board.GetPieceAt(column, row);
            // Skip empty spots and if white skip black and if black skip white pieces
            if ( piece == 0 || (white && piece < 0) || (!white && piece > 0) ) continue;
            std::vector< std::string > new_moves;
            switch ( piece ) {
                case -1:
                case 1:
                    new_moves = GeneratePawnMoves(board, column, row, false);
                    break;
                case -2:
                case 2:
                    new_moves = GenerateKnightMoves(board, column, row, false);
                    break;
                case -3:
                case 3:
                    new_moves = GenerateBishopMoves(board, column, row, false);
                    break;
                case -4:
                case 4:
                    new_moves = GenerateRookMoves(board, column, row, false);
                    break;
                case -5:
                case 5:
                    new_moves = GenerateQueenMoves(board, column, row, false);
                    break;
                case -6:
                case 6:
                    new_moves = GenerateKingMoves(board, column, row, false);
                    break;
                default:
                    break;
            }
            if ( new_moves.empty() ) continue;
            // Add new moves
            moves.insert( moves.end(), new_moves.begin(), new_moves.end() );
        }
    }
    return moves;
}

std::vector< std::string > MoveGenerator::GeneratePawnMoves( Board& board, int column, int row, bool only_captures ) {
    std::vector< std::string > moves;
    std::string move = board.PositionToString( column, row );
    bool is_white = board.GetPieceAt(column, row) > 0;
    int next_column, next_row;
    // If white then first move when pawn at row #2
    // If black then first move when pawn at row #7
    bool is_first_move = is_white ? row == 1 : row == 6;
    // If white inc (+), if black move dec (-)
    int forward_step = is_white ? 1 : -1;
    next_row = row + forward_step;
    // Check capture left
    next_column = column -1;
    if ( board.IsCapture( next_column, next_row , is_white ) ) {
        moves.push_back( move + board.PositionToString( next_column, next_row ) );
    }
    // Check capture right
    next_column = column +1;
    if ( board.IsCapture( next_column, next_row, is_white ) ) {
        moves.push_back( move + board.PositionToString( next_column, next_row ) );
    }
    // Check if free
    next_column = column;
    if ( board.IsFree( next_column, next_row ) && !only_captures ) {
        moves.push_back( move + board.PositionToString( next_column, next_row ) );
        // If first movement possible to move 2 steps
        next_row += forward_step;
        if ( is_first_move && board.IsFree( next_column, next_row ) ) {
            moves.push_back( move + board.PositionToString( next_column, next_row ) );
        }
    }
    // TODO: Check promotion
    // TODO: En passant
    return moves;
}

std::vector< std::string > MoveGenerator::GenerateKnightMoves( Board& board, int column, int row, bool only_captures ) {
    std::vector< std::string > moves;
    bool is_white = board.GetPieceAt(column, row) > 0;
    std::string move = board.PositionToString( column, row );
    int next_column, next_row, column_step;

    for ( int row_step = -2; row_step <= 2; row_step++ ) {
        if (row_step == 0) continue;
        next_row = row +row_step;
        column_step  = 3 -abs(row_step);
        // left
        next_column = column -column_step;
        if ( board.IsCapture( next_column, next_row, is_white ) ) {
            moves.push_back( move + board.PositionToString( next_column, next_row ) );
        }
        else if ( !only_captures && board.IsFree( next_column, next_row ) ) {
            moves.push_back( move + board.PositionToString( next_column, next_row ) );
        }
        // right
        next_column = column +column_step;
        if ( board.IsCapture( next_column, next_row, is_white ) ) {
            moves.push_back( move + board.PositionToString( next_column, next_row ) );
        }
        else if ( !only_captures && board.IsFree( next_column, next_row ) ) {
            moves.push_back( move + board.PositionToString( next_column, next_row ) );
        }
    }
    return moves;
}

std::vector< std::string > MoveGenerator::GenerateBishopMoves( Board& board, int column, int row, bool only_captures ) {
    std::vector< std::string > moves;
    bool is_white = board.GetPieceAt(column, row) > 0;
    std::string move = board.PositionToString( column, row );
    int next_column, next_row;

    for ( int row_step = -1; row_step <= 1; row_step += 2 ) {
        for ( int column_step = -1; column_step <= 1; column_step += 2 ) {
            next_column = column + column_step;
            next_row = row + row_step;
            while ( board.IsValidPos( next_column, next_row ) ) {
                // If free
                if ( board.IsFree(next_column, next_row) ) {
                    if ( !only_captures ) {
                        moves.push_back( move + board.PositionToString( next_column, next_row ) );
                    }
                }
                else {
                    // If occupied by enemy add to list
                    if ( board.IsCapture(next_column, next_row, is_white) ) {
                        moves.push_back( move + board.PositionToString( next_column, next_row ) );
                    }
                    break;
                }
                next_column += column_step;
                next_row += row_step;
            }
        }
    }
    return moves;
}

std::vector< std::string > MoveGenerator::GenerateRookMoves( Board& board, int column, int row, bool only_captures ) {
    std::vector< std::string > moves;
    bool is_white = board.GetPieceAt(column, row) > 0;
    std::string move = board.PositionToString( column, row );
    int next_column, next_row;

    // Up and down
    for (int row_step = -1; row_step <= 1; row_step += 2 ) {
        next_column = column;
        next_row = row +row_step;
        while ( board.IsValidRow(next_row) ) {
            // If free
            if ( board.IsFree(next_column, next_row) ) {
                if ( !only_captures ) {
                    moves.push_back( move + board.PositionToString( next_column, next_row ) );
                }
            }
            else {
                // If occupied by enemy add to list
                if ( board.IsCapture(next_column, next_row, is_white) ) {
                    moves.push_back( move + board.PositionToString( next_column, next_row ) );
                }
                break;
            }
            next_row += row_step;
        }
    }
    // Left and right
    for (int column_step = -1; column_step <= 1; column_step += 2 ) {
        next_column = column +column_step;
        next_row = row ;
        while ( board.IsValidColumn(next_column) ) {
            // If free
            if ( board.IsFree(next_column, next_row) ) {
                if ( !only_captures ) {
                    moves.push_back( move + board.PositionToString( next_column, next_row ) );
                }
            }
            else {
                // If occupied by enemy add to list
                if ( board.IsCapture(next_column, next_row, is_white) ) {
                    moves.push_back( move + board.PositionToString( next_column, next_row ) );
                }
                break;
            }
            next_column += column_step;
        }
    }
    return moves;
}

std::vector< std::string > MoveGenerator::GenerateQueenMoves( Board& board, int column, int row, bool only_captures ) {
    std::vector< std::string > moves;
    bool is_white = board.GetPieceAt(column, row) > 0;
    moves = GenerateBishopMoves( board, column, row, only_captures );
    std::vector< std::string > rookMoves = GenerateRookMoves( board, column, row, only_captures );
    moves.insert( moves.end(), rookMoves.begin(), rookMoves.end() );
    return moves;
}

std::vector< std::string > MoveGenerator::GenerateKingMoves( Board& board, int column, int row, bool only_captures ) {
    std::vector< std::string > moves;
    bool is_white = board.GetPieceAt(column, row) > 0;
    std::string move = board.PositionToString( column, row );
    // Check the 8 squares around King
    for ( int next_row = row-1; next_row <= row+1; next_row++ ) {
        // Skip out of bounds row
        if ( !board.IsValidRow(next_row) ) continue;
        for ( int next_column = column-1; next_column <= column+1; next_column++ ) {
            // Skip out of bounds column and current pos
            if ( !board.IsValidColumn(next_column) || (next_row == row && next_column == column) ) continue;
            // Free
            if ( !only_captures && board.IsFree( next_column, next_row ) ) {
                moves.push_back( move + board.PositionToString( next_column, next_row ) );
            }
            // Capture for white
            else if ( board.IsCapture( next_column, next_row, is_white ) ) {
                moves.push_back( move + board.PositionToString( next_column, next_row ) );
            }
        }
    }
    // TODO: Check castling
    return moves;
}
