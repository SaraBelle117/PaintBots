#pragma once
#include <iostream>
#include "ObserverPattern.h"
#include "GameBoard.h"
#include "BoardSquare.h"
#include "IRobotAgent.h"

enum RobotMove{ROTATELEFT, ROTATERIGHT, FORWARD, NONE};


class Robot : public Observer<GameBoard>
{       
    public:
        //for updating the data (to be implemented)
        virtual void update(ObservableData<GameBoard> *data) override;

        //destructor 
        virtual ~Robot();

        enum RobotColor{RED, BLUE};
        SquareColor paintcolor;
        int paintblobs;
        int longrange;

        //default constructor
        Robot();

        //specific constructor
        Robot(RobotColor rc);

        ObservableData<GameBoard> *getLastUpdate();
        void setRobotAgent(IRobotAgent* a);
        IRobotAgent *getRobotAgent();
        void setColor(RobotColor);
        RobotColor getRobotColor();

    private:
        IRobotAgent* agent;
        RobotColor color;
        ObservableData<GameBoard> *lastData = nullptr;

};

struct RobotMoveRequest {
    Robot::RobotColor robot; 
    RobotMove move;
    bool shoot;
};