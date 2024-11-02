#include "ExternalBoardSquare.h"

ExternalBoardSquare::ExternalBoardSquare(const InternalBoardSquare& internalSquare):
    ext_color(internalSquare.getSquareColor()), 
    ext_square(internalSquare.getSquareType()), 
    ext_dir(internalSquare.robotDirection()),
    ext_redRobot(internalSquare.redRobotPresent()),
    ext_blueRobot(internalSquare.blueRobotPresent())
{}

Color ExternalBoardSquare::getSquareColor() const
{
    return ext_color;
}

bool ExternalBoardSquare::redRobotPresent() const
{
    return ext_redRobot;
}

bool ExternalBoardSquare::blueRobotPresent() const
{
    return ext_blueRobot;
}

Direction ExternalBoardSquare::robotDirection() const
{
    return ext_dir;
}

SquareType ExternalBoardSquare::getSquareType() const
{
    return ext_square;    
}