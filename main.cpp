#include <iostream>
#include <string>
#include "CommunicatorUCI.h"

int main()
{
  while (true) {
    std::string tmp;
    getline(std::cin, tmp);
    if (tmp == "perft") {
      MoveGenerator move_generator = MoveGenerator();
      Board board = Board();
      int perft_depth;
      std::cout << "depth ";
      std::cin >> perft_depth;
      std::cout << move_generator.Perft(perft_depth, board, true) << std::endl;
    } else if (tmp == "uci" ) {
      CommunicatorUCI uci_communicator = CommunicatorUCI();
      uci_communicator.Run();
    } else if (tmp == "q") break;
  }

	return 0;
}
