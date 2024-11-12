#include "InternalBoardSquare.h"

InternalBoardSquare::InternalBoardSquare(): BoardSquare() {}

InternalBoardSquare::InternalBoardSquare(Color col, SquareType sq, Direction dir, bool redRobot, bool blueRobot):
    BoardSquare(col, sq, dir, redRobot, blueRobot){}

