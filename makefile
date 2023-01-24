.PHONY: all clean

TARGET = othello
CXX = g++
CPPFLAGS = 
CXXFLAGS = -O3 -Wall --std=c++17

SRC = othello.cpp board.cpp brain.cpp hard_coded.cpp io.cpp minimax.cpp position.cpp
OBJ = $(SRC:%.cpp=%.o)

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

all: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ:%=%)

clean:
	rm ./*.o