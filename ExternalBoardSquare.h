#include "BoardSquare.h"
#pragma once

class ExternalBoardSquare {

    private:
        Color ext_color;
        SquareType ext_square;
        Direction ext_dir;
        

    public:
        Color getSquareColor();
        bool redRobotPresent();
        bool blueRobotPresent();
        Direction robotDirection();
        SquareType getSquareType();
};