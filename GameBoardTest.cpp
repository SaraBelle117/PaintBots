#include "GameBoardTest.h"
#include <iostream>
using namespace std;

GameBoardTest::GameBoardTest() {}

/**
 * Runs all tests within GameBoardTest
 * @return true if all tests passed, false otherwise
 */
bool GameBoardTest::doTests()
{
    cout << "Testing GameBoard class......." << endl;

    return (testInstance() && testGetSquare() && testMoveRobot() && testScores() && testGetLongRangeScan() && testGetShortRangeScan());

}

/**
 * Tests the given instance for the class (with correct password, and incorrect password)
 * @return true if both tests passed, false otherwise
 */
bool GameBoardTest::testInstance()
{
    bool test1, test2;
    GameBoard* gb = GameBoard::getInstance("xyzzy");
    if(gb == nullptr){
        cout << "Test Instance (w/ correct password): FAILED" << endl;
        test1 = false;
    }
    else{
        cout << "Test Instance (w/ correct password): PASSED" << endl;
        test1 = true;
    }

    GameBoard* gb2 = GameBoard::getInstance("WRONG_PASSWORD");
    if(gb2 == nullptr){
        cout << "Test Instance (w/ incorrect password): PASSED" << endl;
        test2 = true;
    }
    else{
        cout << "Test Instance (w/ incorrect passowrd): FAILED" << endl;
        test2 = false;
    }

    return (test1 && test2);
}

/**
 * Tests that getSquare method works as intended
 * @return true if passed, false otherwise
 */
bool GameBoardTest::testGetSquare()
{
    GameBoard* gb3 = GameBoard::getInstance("xyzzy");
    if(gb3 == nullptr){
        cerr << "GameBoard instance could not be created." << endl;
        return false;
    }

    try{
        //both squares at boundary should be a WALL SQUARE
        InternalBoardSquare& sq = gb3->getSquare(0, 0);
        InternalBoardSquare& sq2 = gb3->getSquare(14, 14);

        if(sq.getSquareType() != WALL && sq2.getSquareType() != WALL){
            cout << "Test GetSquare(): FAILED" << endl;
            return false;
        }

        //should be invalid index, make sure this throws an exception
        InternalBoardSquare& sq3 = gb3->getSquare(-1, 3);

        //fixes warning from compiler (since we are intentionally not using it)
        (void)sq3;
        cout << "Test GetSquare(): FAILED" << endl;
        return false;

    } catch (const out_of_range&){
        //if this point has been reached, all tests so far have passed
        cout << "Test GetSquare(): PASSED" << endl;
    }

    return true;
}

bool GameBoardTest::testMoveRobot()
{
    GameBoard* gb4 = GameBoard::getInstance("xyzzy");
    //make sure we have a game instance before continuing
    if(gb4 == nullptr){
        cerr << "GameBoard instance could not be created." << endl;
        return false;
    }

    return true;
}

bool GameBoardTest::testScores()
{
    GameBoard* gb7 = GameBoard::getInstance("xyzzy");
    //make sure we have a game instance before continuing
    if(gb7 == nullptr){
        cerr << "GameBoard instance could not be created." << endl;
        return false;
    }
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            gb7->setSquareColor(i, j, RED);
        }
    }
    if(gb7->redScore() != 225){
        cout << "Test scores(): FAILED" << gb7->redScore() << endl;
        return false;
    }

    cout << "Test scores(): PASSED" << endl;
    return true;
}

bool GameBoardTest::testGetLongRangeScan()
{
    GameBoard* gb5 = GameBoard::getInstance("xyzzy");
    //make sure we have a game instance before continuing
    if(gb5 == nullptr){
        cerr << "GameBoard instance could not be created." << endl;
        return false;
    }

    //sets up squares with specific values
    gb5->setSquareColor(1, 1, BLUE);
    gb5->setSquareColor(2, 2, RED);
    gb5->setSquareColor(3, 3, WHITE);

    ExternalBoardSquare** grid = gb5->getLongRangeScan();

    if(grid[1][1].getSquareColor() != BLUE || grid[2][2].getSquareColor() != RED || grid[3][3].getSquareColor() != WHITE){
        cout << "Test getLongRangeScan(): FAILED" << endl;
        return false;
    }
    cout << "Test getLongRangeScan(): PASSED" << endl;

    return true;
}

bool GameBoardTest::testGetShortRangeScan()
{
    GameBoard* gb6 = GameBoard::getInstance("xyzzy");
    //make sure we have a game instance before continuing
    if(gb6 == nullptr){
        cerr << "GameBoard instance could not be created." << endl;
        return false;
    }

    gb6->setRobotPaintColor(XRED, RED);
    gb6->setSquareColor(7, 7, WHITE);

    ExternalBoardSquare** grid = gb6->getShortRangeScan(XRED);
    if(grid[2][2].getSquareType() != EMPTY || grid[2][2].getSquareColor() != WHITE){
        cout << "Test getShortRangeScan(): FAILED" << endl;
        return false;
    }

    return true;
}

int main()
{
    GameBoardTest test;
    if(test.doTests()){
        cout << "GameBoard tests: ALL PASSED" << endl;
    }
    else{
        cout << "GameBoard tests: NOT ALL TESTS PASSED" << endl;
    }
    return 0;
}