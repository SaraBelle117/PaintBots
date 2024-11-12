#include "ExternalBoardSquare.h"

ExternalBoardSquare::ExternalBoardSquare(const InternalBoardSquare& internalSquare):
    BoardSquare(internalSquare.getSquareColor(), internalSquare.getSquareType(), 
    internalSquare.robotDirection(), internalSquare.redRobotPresent(), 
    internalSquare.blueRobotPresent())
{}

