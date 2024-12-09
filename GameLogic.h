#pragma once
#include <string>
#include "GameBoard.h"
using namespace std;

class GameLogic
{
    private:
        GameBoard* gameboard;
        Robot *red;
        Robot *blue;
        bool pause;

    public:
        //default constructor
        GameLogic();

        //destructor
        ~GameLogic();

        void playGame(string boardconfig, string robotconfig);

        void setPause(bool pausemode);


};