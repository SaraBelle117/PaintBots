#include <iostream>
#include "InternalBoardSquare.h"

void testGetSetColor()
{
    InternalBoardSquare square;
    square.setSquareColor(RED);

    if(square.getSquareColor() == RED){
        std::cout << "testSetColor passed!" << std::endl;
    }
    else{
        std::cout << "testSetColor failed." << std::endl;
    }
}

void testRobotPresence()
{
    InternalBoardSquare square;
    square.setRedRobotPresent(true);

    if(square.redRobotPresent() == true){
        std::cout << "testRobotPresence p1 passed!" << std::endl;
    }
    else{
        std::cout << "testRobotPresence p1 failed." << std::endl;
    }

    square.setRedRobotPresent(false);

    if(square.redRobotPresent() == false){
        std::cout << "testRobotPresence p2 passed!" << std::endl;
    }
    else{
        std::cout << "testRobotPresence p2 failed." << std::endl;
    }
}

void testDirection()
{
    InternalBoardSquare square;
    square.setRobotDirection(SOUTH);

    if(square.robotDirection() == SOUTH){
        std::cout << "testDirection passed." << std::endl;
    }
    else{
        std::cout << "testDirection failed." << std::endl;
    }

}

int main()
{
    testGetSetColor();
    testRobotPresence();
    testDirection();
    return 0;
}