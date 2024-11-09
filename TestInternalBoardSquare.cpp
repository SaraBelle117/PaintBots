#include <iostream>
#include "InternalBoardSquare.h"
using namespace std;

void testGetSetColor()
{
    InternalBoardSquare square;
    square.setSquareColor(RED);

    if(square.getSquareColor() == RED){
        cout << "Testing set color: PASS" << endl;
    }
    else{
        cout << "Testing set color: FAIL" << endl;
    }
}

void testRobotPresence()
{
    InternalBoardSquare square;
    square.setRedRobotPresent(true);

    if(square.redRobotPresent() == true){
        cout << "Testing set robot1: PASS" << endl;
    }
    else{
        cout << "Testing set robot1: FAIL" << endl;
    }

    square.setRedRobotPresent(false);

    if(square.redRobotPresent() == false){
        cout << "Testing set robot2: PASS" << endl;
    }
    else{
        cout << "Testing set robot2: FAIL" << endl;
    }
}

void testDirection()
{
    InternalBoardSquare square;
    square.setRobotDirection(SOUTH);

    if(square.robotDirection() == SOUTH){
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