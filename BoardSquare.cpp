#include "BoardSquare.h"

//default constructor
BoardSquare::BoardSquare():
    b_color(WHITE),
    b_square(EMPTY),
    b_dir(NORTH),
    b_redRobot(false),
    b_blueRobot(false)
    {}

//specific constructor
BoardSquare::BoardSquare(Color col, SquareType sq, Direction dir, bool redRobot, bool blueRobot):
    b_color(col), b_square(sq), b_dir(dir), b_redRobot(redRobot), b_blueRobot(blueRobot)
    {}

//copy constructor
BoardSquare::BoardSquare(const BoardSquare & rhs):
    b_color(rhs.b_color), b_square(rhs.b_square), b_dir(rhs.b_dir), 
    b_redRobot(rhs.b_redRobot), b_blueRobot(rhs.b_blueRobot)
    {}

//virtual destructor
BoardSquare:: ~BoardSquare(){};

//operator =
const BoardSquare & BoardSquare::operator = (const BoardSquare & rhs){
    //prevents self-assignment (don't want to override object with itself)
    if(this != &rhs){
        b_color = rhs.b_color;
        b_square = rhs.b_square;
        b_dir = rhs.b_dir;
        b_redRobot = rhs.b_redRobot;
        b_blueRobot = rhs.b_blueRobot;
    }
    return *this;
}

Color BoardSquare::getSquareColor() const {
    return b_color;
}

SquareType BoardSquare::getSquareType() const {
    return b_square;
}

Direction BoardSquare::robotDirection() const {
    return b_dir;
}

bool BoardSquare::redRobotPresent() const {
    return b_redRobot;
}

bool BoardSquare::blueRobotPresent() const {
    return b_blueRobot;
}

//sets the square color
void BoardSquare::setSquareColor(Color col){
    b_color = col;
}

//sets the square type
void BoardSquare::setSquareType(SquareType sq){
    b_square = sq;
}

//sets the robot's direction
void BoardSquare::setRobotDirection(Direction dir){
    b_dir = dir;
}

//sets red robot 
void BoardSquare::setRedRobotPresent(bool p){
    b_redRobot = p;
}


//sets blue robot
void BoardSquare::setBlueRobotPresent(bool p){
    b_blueRobot = p;
}