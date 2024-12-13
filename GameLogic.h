#pragma once
#include <string>
#include "GameBoard.h"
using namespace std;

class PlainDisplay;

class GameLogic
{
    private:
        GameBoard* gameboard;
        Robot *red;
        Robot *blue;
        bool pause;
        bool red_lrs;
        bool blue_lrs;

    public:
        //default constructor
        GameLogic();

        //destructor
        ~GameLogic();

        void playGame(string boardconfig, string robotconfig);

        void setPause(bool pausemode);

};