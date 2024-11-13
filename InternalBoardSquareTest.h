#pragma once
#include "ITest.h"
#include "InternalBoardSquare.h"

class InternalBoardSquareTest : public ITest {

    public:
        //constructor
        InternalBoardSquareTest();
        virtual bool doTests() override;

    private:
        bool testSetColor();
        bool testRobotPresence();
        bool testDirection();

};