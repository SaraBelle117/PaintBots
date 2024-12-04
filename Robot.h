#pragma once
#include <iostream>
#include "BoardSquare.h"
#include "IRobotAgent.h"

enum RobotMove{ROTATELEFT, ROTATERIGHT, FORWARD, NONE};


class Robot
{
    private:
        IRobotAgent* agent;
        
    public: 
        //TODO -- need to be private?
        enum RobotColor{RED, BLUE};
        SquareColor paintcolor;
        int paintblobs;
        int longrange;

        


};

struct RobotMoveRequest {
            Robot::RobotColor robot; 
            RobotMove move;
            bool shoot;
        };