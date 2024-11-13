#include "BoardSquareTest.h"
#include "BoardSquare.h"
#include <iostream>
using namespace std;

BoardSquareTest::BoardSquareTest() {}

bool BoardSquareTest::doTests()
{
    cout << "Testing BoardSquare class......." << endl;

    return (testSetColor() && testRobotPresence() && testDirection());
}

bool BoardSquareTest::testSetColor()
{
    BoardSquare sq(BLUE, EMPTY, NORTH, false, false);

    if(sq.getSquareColor() == BLUE){
        cout << "Testing set color: PASS" << endl;
        return true;
    }
    else{
        cout << "Testing set color: FAIL" << endl;
        return false;
    }
}

bool BoardSquareTest::testRobotPresence()
{
    BoardSquare sq2(WHITE, EMPTY, NORTH, false, true);

    if(sq2.blueRobotPresent() == true){
        cout << "Testing set robot: PASS" << endl;
        return true;
    }
    else{
        cout << "Testing set robot: FAIL" << endl;
        return false;
    }
}

bool BoardSquareTest::testDirection()
{
    BoardSquare sq3(WHITE, EMPTY, WEST, false, false);
    
    if(sq3.robotDirection() == WEST){
        cout << "Testing set direction: PASS" << endl;
        return true;
    }
    else{
        cout << "Testing set direction: FAIL" << endl;
        return false;
    }
}

int main()
{
    BoardSquareTest test;

    if(test.doTests()){
        cout << "BoardSquare tests: ALL PASSED" << endl;
    }
    else{
        cout << "BoardSquare tests: NOT ALL TESTS PASSED" << endl;
    }
    return 0;
}