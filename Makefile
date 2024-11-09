all: testconfig testinternalboard

testconfig: Config.cpp ConfigTest.cpp
	g++ -Wall -g -std=c++11 -o testconfig Config.cpp ConfigTest.cpp

testinternalboard: testInternalBoardSquare.cpp InternalBoardSquare.cpp 
	g++ -Wall -g -std=c++11 -o testinternalboard testInternalBoardSquare.cpp InternalBoardSquare.cpp

clean:
	rm -f display testconfig testinernalboard Config.o