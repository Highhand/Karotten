TARGET_EXEC ?= Karotten

BUILD_DIR ?= ./
SRC_DIRS ?= ./

SRCS := $(shell find ./ -name "*.cpp")
OBJS := $(SRCS:%.cpp=%.o)

CXX = g++

CXXFLAGS = -std=c++17 -pedantic -Wall -Wextra -Werror -Wsuggest-attribute=const

$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@

# c++ source
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) *.o
