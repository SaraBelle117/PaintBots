#pragma once
#include <iostream>
#include "ObserverPattern.h"
//#include "GameBoard.h"
#include "IRobotAgent.h"

class GameBoard;

class Robot : public Observer<GameBoard>
{ 
    private:
        IRobotAgent* agent;
        RobotColor color;
        ObservableData<GameBoard> *lastData = nullptr;

    public:
        SquareColor paintcolor;
        int paintblobs;
        int longrange;

        //default constructor (implemented in .cpp file)
        Robot();

        //destructor 
        virtual ~Robot();

        //for updating the data (to be implemented)
        virtual void update(ObservableData<GameBoard> *data) override;

        ObservableData<GameBoard> *getLastUpdate();
        void setRobotAgent(IRobotAgent* a);
        IRobotAgent *getRobotAgent();
        void setColor(RobotColor);
        RobotColor getRobotColor();

};