#include "InternalBoardSquareTest.h"
#include "InternalBoardSquare.h"
#include <iostream>
using namespace std;

InternalBoardSquareTest::InternalBoardSquareTest() {}

bool InternalBoardSquareTest::doTests(){

    cout << "Testing InternalBoard class......." << endl;
    bool t1, t2, t3;
    t1 = testSetColor();
    t2 = testRobotPresence();
    t3 = testDirection();

    return (t1 && t2 && t3);
}

bool InternalBoardSquareTest::testSetColor()
{
    InternalBoardSquare square(RED, EMPTY, NORTH, false, false);

    if(square.getSquareColor() == RED){
        cout << "Testing set color: PASS" << endl;
        return true;
    }
    else{
        cout << "Testing set color: FAIL" << endl;
        return false;
    }
}

bool InternalBoardSquareTest::testRobotPresence()
{
    InternalBoardSquare square2(WHITE, EMPTY, NORTH, true, false);
    bool test1, test2;

    if(square2.redRobotPresent() == true){
        cout << "Testing set robot1: PASS" << endl;
        test1 = true;
    }
    else{
        cout << "Testing set robot1: FAIL" << endl;
        test1 = false;
    }

    InternalBoardSquare square3(RED, EMPTY, NORTH, false, false);

    if(square3.redRobotPresent() == false){
        cout << "Testing set robot2: PASS" << endl;
        test2 = true;
    }
    else{
        cout << "Testing set robot2: FAIL" << endl;
        test2 = false;
    }   
    return(test1 && test2);
}

bool InternalBoardSquareTest::testDirection()
{
    InternalBoardSquare square4(WHITE, EMPTY, SOUTH, false, false);

    if(square4.robotDirection() == SOUTH){
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
    InternalBoardSquareTest test;
    
    if(test.doTests()){
        cout << "InternalBoardSquare tests: ALL PASSED" << endl;
    }
    else{
        cout << "InternalBoardSquare tests: NOT ALL TESTS PASSED" << endl;
    }
    return 0;
}