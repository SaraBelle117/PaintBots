#pragma once
#include "ObserverPattern.h"
#include "GameBoard.h"
using namespace std;

class PlainDisplay : public Observer<GameBoard> {
    private:
        GameBoard *gb;
    
    public:
        explicit PlainDisplay(GameBoard *gameBoard) : gb(gameBoard) {}

        void update(GameBoard *data) override {
            gb = data;
            display();
        }
};