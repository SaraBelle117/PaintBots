#include "BoardSquare.h"
#include "InternalBoardSquare.h"
#pragma once

class ExternalBoardSquare {
    private:
        Color ext_color;
        SquareType ext_square;
        Direction ext_dir;
        bool ext_redRobot;
        bool ext_blueRobot;
    public:
        //constructor
        ExternalBoardSquare(const InternalBoardSquare& internalSquare);
        //getter methods
        Color getSquareColor() const;
        bool redRobotPresent() const;
        bool blueRobotPresent() const;
        Direction robotDirection() const;
        SquareType getSquareType() const;
};