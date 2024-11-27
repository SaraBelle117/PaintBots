#include "ExternalBoardSquare.h"

ExternalBoardSquare::ExternalBoardSquare(){}

ExternalBoardSquare::ExternalBoardSquare(const InternalBoardSquare& internalSquare):
    BoardSquare(internalSquare.getSquareColor(), internalSquare.getSquareType(), 
    internalSquare.robotDirection(), internalSquare.redRobotPresent(), 
    internalSquare.blueRobotPresent())
{}

