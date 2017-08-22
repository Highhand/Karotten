#include "MoveGenerator.h"
#include <iostream>

MoveGenerator::MoveGenerator() {
    // std::cout << "Created MoveGenerator" << std::endl;
}

MoveGenerator::~MoveGenerator() {
    // std::cout << "Destroyed MoveGenerator" << std::endl;
}

std::vector< std::string > MoveGenerator::generateMoves( Board& board, bool white ) {
    std::vector< std::string > moves;
    for ( int row = 0; row < Board::HEIGHT; row++ ) {
        for ( int column = 0; column < Board::WIDTH; column++ ) {
            char piece = board.getPieceAt(column, row);
            // Skip empty spots and if white skip black and if black skip white pieces
            if ( piece == 0 || (white && piece < 0) || (!white && piece > 0) ) continue;
            std::vector< std::string > newMoves;
            switch ( piece ) {
                case -1:
                case 1:
                    newMoves = this->generatePawnMoves(board, column, row, false);
                    break;
                case -2:
                case 2:
                    newMoves = this->generateKnightMoves(board, column, row, false);
                    break;
                case -3:
                case 3:
                    newMoves = this->generateBishopMoves(board, column, row, false);
                    break;
                case -4:
                case 4:
                    newMoves = this->generateRookMoves(board, column, row, false);
                    break;
                case -5:
                case 5:
                    newMoves = this->generateQueenMoves(board, column, row, false);
                    break;
                case -6:
                case 6:
                    newMoves = this->generateKingMoves(board, column, row, false);
                    break;
                default:
                    break;
            }
            if ( newMoves.empty() ) continue;
            // Add new moves
            moves.insert( moves.end(), newMoves.begin(), newMoves.end() );
        }
    }
    return moves;
}

std::vector< std::string > MoveGenerator::generatePawnMoves( Board& board, int column, int row, bool onlyCaptures ) {
    std::vector< std::string > moves;
    std::string move = board.positionToString( column, row );
    bool isWhite = board.getPieceAt(column, row) > 0;
    int nextColumn, nextRow;
    // If white then first move when pawn at row #2
    // If black then first move when pawn at row #7
    bool isFirstMove = isWhite ? row == 1 : row == 6;
    // If white inc (+), if black move dec (-)
    int forwardStep = isWhite ? 1 : -1;
    nextRow = row + forwardStep;
    // Check capture left
    nextColumn = column -1;
    if ( board.isCapture( nextColumn, nextRow , isWhite ) ) {
        moves.push_back( move + board.positionToString( nextColumn, nextRow ) );
    }
    // Check capture right
    nextColumn = column +1;
    if ( board.isCapture( nextColumn, nextRow, isWhite ) ) {
        moves.push_back( move + board.positionToString( nextColumn, nextRow ) );
    }
    // Check if free
    nextColumn = column;
    if ( board.isFree( nextColumn, nextRow ) && !onlyCaptures ) {
        moves.push_back( move + board.positionToString( nextColumn, nextRow ) );
        // If first movement possible to move 2 steps
        nextRow += forwardStep;
        if ( isFirstMove && board.isFree( nextColumn, nextRow ) ) {
            moves.push_back( move + board.positionToString( nextColumn, nextRow ) );
        }
    }
    // TODO: Check promotion
    // TODO: En passant
    return moves;
}

std::vector< std::string > MoveGenerator::generateKnightMoves( Board& board, int column, int row, bool onlyCaptures ) {
    std::vector< std::string > moves;
    bool isWhite = board.getPieceAt(column, row) > 0;
    std::string move = board.positionToString( column, row );
    int nextColumn, nextRow, columnStep;

    for ( int rowStep = -2; rowStep <= 2; rowStep++ ) {
        if (rowStep == 0) continue;
        nextRow = row +rowStep;
        columnStep  = 3 -abs(rowStep);
        // left
        nextColumn = column -columnStep;
        if ( board.isCapture( nextColumn, nextRow, isWhite ) ) {
            moves.push_back( move + board.positionToString( nextColumn, nextRow ) );
        }
        else if ( !onlyCaptures && board.isFree( nextColumn, nextRow ) ) {
            moves.push_back( move + board.positionToString( nextColumn, nextRow ) );
        }
        // right
        nextColumn = column +columnStep;
        if ( board.isCapture( nextColumn, nextRow, isWhite ) ) {
            moves.push_back( move + board.positionToString( nextColumn, nextRow ) );
        }
        else if ( !onlyCaptures && board.isFree( nextColumn, nextRow ) ) {
            moves.push_back( move + board.positionToString( nextColumn, nextRow ) );
        }
    }
    return moves;
}

