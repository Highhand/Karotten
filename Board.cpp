#include "Board.h"
#include <iostream>

Board::Board() {
    this->currentBoard[0] = { 4, 2, 3, 5, 6, 3, 2, 4 };
    this->currentBoard[1] = { 1, 1, 1, 1, 1, 1, 1, 1 };
    this->currentBoard[2] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    this->currentBoard[3] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    this->currentBoard[4] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    this->currentBoard[5] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    this->currentBoard[6] = { -1, -1, -1, -1, -1, -1, -1, -1 };
    this->currentBoard[7] = { -4, -2, -3, -5, -6, -3, -2, -4 };
}

Board::~Board() {}

std::array< std::array< char, BOARD_WIDTH >, BOARD_HEIGHT > Board::getCurrentBoard() {
    return this->currentBoard;
}

void Board::makeMove() {
    std::vector< std::string > moves;
    for ( int r = 0; r < BOARD_HEIGHT; r++ ) {
        for ( int c = 0; c < BOARD_WIDTH; c++ ) {
            if ( this->currentBoard[r][c] == 6 || this->currentBoard[r][c] == -6 ) {
                moves = generateKingMoves( c, r , false);
                std::cout << positionToString( c, r ) << ": ";
                for (int i = 0; i < moves.size(); i++ ) {
                    std::cout << moves.at(i);
                    if ( this->kingIsSafe( moves.at(i) ) ) {
                        std::cout << " places king in check, ";
                    }
                    else {
                        std::cout << " is safe move, ";
                    }
                }
                std::cout << std::endl;
            }
        }
    }
}

void Board::registerMove( std::string move ) {
    // std::cout << "Registering move: " << move << std::endl;
    if ( move.size() != 4 ) return;
    int columnFrom, rowFrom, columnTo, rowTo;
    columnFrom = this->columnToInt( move.at(0) );
    rowFrom = this->rowToInt( move.at(1) );
    columnTo = this->columnToInt( move.at(2) );
    rowTo = this->rowToInt( move.at(3) );
    // Update board and check if valid pos to avoid segmentation error
    if ( this->isValidPos(columnFrom, rowFrom) && this->isValidPos(columnTo, rowTo) &&
         !this->isFree(columnFrom, rowFrom) )
    {
        this->currentBoard[rowTo][columnTo] = this->currentBoard[rowFrom][columnFrom];
        this->currentBoard[rowFrom][columnFrom] = 0;
    }
    // std::cout << move << " registered ..." << std::endl;
}

bool Board::kingIsSafe( std::string move ) {
    std::vector< std::string > moves;
    std::string from = move.substr(0,2);
    std::string to = move.substr(2,2);
    bool isWhite = this->getPieceAt(from) > 0;
    int colorModifier = isWhite ? 1 : -1;
    int kingColumn, kingRow;
    int oldPiece = this->getPieceAt(to);
    int columnTo = this->columnToInt(to.at(0));
    int rowTo = this->rowToInt(to.at(1));
    // make move
    this->registerMove( move );
    // gen all diff moves for King
    for ( int row = 0; row < BOARD_HEIGHT; row++ ) {
        for ( int column = 0; column < BOARD_WIDTH; column++ ) {
            if ( this->currentBoard[row][column] == 6*colorModifier ) {
                kingColumn = column;
                kingRow = row;
            }
        }
    }
    // knight
    moves = this->generateKnightMoves( kingColumn, kingRow, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opposing colors piece
        if ( getPieceAt(moves[i].substr(2,2)) == 2*colorModifier*-1 ) {
            this->registerMove( to + from );
            this->currentBoard[rowTo][columnTo] = oldPiece;
            // std::cout << "King threatend by piece at: " << moves.at(i).substr(2,2) << std::endl;
            return true;
        }
    }
    // Rook or Queen
    moves = this->generateRookMoves( kingColumn, kingRow, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opposing colors piece
        int piece = getPieceAt(moves[i].substr(2,2));
        if ( piece == 4*colorModifier*-1 || piece == 5*colorModifier*-1 ) {
            this->registerMove( to + from );
            this->currentBoard[rowTo][columnTo] = oldPiece;
            // std::cout << "King threatend by piece at: " << moves.at(i).substr(2,2) << std::endl;
            return true;
        }
    }
    // Bishop or Queen
    moves = this->generateBishopMoves( kingColumn, kingRow, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opposing colors piece
        int piece = getPieceAt(moves[i].substr(2,2));
        if ( piece == 3*colorModifier*-1 || piece == 5*colorModifier*-1 ) {
            this->registerMove( to + from );
            this->currentBoard[rowTo][columnTo] = oldPiece;
            // std::cout << "King threatend by piece at: " << moves.at(i).substr(2,2) << std::endl;
            return true;
        }
    }
    // Pawn
    moves = this->generatePawnMoves( kingColumn, kingRow, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opposing colors pawn
        if ( getPieceAt(moves[i].substr(2,2)) == 1*colorModifier*-1 ) {
            this->registerMove( to + from );
            this->currentBoard[rowTo][columnTo] = oldPiece;
            // std::cout << "King threatend by piece at: " << moves.at(i).substr(2,2) << std::endl;
            return true;
        }
    }
    // King
    moves = this->generateKingMoves( kingColumn, kingRow, true);
    for ( int i = 0; i < moves.size(); i++ ) {
        // Check if opposing colors piece
        if ( getPieceAt(moves[i].substr(2,2)) == 6*colorModifier*-1 ) {
            this->registerMove( to + from );
            this->currentBoard[rowTo][columnTo] = oldPiece;
            // std::cout << "King threatend by piece at: " << moves.at(i).substr(2,2) << std::endl;
            return true;
        }
    }
    this->registerMove( to + from );
    this->currentBoard[rowTo][columnTo] = oldPiece;
    return false;
}

