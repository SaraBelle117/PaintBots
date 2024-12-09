#pragma once
#include <iostream>
#include "BoardSquare.h"
#include "IRobotAgent.h"

enum RobotMove{ROTATELEFT, ROTATERIGHT, FORWARD, NONE};


class Robot
{       
    public: 
        enum RobotColor{RED, BLUE};
        SquareColor paintcolor;
        int paintblobs;
        int longrange;

        //default constructor
        Robot();
        void setRobotAgent(IRobotAgent* a);
        IRobotAgent *getRobotAgent();
        void setColor(RobotColor);
        RobotColor getRobotColor();

    private:
        IRobotAgent* agent;
        RobotColor color;

};

struct RobotMoveRequest {
    Robot::RobotColor robot; 
    RobotMove move;
    bool shoot;
};