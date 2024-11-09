#include "BoardSquare.h"
#pragma  once

class InternalBoardSquare{
    private:
        Color int_color;
        SquareType int_square;
        Direction int_dir;
        bool int_redRobot;
        bool int_blueRobot;
    public:
        //constructor
        InternalBoardSquare();

        //getter methods
        Color getSquareColor() const;
        bool redRobotPresent() const;
        bool blueRobotPresent() const;
        Direction robotDirection() const;
        SquareType getSquareType() const;
        
        //setter methods
        void setSquareColor(Color col);
        void setRedRobotPresent(bool p);
        void setBlueRobotPresent(bool p);
        void setRobotDirection(Direction dir);
        void setSquareType(SquareType sq);
};