std::vector< std::string > Board::generatePawnMoves( int column, int row, bool onlyCaptures ) {
    std::vector< std::string > moves;
    std::string move = this->positionToString( column, row );
    bool isWhite = this->currentBoard[row][column] > 0;
    int nextColumn, nextRow;
    // If white then first move when pawn at row #2
    // If black then first move when pawn at row #7
    bool isFirstMove = isWhite ? row == 1 : row == 6;
    // If white inc (+), if black move dec (-)
    int forwardStep = isWhite ? 1 : -1;
    nextRow = row + forwardStep;
    // Check capture left
    nextColumn = column -1;
    if ( this->isCapture( nextColumn, nextRow , isWhite ) ) {
        moves.push_back( move + this->positionToString( nextColumn, nextRow ) );
    }
    // Check capture right
    nextColumn = column +1;
    if ( this->isCapture( nextColumn, nextRow, isWhite ) ) {
        moves.push_back( move + this->positionToString( nextColumn, nextRow ) );
    }
    // Check if free
    nextColumn = column;
    if ( this->isFree( nextColumn, nextRow ) && !onlyCaptures ) {
        moves.push_back( move + this->positionToString( nextColumn, nextRow ) );
        // If first movement possible to move 2 steps
        nextRow += forwardStep;
        if ( isFirstMove && this->isFree( nextColumn, nextRow ) ) {
            moves.push_back( move + this->positionToString( nextColumn, nextRow ) );
        }
    }
    // TODO: Check promotion
    return moves;
}

std::vector< std::string > Board::generateKnightMoves( int column, int row, bool onlyCaptures ) {
    std::vector< std::string > moves;
    bool isWhite = this->currentBoard[row][column] > 0;
    std::string move = this->positionToString( column, row );
    int nextColumn, nextRow, columnStep;

    for ( int rowStep = -2; rowStep <= 2; rowStep++ ) {
        if (rowStep == 0) continue;
        nextRow = row +rowStep;
        columnStep  = 3 -abs(rowStep);
        // left
        nextColumn = column -columnStep;
        if ( this->isCapture( nextColumn, nextRow, isWhite ) ) {
            moves.push_back( move + this->positionToString( nextColumn, nextRow ) );
        }
        else if ( !onlyCaptures && this->isFree( nextColumn, nextRow ) ) {
            moves.push_back( move + this->positionToString( nextColumn, nextRow ) );
        }
        // right
        nextColumn = column +columnStep;
        if ( this->isCapture( nextColumn, nextRow, isWhite ) ) {
            moves.push_back( move + this->positionToString( nextColumn, nextRow ) );
        }
        else if ( !onlyCaptures && this->isFree( nextColumn, nextRow ) ) {
            moves.push_back( move + this->positionToString( nextColumn, nextRow ) );
        }
    }
    return moves;
}

