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
    std::vector< std::string > _moves;
    for ( int r = 0; r < BOARD_HEIGHT; r++ ) {
        for ( int c = 0; c < BOARD_WIDTH; c++ ) {
            if ( this->currentBoard[r][c] == 4 || this->currentBoard[r][c] == -4 ) {
                std::cout << "found bish" << std::endl;
                _moves = generateRookMoves( c, r );
                std::cout << positionToString( c, r ) << ": ";
                for (int i = 0; i < _moves.size(); i++ ) {
                    std::cout << _moves.at(i) << ", ";
                }
                std::cout << std::endl;
            }
        }
    }
}

void Board::registerMove( std::string move ) {
    if ( move.size() != 4 ) return;
    int _columnFrom, _rowFrom, _columnTo, _rowTo;
    _columnFrom = this->columnToInt( move.at(0) );
    // Assuming ASCII
    _rowFrom = move.at(1) - '1';
    _columnTo = this->columnToInt( move.at(2) );
    _rowTo = move.at(3) - '1';
    // Update board and check if valid pos to avoid segmentation error
    if ( this->isValidRow( _rowFrom ) && this->isValidRow( _rowTo ) &&
         this->isValidColumn( _columnFrom ) && this->isValidColumn( _columnTo ) &&
         this->currentBoard[_rowFrom][_columnFrom] != 0 )
    {
        this->currentBoard[_rowTo][_columnTo] = this->currentBoard[_rowFrom][_columnFrom];
        this->currentBoard[_rowFrom][_columnFrom] = 0;
    }
}

std::vector< std::string > Board::generatePawnMoves( int column, int row ) {
    std::vector< std::string > _moves;
    std::string _move = this->positionToString( column, row );
    bool _isWhite = this->currentBoard[row][column] > 0;
    int _nextColumn, _nextRow;
    // If white then first move when pawn at row #2
    // If black then first move when pawn at row #7
    bool _isFirstMove = _isWhite ? row == 1 : row == 6;
    // If white inc (+), if black move dec (-)
    int _forwardStep = _isWhite ? 1 : -1;
    // Check capture left
    _nextRow = row + _forwardStep;
    if ( this->isValidRow(_nextRow) ) {
        _nextColumn = column -1;
        if ( this->isValidColumn(_nextColumn) && this->isCapture( _nextColumn, _nextRow , _isWhite ) ) {
            // std::cout << "cap left " << std::endl;
            _moves.push_back( _move + this->positionToString( _nextColumn, _nextRow ) );
        }
        // Check capture right
        _nextColumn = column +1;
        if ( this->isValidColumn(_nextColumn) && this->isCapture( _nextColumn, _nextRow, _isWhite ) ) {
            // std::cout << "cap right " << std::endl;
            _moves.push_back( _move + this->positionToString( _nextColumn, _nextRow ) );
        }
        // Check if free
        _nextColumn = column;
        if ( this->isFree( _nextColumn, _nextRow ) ) {
            // std::cout << "free " << std::endl;
            _moves.push_back( _move + this->positionToString( _nextColumn, _nextRow ) );
            // If first movement possible to move 2 steps
            _nextRow += _forwardStep;
            if ( _isFirstMove && isValidRow(_nextRow) && this->isFree( _nextColumn, _nextRow ) ) {
                _moves.push_back( _move + this->positionToString( _nextColumn, _nextRow ) );
            }
        }
    }
    // TODO: Check promotion
    return _moves;
}

std::vector< std::string > Board::generateKnightMoves( int column, int row ) {
    std::vector< std::string > _moves;
    bool _isWhite = this->currentBoard[row][column] > 0;
    std::string _move = this->positionToString( column, row );
    int _nextColumn, _nextRow, _columnStep;

    for ( int _rowStep = -2; _rowStep <= 2; _rowStep++ ) {
        if (_rowStep == 0) continue;
        _nextRow = row +_rowStep;
        if ( this->isValidRow( _nextRow ) ) {
            // left
            _columnStep  = 3 -abs(_rowStep);
            _nextColumn = column -_columnStep;
            if ( this->isValidColumn( _nextColumn ) &&
                 ( this->isFree( _nextColumn, _nextRow ) || this->isCapture( _nextColumn, _nextRow, _isWhite ) ) )
            {
                _moves.push_back( _move + this->positionToString( _nextColumn, _nextRow ) );
            }
            // right
            _nextColumn = column +_columnStep;
            if ( this->isValidColumn( _nextColumn ) &&
                 ( this->isFree( _nextColumn, _nextRow ) || this->isCapture( _nextColumn, _nextRow, _isWhite ) ) )
            {
                _moves.push_back( _move + this->positionToString( _nextColumn, _nextRow ) );
            }
        }
    }
    return _moves;
}

std::vector< std::string > Board::generateBishopMoves( int column, int row ) {
    std::vector< std::string > _moves;
    bool _isWhite = this->currentBoard[row][column] > 0;
    std::string _move = this->positionToString( column, row );
    int _nextColumn, _nextRow;

    for ( int _rowStep = -1; _rowStep <= 1; _rowStep += 2 ) {
        // std::cout << "rdir: " << _rowStep << std::endl;
        for ( int _columnStep = -1; _columnStep <= 1; _columnStep += 2 ) {
            // std::cout << "cdir: " << _columnStep << std::endl;
            _nextColumn = column + _columnStep;
            _nextRow = row + _rowStep;
            while ( isValidColumn(_nextColumn) && isValidRow(_nextRow) ) {
                // std::cout << "checking" << std::endl;
                // Occupied
                if ( !isFree(_nextColumn, _nextRow) ) {
                    // If occupied by enemy
                    if ( isCapture(_nextColumn, _nextRow, _isWhite) ) {
                        _moves.push_back( _move + this->positionToString( _nextColumn, _nextRow ) );
                    }
                    break;
                }
                _moves.push_back( _move + this->positionToString( _nextColumn, _nextRow ) );
                _nextColumn += _columnStep;
                _nextRow += _rowStep;
            }
        }
    }
    return _moves;
}

