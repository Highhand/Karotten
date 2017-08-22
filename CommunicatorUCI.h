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

    static constexpr char* AUTHOR = "Simon Karlsson";
    static constexpr char* NAME = "Karotten";

    void run();
private:
    void debug();

    void go( std::string args );

    void init();

    void newGame();

    void ponderHit();

    void position( std::string args);

    void quit();

    void registration();

    void setOption();

    void stop();

    Board board;
    MoveEvaluator moveEval;
    bool isReady; // True when gui is waiting for engine
    bool whiteTurn;
};

#endif
