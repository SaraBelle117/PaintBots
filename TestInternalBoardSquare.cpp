#include <iostream>
#include "InternalBoardSquare.h"
using namespace std;

void testGetSetColor()
{
    InternalBoardSquare square(RED, EMPTY, NORTH, false, false);

    if(square.getSquareColor() == RED){
        cout << "Testing set color: PASS" << endl;
    }
    else{
        cout << "Testing set color: FAIL" << endl;
    }
}

void testRobotPresence()
{
    InternalBoardSquare square2(WHITE, EMPTY, NORTH, true, false);

    if(square2.redRobotPresent() == true){
        cout << "Testing set robot1: PASS" << endl;
    }
    else{
        cout << "Testing set robot1: FAIL" << endl;
    }

    InternalBoardSquare square3(RED, EMPTY, NORTH, false, false);

    if(square3.redRobotPresent() == false){
        cout << "Testing set robot2: PASS" << endl;
    }
    else{
        cout << "Testing set robot2: FAIL" << endl;
    }
}

void testDirection()
{
    InternalBoardSquare square4(WHITE, EMPTY, SOUTH, false, false);

    if(square4.robotDirection() == SOUTH){
        cout << "Testing set direction: PASS" << endl;
    }
    else{
        cout << "Testing set direction: FAIL" << endl;
    }

}

int main()
{
    cout << "Testing Internal Board Square: " << endl;
    testGetSetColor();
    testRobotPresence();
    testDirection();
    return 0;
}