#pragma once
#include "ITest.h"
#include "GameBoard.h"

class GameBoardTest : public ITest {

        public:
            //constructor
            GameBoardTest();
            virtual bool doTests() override;

        private:
            bool testInstance();
            bool testGetSquare();
            bool testMoveRobot();
            bool testScores();
            bool testGetLongRangeScan();
            bool testGetShortRangeScan();
};