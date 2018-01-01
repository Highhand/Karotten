#include "CommunicatorUCI.h"
#include <iostream>

#include <stdexcept>

CommunicatorUCI::CommunicatorUCI() {
    // std::cout << "Created CommunicatorUCI" << std::endl;
    is_ready = false;
    white_turn = true;
}

CommunicatorUCI::~CommunicatorUCI() {
    // std::cout << "Destroyed CommunicatorUCI" << std::endl;
}

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
            board.PrintBoard();
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
    }
}

void CommunicatorUCI::Quit() {}

void CommunicatorUCI::Registration() {}

void CommunicatorUCI::SetOption() {}

void CommunicatorUCI::Stop() {}
