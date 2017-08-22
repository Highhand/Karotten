#include <iostream>
#include <string>
#include "CommunicatorUCI.h"

int main( int argc, char* args[] )
{
    CommunicatorUCI uciComs = CommunicatorUCI();

    std::string tmp;
    getline(std::cin, tmp);
    if ( tmp == "uci" ) {
        uciComs.run();
    }

	return 0;
}
