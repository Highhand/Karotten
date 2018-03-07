#include "Board.h"
#include <iostream>

Board::Board() {
    ResetBoard();
}

std::array< std::array< char, Board::WIDTH >, Board::HEIGHT > Board::GetCurrentBoard() {
    return current_board;
}

char Board::GetPieceAt(std::string pos) {
    // A position must be of length 2
    if (pos.size() != 2) return 0;

    int column, row;
    column = ColumnToInt(pos.at(0));
    row = RowToInt(pos.at(1));
    // If invalid postion return 0
    if (!IsValidPos(column, row)) return 0;
    return current_board[row][column];
}

char Board::GetPieceAt(int column, int row) {
    if (!IsValidPos(column, row)) return 0;
    return current_board[row][column];
}

void Board::SetPieceAt(std::string pos, char piece) {
    // A position must be of length 2
    if (pos.size() != 2) return;
    int column, row;
    column = ColumnToInt(pos.at(0));
    row = RowToInt(pos.at(1));
    // Return if invalid position
    if (!IsValidPos(column, row)) return;
    // Check if valid piece
    if (piece >= -6 && piece <= 6) {
        current_board[row][column] = piece;
    }
    else {
        current_board[row][column] = 0;
    }
}

void Board::SetPieceAt(int column, int row, char piece) {
    // Return if invalid position
    if (!IsValidPos(column, row)) return;
    if (piece >= -6 && piece <= 6) {
        current_board[row][column] = piece;
    }
    else {
        current_board[row][column] = 0;
    }
}

std::string Board::GetLastMove() {
    return last_move;
}

char Board::MakeMove(std::string move) {
    if (move.size() != 4) return 0;
    int column_from, row_from, column_to, row_to;
    char captured_piece = 0;
    column_from = ColumnToInt(move.at(0));
    row_from = RowToInt(move.at(1));
    column_to = ColumnToInt(move.at(2));
    row_to = RowToInt(move.at(3));
    // Update board and check if valid pos to avoid segmentation error
    if (IsValidPos(column_from, row_from) && IsValidPos(column_to, row_to) &&
         !IsFree(column_from, row_from))
    {
        captured_piece = GetPieceAt(column_to, row_to);
        SetPieceAt(column_to, row_to, GetPieceAt(column_from, row_from));
        SetPieceAt(column_from, row_from, 0);
        last_move = move;
    }
    return captured_piece;
}

void Board::UndoMove(std::string move, char captured_piece) {
    if (move.size() != 4) return;
    int column_from, row_from, column_to, row_to;
    column_from = ColumnToInt(move.at(2));
    row_from = RowToInt(move.at(3));
    column_to = ColumnToInt(move.at(0));
    row_to = RowToInt(move.at(1));
    // Update board and check if valid pos to avoid segmentation error
    if (IsFree(column_to, row_to))
    {
        SetPieceAt(column_to, row_to, GetPieceAt(column_from, row_from));
        SetPieceAt(column_from, row_from, captured_piece);
    }
}

void Board::PrintBoard() {
    for (int row = 0; row < Board::HEIGHT; row++) {
        for (int column = 0; column < Board::WIDTH; column++) {
            int piece = (int)GetPieceAt(column ,row);
            std::string tmp = piece < 0 ? "|" : "| ";
            std::cout << tmp << (int)GetPieceAt(column ,row) << " ";
        }
        std::cout << "|" << std::endl;
    }
}

void Board::ResetBoard() {
    current_board[0] = { 4, 2, 3, 5, 6, 3, 2, 4 };
    current_board[1] = { 1, 1, 1, 1, 1, 1, 1, 1 };
    current_board[2] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    current_board[3] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    current_board[4] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    current_board[5] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    current_board[6] = { -1, -1, -1, -1, -1, -1, -1, -1 };
    current_board[7] = { -4, -2, -3, -5, -6, -3, -2, -4 };

    last_move = "";
}

std::string Board::PositionToString(int column, int row) {
    std::string res = "";
    switch (column) {
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
            break;
    }
    res += std::to_string(row+1);
    return res;
}

int Board::ColumnToInt(char column) {
    int res;
    switch (column) {
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

int Board::RowToInt(char row) {
    int res = row - '1';
    if (IsValidRow(res)) {
        return res;
    }
    else {
        return -1;
    }
}

bool Board::IsValidRow(int row) {
    return row >= 0 && row < Board::HEIGHT;
}

bool Board::IsValidColumn(int column) {
    return column >= 0 && column < Board::WIDTH;
}

bool Board::IsValidPos(int column, int row) {
    return IsValidColumn(column) && IsValidRow(row);
}

bool Board::IsCapture(int column, int row, bool isWhite) {
    if (IsValidPos(column, row)) {
        return (current_board[row][column] > 0 && !isWhite) ||
               (current_board[row][column] < 0 && isWhite);
    }
    return false;
}

bool Board::IsFree(int column, int row) {
    return IsValidPos(column, row) && current_board[row][column] == 0;
}
