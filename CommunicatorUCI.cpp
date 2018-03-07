#include "CommunicatorUCI.h"
#include <iostream>

void CommunicatorUCI::Run() {
    std::string tmp, keyword, args;
    Init();
    bool running = true;
    // Handle options
    while (running) {
        getline(std::cin, tmp);
        size_t firstspace_pos = tmp.find(" ");
        keyword = tmp.substr(0, firstspace_pos);
        // Check for arguments
        if (firstspace_pos != std::string::npos) {
            args = tmp.substr(firstspace_pos+1);
        }
        else {
            args = "";
        }
        if (keyword == "Debug") {
            Debug();
        }
        else if (keyword == "go") {
            Go();
        }
        else if (keyword == "isready") {
            // is_ready = true;
            std::cout << "readyok" << std::endl;
        }
        else if (keyword == "ucinewgame") {
            NewGame();
        }
        else if (keyword == "ponderhit") {
            PonderHit();
        }
        else if (keyword == "position") {
            Position(args);
        }
        else if (keyword == "print") {
            Print(args);
        }
        else if (keyword == "quit") {
            Quit();
            running = false;
        }
        else if (keyword == "register") {
            Registration();
        }
        else if (keyword == "setoption") {
            SetOption();
        }
        else if (keyword == "stop") {
            Stop();
        }
    }
}

void CommunicatorUCI::Debug() {}

void CommunicatorUCI::Go() {
    // Find optimal move
    std::pair< std::string, int > move = move_evaluator.FindBestMove(board, white_turn);
    std::cout << "bestmove " << move.first << std::endl;
}

void CommunicatorUCI::Init() {
    std::cout << "id name " << CommunicatorUCI::NAME << std::endl;
    std::cout << "id author " << CommunicatorUCI::AUTHOR << std::endl;
    // Options here "option name ..."
    std::cout << "uciok" << std::endl;
}

void CommunicatorUCI::NewGame() {
    board.ResetBoard();
}

void CommunicatorUCI::PonderHit() {}

void CommunicatorUCI::Position(std::string args) {
    std::string option, move, moves;
    // First arg
    size_t space_pos = args.find(" ");
    option = args.substr(0, space_pos);
    args = args.substr(space_pos+1);
    // startpos
    if (option == "startpos") {
        white_turn = true;
        board.ResetBoard();
        // Second arg
        space_pos = args.find(" ");
        option = args.substr(0, space_pos);
        moves = args.substr(space_pos+1);
        if (option == "moves") {
            // Process movelist
            while (space_pos != std::string::npos) {
                space_pos = moves.find(" ");
                move = moves.substr(0, space_pos);
                board.MakeMove(move);
                white_turn = !white_turn;
                moves = moves.substr(space_pos+1);
            }
        }
    } else if (option == "fen") {
      // https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
      // Pieces
      space_pos = args.find(" ");
      auto boards_setup = args.substr(0,space_pos);
      args.substr(space_pos+1);
      int row{7},column{0};
      for (auto& piece : boards_setup) {
        if (row == 0 && column > 7) break;
        switch (piece) {
          case '/':
            row--;
            column = 0;
            break;
          case 'p':
            board.SetPieceAt(column,row,-1);
            column++;
            break;
          case 'n':
            board.SetPieceAt(column,row,-2);
            column++;
            break;
          case 'b':
            board.SetPieceAt(column,row,-3);
            column++;
            break;
          case 'r':
            board.SetPieceAt(column,row,-4);
            column++;
            break;
          case 'q':
            board.SetPieceAt(column,row,-5);
            column++;
            break;
          case 'k':
            board.SetPieceAt(column,row,-6);
            column++;
            break;
          case 'P':
            board.SetPieceAt(column,row,1);
            column++;
            break;
          case 'N':
            board.SetPieceAt(column,row,2);
            column++;
            break;
          case 'B':
            board.SetPieceAt(column,row,3);
            column++;
            break;
          case 'R':
            board.SetPieceAt(column,row,4);
            column++;
            break;
          case 'Q':
            board.SetPieceAt(column,row,5);
            column++;
            break;
          case 'K':
            board.SetPieceAt(column,row,6);
            column++;
            break;
          default:
            auto empty_cols = std::stoi(std::string{piece});
            for (int i = 0; i < empty_cols; ++i) {
              board.SetPieceAt(column,row,0);
              column++;
            }
            break;
        }
      }
      // Active color
      space_pos = args.find(" ");
      auto active_color = args.substr(0,space_pos);
      args.substr(space_pos+1);
      active_color == "w" ? white_turn = true : white_turn = false;
      // Castling available
      // En passant target
      // Halfmove clock for fifty move rule
      // Fullmove nr start at 1
    }
    // TODO: FEN strings
}

void CommunicatorUCI::Print(std::string args) {
    std::string option;
    size_t space_pos = args.find(" ");
    option = args.substr(0, space_pos);
    args = args.substr(space_pos+1);
    if (option == "board") {
      board.PrintBoard();
    } else if (option == "moves") {
      auto moves = move_generator.GenerateMoves(board,white_turn);
      std::cout << moves.size() << ": ";
      for (auto& move : moves) {
        std::cout << move << " ";
      }
      std::cout << std::endl;
    } else if (option == "last") {
      std::cout << board.GetLastMove() << std::endl;
    }
}

void CommunicatorUCI::Quit() {}

void CommunicatorUCI::Registration() {}

void CommunicatorUCI::SetOption() {}

void CommunicatorUCI::Stop() {}
