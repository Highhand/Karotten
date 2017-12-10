#include <iostream>
#include <string>
#include "CommunicatorUCI.h"

int main( int argc, char* args[] )
{
  bool perft_debug = false;
  int perft_depth;

  for (int i = 0; i < argc; i++) {
    std::string arg = args[i];
    if (arg == "perft") {
      perft_debug = true;
    }
  }

  if (perft_debug) {
    MoveGenerator move_generator = MoveGenerator();
    Board board = Board();
    int perft_depth;
    std::cout << "Depth ";
    std::cin >> perft_depth;
    move_generator.Perft(perft_depth, board);

  }  else {
    std::string tmp;
    getline(std::cin, tmp);
    if ( tmp == "uci" ) {
      CommunicatorUCI uci_communicator = CommunicatorUCI();
      uci_communicator.Run();
    }
  }

	return 0;
}
