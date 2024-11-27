#pragma once
#include "ObserverPattern.h"
#include "GameBoard.h"
#include <iostream>
using namespace std;

class PlainDisplay : public Observer<GameBoard> {
    private:
        GameBoard *gb;
    
    public:
        explicit PlainDisplay(GameBoard *gameBoard);

        virtual void update(ObservableData<GameBoard> *data) override;

        void display();
};