std::vector< std::string > MoveGenerator::generateBishopMoves( Board& board, int column, int row, bool onlyCaptures ) {
    std::vector< std::string > moves;
    bool isWhite = board.getPieceAt(column, row) > 0;
    std::string move = board.positionToString( column, row );
    int nextColumn, nextRow;

    for ( int rowStep = -1; rowStep <= 1; rowStep += 2 ) {
        for ( int columnStep = -1; columnStep <= 1; columnStep += 2 ) {
            nextColumn = column + columnStep;
            nextRow = row + rowStep;
            while ( board.isValidPos( nextColumn, nextRow ) ) {
                // If free
                if ( board.isFree(nextColumn, nextRow) ) {
                    if ( !onlyCaptures ) {
                        moves.push_back( move + board.positionToString( nextColumn, nextRow ) );
                    }
                }
                else {
                    // If occupied by enemy add to list
                    if ( board.isCapture(nextColumn, nextRow, isWhite) ) {
                        moves.push_back( move + board.positionToString( nextColumn, nextRow ) );
                    }
                    break;
                }
                nextColumn += columnStep;
                nextRow += rowStep;
            }
        }
    }
    return moves;
}

std::vector< std::string > MoveGenerator::generateRookMoves( Board& board, int column, int row, bool onlyCaptures ) {
    std::vector< std::string > moves;
    bool isWhite = board.getPieceAt(column, row) > 0;
    std::string move = board.positionToString( column, row );
    int nextColumn, nextRow;

    // Up and down
    for (int rowStep = -1; rowStep <= 1; rowStep += 2 ) {
        nextColumn = column;
        nextRow = row +rowStep;
        while ( board.isValidRow(nextRow) ) {
            // If free
            if ( board.isFree(nextColumn, nextRow) ) {
                if ( !onlyCaptures ) {
                    moves.push_back( move + board.positionToString( nextColumn, nextRow ) );
                }
            }
            else {
                // If occupied by enemy add to list
                if ( board.isCapture(nextColumn, nextRow, isWhite) ) {
                    moves.push_back( move + board.positionToString( nextColumn, nextRow ) );
                }
                break;
            }
            nextRow += rowStep;
        }
    }
    // Left and right
    for (int columnStep = -1; columnStep <= 1; columnStep += 2 ) {
        nextColumn = column +columnStep;
        nextRow = row ;
        while ( board.isValidColumn(nextColumn) ) {
            // If free
            if ( board.isFree(nextColumn, nextRow) ) {
                if ( !onlyCaptures ) {
                    moves.push_back( move + board.positionToString( nextColumn, nextRow ) );
                }
            }
            else {
                // If occupied by enemy add to list
                if ( board.isCapture(nextColumn, nextRow, isWhite) ) {
                    moves.push_back( move + board.positionToString( nextColumn, nextRow ) );
                }
                break;
            }
            nextColumn += columnStep;
        }
    }
    return moves;
}

std::vector< std::string > MoveGenerator::generateQueenMoves( Board& board, int column, int row, bool onlyCaptures ) {
    std::vector< std::string > moves;
    bool isWhite = board.getPieceAt(column, row) > 0;
    moves = this->generateBishopMoves( board, column, row, onlyCaptures );
    std::vector< std::string > rookMoves = this->generateRookMoves( board, column, row, onlyCaptures );
    moves.insert( moves.end(), rookMoves.begin(), rookMoves.end() );
    return moves;
}

std::vector< std::string > MoveGenerator::generateKingMoves( Board& board, int column, int row, bool onlyCaptures ) {
    std::vector< std::string > moves;
    bool isWhite = board.getPieceAt(column, row) > 0;
    std::string move = board.positionToString( column, row );
    // Check the 8 squares around King
    for ( int nextRow = row-1; nextRow <= row+1; nextRow++ ) {
        // Skip out of bounds row
        if ( !board.isValidRow(nextRow) ) continue;
        for ( int nextColumn = column-1; nextColumn <= column+1; nextColumn++ ) {
            // Skip out of bounds column and current pos
            if ( !board.isValidColumn(nextColumn) || (nextRow == row && nextColumn == column) ) continue;
            // Free
            if ( !onlyCaptures && board.isFree( nextColumn, nextRow ) ) {
                moves.push_back( move + board.positionToString( nextColumn, nextRow ) );
            }
            // Capture for white
            else if ( board.isCapture( nextColumn, nextRow, isWhite ) ) {
                moves.push_back( move + board.positionToString( nextColumn, nextRow ) );
            }
        }
    }
    // TODO: Check castling
    return moves;
}
