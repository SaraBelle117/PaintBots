#include "InternalBoardSquare.h"

InternalBoardSquare::InternalBoardSquare():
    int_color(WHITE), 
    int_square(EMPTY), 
    int_dir(NORTH),
    int_redRobot(false),
    int_blueRobot(false)
{}

Color InternalBoardSquare::getSquareColor() const
{
    return int_color;
}

bool InternalBoardSquare::redRobotPresent() const
{
    return int_redRobot;
}

bool InternalBoardSquare::blueRobotPresent() const
{
    return int_blueRobot;
}

Direction InternalBoardSquare::robotDirection() const
{
    return int_dir;
}

SquareType InternalBoardSquare::getSquareType() const
{
    return int_square;    
}

void InternalBoardSquare::setSquareColor(Color col)
{
    int_color = col;
}

void InternalBoardSquare::setRedRobotPresent(bool p)
{
    int_redRobot = p;
}

void InternalBoardSquare::setBlueRobotPresent(bool p)
{
    int_blueRobot = p;
}

void InternalBoardSquare::setRobotDirection(Direction dir)
{
    int_dir = dir;
}

void InternalBoardSquare::setSquareType(SquareType sq)
{
    int_square = sq;
}