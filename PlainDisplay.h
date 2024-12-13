#pragma once
#include "ObserverPattern.h"
#include "GameBoard.h"
#include <iostream>
using namespace std;

class PlainDisplay : public Observer<GameBoard> 
{
    private:
        GameBoard *gb;

        //for testing purposes
        ObservableData<GameBoard> *lastData = nullptr;

    public:
        //default constructor
        PlainDisplay();

        //destructor
        virtual ~PlainDisplay(){}

        //updates the observer
        virtual void update(ObservableData<GameBoard> *data) override;

        //for displaying the GameBoard
        void display();

        //added for testing getShortRangeScan() and getLongRangeScan()
        void displayScan(ExternalBoardSquare** list, int size);

        //added for testing observers are receiving the correct data
        ObservableData<GameBoard> *getLastUpdate();

        //for opening the game
        static void titleScreen();

        //for adding colors to the board
        static const string RESET; 
        static const string PURPLE_C;
        static const string RED_C;
        static const string BLUE_C;
        static const string REDBOLD;
        static const string BLUEBOLD;
        static const string GREEN_C;
        static const string YELLOW_C;
        
    
};