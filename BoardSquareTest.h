#pragma once
#include "ITest.h"
#include "BoardSquare.h"

class BoardSquareTest : public ITest {

    public:
        //constructor
        BoardSquareTest();
        virtual bool doTests() override;

    private:
        bool testSetColor();
        bool testRobotPresence();
        bool testDirection();
};