std::vector< std::string > Board::generateBishopMoves( int column, int row, bool onlyCaptures ) {
    std::vector< std::string > moves;
    bool isWhite = this->currentBoard[row][column] > 0;
    std::string move = this->positionToString( column, row );
    int nextColumn, nextRow;

    for ( int rowStep = -1; rowStep <= 1; rowStep += 2 ) {
        for ( int columnStep = -1; columnStep <= 1; columnStep += 2 ) {
            nextColumn = column + columnStep;
            nextRow = row + rowStep;
            while ( this->isValidPos( nextColumn, nextRow ) ) {
                // If free
                if ( this->isFree(nextColumn, nextRow) ) {
                    if ( !onlyCaptures ) {
                        moves.push_back( move + this->positionToString( nextColumn, nextRow ) );
                    }
                }
                else {
                    // If occupied by enemy add to list
                    if ( this->isCapture(nextColumn, nextRow, isWhite) ) {
                        moves.push_back( move + this->positionToString( nextColumn, nextRow ) );
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

std::vector< std::string > Board::generateRookMoves( int column, int row, bool onlyCaptures ) {
    std::vector< std::string > moves;
    bool isWhite = this->currentBoard[row][column] > 0;
    std::string move = this->positionToString( column, row );
    int nextColumn, nextRow;

    // Up and down
    for (int rowStep = -1; rowStep <= 1; rowStep += 2 ) {
        nextColumn = column;
        nextRow = row +rowStep;
        while ( this->isValidRow(nextRow) ) {
            // If free
            if ( this->isFree(nextColumn, nextRow) ) {
                if ( !onlyCaptures ) {
                    moves.push_back( move + this->positionToString( nextColumn, nextRow ) );
                }
            }
            else {
                // If occupied by enemy add to list
                if ( this->isCapture(nextColumn, nextRow, isWhite) ) {
                    moves.push_back( move + this->positionToString( nextColumn, nextRow ) );
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
        while ( this->isValidColumn(nextColumn) ) {
            // If free
            if ( this->isFree(nextColumn, nextRow) ) {
                if ( !onlyCaptures ) {
                    moves.push_back( move + this->positionToString( nextColumn, nextRow ) );
                }
            }
            else {
                // If occupied by enemy add to list
                if ( this->isCapture(nextColumn, nextRow, isWhite) ) {
                    moves.push_back( move + this->positionToString( nextColumn, nextRow ) );
                }
                break;
            }
            nextColumn += columnStep;
        }
    }
    return moves;
}

std::vector< std::string > Board::generateQueenMoves( int column, int row, bool onlyCaptures ) {
    std::vector< std::string > moves;
    bool isWhite = this->currentBoard[row][column] > 0;
    moves = this->generateBishopMoves( column, row, onlyCaptures );
    std::vector< std::string > rookMoves = this->generateRookMoves( column, row, onlyCaptures );
    moves.insert( moves.end(), rookMoves.begin(), rookMoves.end() );
    return moves;
}

std::vector< std::string > Board::generateKingMoves( int column, int row, bool onlyCaptures ) {
    std::vector< std::string > moves;
    bool isWhite = this->currentBoard[row][column] > 0;
    std::string move = this->positionToString( column, row );
    // Check the 8 squares around King
    for ( int nextRow = row-1; nextRow <= row+1; nextRow++ ) {
        // Skip out of bounds row
        if ( !this->isValidRow(nextRow) ) continue;
        for ( int nextColumn = column-1; nextColumn <= column+1; nextColumn++ ) {
            // Skip out of bounds column and current pos
            if ( !this->isValidColumn(nextColumn) || (nextRow == row && nextColumn == column) ) continue;
            // Free
            if ( !onlyCaptures && this->isFree( nextColumn, nextRow ) ) {
                moves.push_back( move + this->positionToString( nextColumn, nextRow ) );
            }
            // Capture for white
            else if ( this->isCapture( nextColumn, nextRow, isWhite ) ) {
                moves.push_back( move + this->positionToString( nextColumn, nextRow ) );
            }
        }
    }
    // TODO: Check castling
    return moves;
}

/* Helper functions */

char Board::getPieceAt( std::string pos ) {
    if ( pos.size() != 2 ) return -1;
    int column, row;
    column = this->columnToInt( pos.at(0) );
    row = this->rowToInt( pos.at(1) );
    return this->currentBoard[row][column];
}

std::string Board::positionToString( int column, int row ) {
    std::string res = "";
    switch ( column ) {
        case 0:
            res += "a";
            break;
        case 1:
            res += "b";
            break;
        case 2:
            res += "c";
            break;
        case 3:
            res += "d";
            break;
        case 4:
            res += "e";
            break;
        case 5:
            res += "f";
            break;
        case 6:
            res += "g";
            break;
        case 7:
            res += "h";
            break;
        default:
            res += "x";
            break;
    }
    res += std::to_string(row+1);
    return res;
}

int Board::columnToInt( char column ) {
    int res;
    switch ( column ) {
        case 'a':
            res = 0;
            break;
        case 'b':
            res = 1;
            break;
        case 'c':
            res = 2;
            break;
        case 'd':
            res = 3;
            break;
        case 'e':
            res = 4;
            break;
        case 'f':
            res = 5;
            break;
        case 'g':
            res = 6;
            break;
        case 'h':
            res = 7;
            break;
        default:
            res = -1;
            break;
    }
    return res;
}

int Board::rowToInt( char row ) {
    int res = row - '1';
    if ( this->isValidRow( res ) ) {
        return res;
    }
    else {
        return -1;
    }
}

bool Board::isValidRow( int row ) {
    return row >= 0 && row < BOARD_HEIGHT;
}

bool Board::isValidColumn( int column ) {
    return column >= 0 && column < BOARD_WIDTH;
}

bool Board::isValidPos( int column, int row ) {
    return isValidColumn(column) && isValidRow(row);
}

bool Board::isCapture( int column, int row, bool isWhite ) {
    if ( isValidPos(column, row) ) {
        return (this->currentBoard[row][column] > 0 && !isWhite) ||
               (this->currentBoard[row][column] < 0 && isWhite);
    }
    return false;
}

bool Board::isFree( int column, int row ) {
    return isValidPos(column, row) && this->currentBoard[row][column] == 0;
}
/* --- */
