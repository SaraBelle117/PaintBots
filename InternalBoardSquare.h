#pragma  once
#include "BoardSquare.h"

class InternalBoardSquare : public BoardSquare{

    public:
        //constructor
        InternalBoardSquare();

        //specific constructor
        InternalBoardSquare(SquareColor col, SquareType sq, Direction dir, bool redRobot, bool blueRobot);
    
};