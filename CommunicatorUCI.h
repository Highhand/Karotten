#ifndef COMMUNICATOR_UCI_H
#define COMMUNICATOR_UCI_H

#include <string>
#include "Board.h"
#include "MoveEvaluator.h"
#include "MoveGenerator.h"

class CommunicatorUCI {
public:
    CommunicatorUCI();
    ~CommunicatorUCI();

    const std::string AUTHOR = "Simon Karlsson";
    const std::string NAME = "Karotten";

    void Run();
private:
    void Debug();

    void Go();

    void Init();

    void NewGame();

    void PonderHit();

    void Position(std::string args);

    void Quit();

    void Registration();

    void SetOption();

    void Stop();

    Board board;
    MoveEvaluator move_evaluator;
    bool is_ready; // True when gui is waiting for engine
    bool white_turn;
};

#endif
