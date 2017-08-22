#include "CommunicatorUCI.h"
#include <iostream>

#include <stdexcept>

CommunicatorUCI::CommunicatorUCI() {
    // std::cout << "Created CommunicatorUCI" << std::endl;
    this->isReady = false;
    this->whiteTurn = true;
}

CommunicatorUCI::~CommunicatorUCI() {
    // std::cout << "Destroyed CommunicatorUCI" << std::endl;
}

void CommunicatorUCI::run() {
    std::string tmp, keyword, args;
    this->init();
    bool running = true;
    // Handle options
    while (running) {
        getline(std::cin, tmp);
        size_t firstSpacePos = tmp.find(" ");
        keyword = tmp.substr(0, firstSpacePos);
        // Check for arguments
        if (firstSpacePos != std::string::npos ) {
            args = tmp.substr(firstSpacePos+1);
        }
        else {
            args = "";
        }
        if ( keyword == "debug" ) {
            this->debug();
        }
        else if ( keyword == "go" ) {
            this->go(args);
        }
        else if ( keyword == "isready" ) {
            // this->isReady = true;
            std::cout << "readyok" << std::endl;
        }
        else if ( keyword == "ucinewgame" ) {
            this->newGame();
        }
        else if ( keyword == "ponderhit" ) {
            this->ponderHit();
        }
        else if ( keyword == "position" ) {
            this->position(args);
        }
        else if ( keyword == "print" ) {
            this->board.printBoard();
        }
        else if ( keyword == "quit" ) {
            this->quit();
            running = false;
        }
        else if ( keyword == "register" ) {
            this->registration();
        }
        else if ( keyword == "setoption" ) {
            this->setOption();
        }
        else if ( keyword == "stop" ) {
            this->stop();
        }
    }
}

void CommunicatorUCI::debug() {}

void CommunicatorUCI::go( std::string args ) {
    // Find optimal move
    std::pair< std::string, int > move = this->moveEval.findBestMove(this->board, this->whiteTurn);
    std::cout << "bestmove " << move.first << std::endl;
}

void CommunicatorUCI::init() {
    std::cout << "id name " << CommunicatorUCI::NAME << std::endl;
    std::cout << "id author " << CommunicatorUCI::AUTHOR << std::endl;
    // Options here "option name ..."
    std::cout << "uciok" << std::endl;
}

void CommunicatorUCI::newGame() {
    board.resetBoard();
}

void CommunicatorUCI::ponderHit() {}

void CommunicatorUCI::position( std::string args ) {
    std::string option, move, moves;
    // First arg
    size_t spacePos = args.find(" ");
    option = args.substr(0, spacePos);
    args = args.substr(spacePos+1);
    // startpos
    if ( option == "startpos" ) {
        this->whiteTurn = true;
        this->board.resetBoard();
        // Second arg
        spacePos = args.find(" ");
        option = args.substr(0, spacePos);
        moves = args.substr(spacePos+1);
        if ( option == "moves" ) {
            // Process movelist
            while ( spacePos != std::string::npos ) {
                spacePos = moves.find(" ");
                move = moves.substr(0, spacePos);
                this->board.makeMove(move);
                this->whiteTurn = !this->whiteTurn;
                moves = moves.substr(spacePos+1);
            }
        }
    }
}

void CommunicatorUCI::quit() {}

void CommunicatorUCI::registration() {}

void CommunicatorUCI::setOption() {}

void CommunicatorUCI::stop() {}
