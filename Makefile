all: testconfig testinternalboard

testconfig: Config.cpp ConfigTest.cpp
	g++ -Wall -g -std=c++11 -o testconfig Config.cpp ConfigTest.cpp

InternalBoardSquareTest: InternalBoardSquareTest.cpp InternalBoardSquare.cpp BoardSquare.cpp
	g++ -Wall -g -std=c++11 -o testinternalboard InternalBoardSquareTest.cpp InternalBoardSquare.cpp BoardSquare.cpp

clean:
	rm -f display testconfig InternalBoardSquareTest Config.o