std::vector< std::string > Board::generateRookMoves( int column, int row ) {
    std::vector< std::string > _moves;
    bool _isWhite = this->currentBoard[row][column] > 0;
    std::string _move = this->positionToString( column, row );
    int _nextColumn, _nextRow;

    // Up and down
    for (int _rowStep = -1; _rowStep <= 1; _rowStep += 2 ) {
        _nextColumn = column;
        _nextRow = row +_rowStep;
        while ( isValidRow(_nextRow) ) {
            // Occupied
            if ( !isFree(_nextColumn, _nextRow) ) {
                // If occupied by enemy
                if ( isCapture(_nextColumn, _nextRow, _isWhite) ) {
                    _moves.push_back( _move + this->positionToString( _nextColumn, _nextRow ) );
                }
                break;
            }
            _moves.push_back( _move + this->positionToString( _nextColumn, _nextRow ) );
            _nextRow += _rowStep;
        }
    }
    // Left and right
    for (int _columnStep = -1; _columnStep <= 1; _columnStep += 2 ) {
        _nextColumn = column +_columnStep;
        _nextRow = row ;
        while ( isValidColumn(_nextColumn) ) {
            // Occupied
            if ( !isFree(_nextColumn, _nextRow) ) {
                // If occupied by enemy
                if ( isCapture(_nextColumn, _nextRow, _isWhite) ) {
                    _moves.push_back( _move + this->positionToString( _nextColumn, _nextRow ) );
                }
                break;
            }
            _moves.push_back( _move + this->positionToString( _nextColumn, _nextRow ) );
            _nextColumn += _columnStep;
        }
    }
    return _moves;
}

std::vector< std::string > Board::generateQueenMoves( int column, int row ) {
    std::vector< std::string > _moves;
    bool _isWhite = this->currentBoard[row][column] > 0;
    _moves = this->generateBishopMoves( column, row );
    std::vector< std::string > _rookMoves = this->generateRookMoves( column, row );
    _moves.insert( _moves.end(), _rookMoves.begin(), _rookMoves.end() );
    return _moves;
}

std::vector< std::string > Board::generateKingMoves( int column, int row ) {
    std::vector< std::string > _moves;
    bool _isWhite = this->currentBoard[row][column] > 0;
    // std::cout << "Currpos r,c:" << row << ", " << column << std::endl;
    // Check the 8 squares around King
    for ( int r = row-1; r <= row+1; r++ ) {
        // Skip out of bounds row
        if ( r < 0 || r >= BOARD_HEIGHT ) continue;
        for ( int c = column-1; c <= column+1; c++ ) {
            // Skip out of bounds column
            if ( c < 0 || c >= BOARD_WIDTH || (r == row && c == column) ) continue;
            std::string move = this->positionToString( column, row );
            char _nextPos = this->currentBoard[r][c];
            // Free
            if ( _nextPos == 0 ) {
                _moves.push_back( move + this->positionToString( c, r ) );
                // std::cout << "Found free: " << move << " at r: " << r << ", c: " << c << std::endl;
            }
            // Capture for white
            else if ( _nextPos < 0 && _isWhite ) {
                _moves.push_back( move + this->positionToString( c, r ) );
                // std::cout << "Found white cap: " << move << " at c: " << r << ", r: " << c << std::endl;
            }
            // Capture for black
            else if ( _nextPos > 0 && !_isWhite ) {
                _moves.push_back( move + this->positionToString( c, r ) );
                // std::cout << "Found black cap: " << move << " at c: " << r << ", r: " << c << std::endl;
            }
        }
    }
    // TODO: Check castling
    return _moves;
}

/* Helper functions */
std::string Board::positionToString( int column, int row ) {
    std::string _res = "";
    switch ( column ) {
        case 0:
            _res += "a";
            break;
        case 1:
            _res += "b";
            break;
        case 2:
            _res += "c";
            break;
        case 3:
            _res += "d";
            break;
        case 4:
            _res += "e";
            break;
        case 5:
            _res += "f";
            break;
        case 6:
            _res += "g";
            break;
        case 7:
            _res += "h";
            break;
        default:
            _res += "x";
            break;
    }
    _res += std::to_string(row+1);
    return _res;
}

int Board::columnToInt( char column ) {
    int _res;
    switch ( column ) {
        case 'a':
            _res = 0;
            break;
        case 'b':
            _res = 1;
            break;
        case 'c':
            _res = 2;
            break;
        case 'd':
            _res = 3;
            break;
        case 'e':
            _res = 4;
            break;
        case 'f':
            _res = 5;
            break;
        case 'g':
            _res = 6;
            break;
        case 'h':
            _res = 7;
            break;
        default:
            _res = -1;
            break;
    }
    return _res;
}

bool Board::isValidRow( int r ) {
    return r >= 0 && r < BOARD_HEIGHT;
}

bool Board::isValidColumn( int c ) {
    return c >= 0 && c < BOARD_WIDTH;
}

bool Board::isCapture( int column, int row, bool isWhite ) {
    return (this->currentBoard[row][column] > 0 && !isWhite) ||
         (this->currentBoard[row][column] < 0 && isWhite);
}

bool Board::isFree( int column, int row ) {
    return this->currentBoard[row][column] == 0;
}
/* --- */
