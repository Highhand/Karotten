#OBJS specifies which files to compile as part of the project
OBJS = main.cpp Board.cpp CommunicatorUCI.cpp MoveEvaluator.cpp MoveGenerator.cpp
#CC specifies which compiler we're using
CC = g++
#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -std=c++11 -Wall -Wextra
#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS =
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Karotten
#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
