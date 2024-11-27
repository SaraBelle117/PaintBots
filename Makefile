all: ConfigTest InternalBoardSquareTest ExternalBoardSquareTest BoardSquareTest GameBoardTest

ConfigTest: Config.cpp ConfigTest.cpp
	g++ -Wall -g -std=c++11 -o ConfigTest Config.cpp ConfigTest.cpp

InternalBoardSquareTest: InternalBoardSquareTest.cpp InternalBoardSquare.cpp BoardSquare.cpp
	g++ -Wall -g -std=c++11 -o InternalBoardSquareTest InternalBoardSquareTest.cpp InternalBoardSquare.cpp BoardSquare.cpp

ExternalBoardSquareTest: ExternalBoardSquareTest.cpp ExternalBoardSquare.cpp BoardSquare.cpp
	g++ -Wall -g -std=c++11 -o ExternalBoardSquareTest ExternalBoardSquareTest.cpp ExternalBoardSquare.cpp BoardSquare.cpp

BoardSquareTest: BoardSquareTest.cpp BoardSquare.cpp 
	g++ -Wall -g -std=c++11 -o BoardSquareTest BoardSquareTest.cpp BoardSquare.cpp

GameBoardTest: GameBoardTest.cpp GameBoard.cpp Config.cpp ExternalBoardSquare.cpp InternalBoardSquare.cpp BoardSquare.cpp PlainDisplay.cpp
	g++ -Wall -g -std=c++11 -o GameBoardTest GameBoardTest.cpp GameBoard.cpp Config.cpp ExternalBoardSquare.cpp InternalBoardSquare.cpp BoardSquare.cpp PlainDisplay.cpp

clean:
	rm -f display ConfigTest InternalBoardSquareTest ExternalBoardSquareTest BoardSquareTest GameBoardTest *.o