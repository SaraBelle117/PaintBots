#include "InternalBoardSquareTest.h"
#include "InternalBoardSquare.h"
#include <iostream>
using namespace std;

InternalBoardSquareTest::InternalBoardSquareTest() {}

/**
 * Completes the tests for InternalBoardSquare class
 * @return true if tests passed, false otherwise
 */
bool InternalBoardSquareTest::doTests()
{

    cout << "Testing InternalBoard class......." << endl;

    return (testSetColor() && testRobotPresence() && testDirection() && testBase());
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

/**
 * Tests the robot presence works as expected
 * @return true if passed, otherwise false
 */
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

/**
 * Tests the direction of InternalBoardSquare works as
 * expected
 * @return true if tests pass, otherwise false
 */
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

/**
 * Tests that InternalBoardSquare is a base class of BoardSquare
 * @return true if test passed, otherwise false
 */
bool InternalBoardSquareTest::testBase()
{
    if(std::is_base_of<BoardSquare, InternalBoardSquare>::value){
        cout << "Testing base class: PASS" << endl;
        return true;
    }
    else{
        cout << "Testing base class: FAIL" << endl;
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