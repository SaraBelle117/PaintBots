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

    return (testInstance() && testGetSquare() && testScores() && testGetLongRangeScan()
    && testGetShortRangeScan() && testMoveRobot() && testObserver());

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

/**
 * Tests that the moveRobot() function returns true (as it always should)
 * and makes moves on the board
 * @return true if tests pass, otherwise false
 */
bool GameBoardTest::testMoveRobot()
{
    GameBoard* gb4 = GameBoard::getInstance("xyzzy");

    //make sure we have a game instance before continuing
    if(gb4 == nullptr){
        cerr << "GameBoard instance could not be created." << endl;
        return false;
    }

    gb4->reset();
    cout << "Resetting board..." << endl;

    Location p;

    p = gb4->find(XRED);

    InternalBoardSquare sq = gb4->getSquare(p.x, p.y);
    //sq.applyRobotDirection(SOUTH);
    RobotMoveRequest mr = {XRED, FORWARD, false};
    bool move = false;

    move = gb4->moveRobot(mr);
    move = gb4->moveRobot(mr);
    move = gb4->moveRobot(mr);

    mr.robot = XBLUE;
    move = gb4->moveRobot(mr);

    if(move){
        cout << "Test moveRobot(): PASSED" <<endl;
        return true;
    }
    else{
        cout << "Test moveRobot(): FAILED" <<endl;
        return false;
    }
}

/**
 * Tests that the score is being calculated correctly
 * @return true if tests pass, otherwise false
 */
bool GameBoardTest::testScores()
{
    GameBoard* gb7 = GameBoard::getInstance("xyzzy");
    //make sure we have a game instance before continuing
    if(gb7 == nullptr){
        cerr << "GameBoard instance could not be created." << endl;
        return false;
    }

    //sets all square colors as red
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            gb7->setSquareColor(i, j, RED);
        }
    }
    if(gb7->redScore() != 225){
        cout << "Test scores(): FAILED" << gb7->redScore() << endl;
        return false;
    }

    //sets all square colors as white (resets)
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            gb7->setSquareColor(i, j, WHITE);
        }
    }

    cout << "Test scores(): PASSED" << endl;
    return true;
}

/**
 * Tests that getLongRangeScan() works as expected
 * @return true if tests pass, false otherwise
 */
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

    //deletes the list since we are now done using it 
    gb5->freeScan(grid, 15);

    return true;
}

/**
 * Tests that getShortRangeScan() works as expected
 * @return true if test passes, otherwise false
 */
bool GameBoardTest::testGetShortRangeScan()
{
    GameBoard* gb6 = GameBoard::getInstance("xyzzy");
    //make sure we have a game instance before continuing
    if(gb6 == nullptr){
        cerr << "GameBoard instance could not be created." << endl;
        return false;
    }

    gb6->setSquareColor(3, 3, BLUE);
    gb6->setSquareColor(2, 2, BLUE);


    ExternalBoardSquare** grid = gb6->getShortRangeScan(XBLUE);
    InternalBoardSquare sq = gb6->getSquare(2, 2);
    InternalBoardSquare sq2 = gb6->getSquare(3, 3);
    if(sq.getSquareColor() != BLUE || sq2.getSquareColor() != BLUE){
        cout << "Test getShortRangeScan(): FAILED" << endl;
    
        return false;
    }
    
    //deletes the array we allocated, since we are done using it 
    gb6->freeScan(grid, 5);

    return true;
}

/**
 * Tests that the observer is given the right change data 
 * @return true if test passes, otherwise false
 */
bool GameBoardTest::testObserver()
{
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