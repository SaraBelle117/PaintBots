#include "GameBoardTest.h"
#include "PlainDisplay.h"
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

    gb = GameBoard::getInstance("WRONG_PASSWORD");
    if(gb == nullptr){
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
    GameBoard* gb = GameBoard::getInstance("xyzzy");
    if(gb == nullptr){
        cerr << "GameBoard instance could not be created." << endl;
        return false;
    }

    try{
        //both squares at boundary should be a WALL SQUARE
        InternalBoardSquare& sq = gb->getSquare(0, 0);
        InternalBoardSquare& sq2 = gb->getSquare(14, 14);

        if(sq.getSquareType() != WALL && sq2.getSquareType() != WALL){
            cout << "Test GetSquare(): FAILED" << endl;
            return false;
        }

        //should be invalid index, make sure this throws an exception
        InternalBoardSquare& sq3 = gb->getSquare(-1, 3);

        //fixes warning from compiler (since we are intentionally not using it)
        (void)sq3;
        cout << "Test GetSquare(): FAILED [did not throw out_of_range exception]" << endl;
        return false;

    } catch (const out_of_range& exception){
        //if this point has been reached, all tests so far have passed
        cout << "Test GetSquare(): PASSED [" << exception.what() << "]" << endl;
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
    GameBoard* gb = GameBoard::getInstance("xyzzy");

    //make sure we have a game instance before continuing
    if(gb == nullptr){
        cerr << "GameBoard instance could not be created." << endl;
        return false;
    }

    gb->reset();
    cout << "Resetting board..." << endl;

    Location p;

    p = gb->find(Robot::RED);

    InternalBoardSquare sq = gb->getSquare(p.x, p.y);
    //sq.applyRobotDirection(SOUTH);
    RobotMoveRequest mr = {Robot::RED, FORWARD, false};
    bool move = false;

    move = gb->moveRobot(mr);
    move = gb->moveRobot(mr);
    move = gb->moveRobot(mr);

    mr.robot = Robot::BLUE;
    move = gb->moveRobot(mr);

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
    GameBoard* gb = GameBoard::getInstance("xyzzy");
    //make sure we have a game instance before continuing
    if(gb == nullptr){
        cerr << "GameBoard instance could not be created." << endl;
        return false;
    }

    try{
        //sets all square colors as red
        for(int i = 1; i <= 15; i++){
            for(int j = 1; j <= 15; j++){
                gb->setSquareColor(i, j, RED);
            }
        }
        if(gb->redScore() != 225){
            cout << "Test scores(): FAILED" << gb->redScore() << endl;
            return false;
        }

        //sets all square colors as white (resets)
        for(int i = 1; i <= 15; i++){
            for(int j = 1; j <= 15; j++){
                gb->setSquareColor(i, j, WHITE);
            }
        }

        cout << "Test scores(): PASSED" << endl;
        return true;

       //catches out of range exception 
    } catch(const out_of_range& exception){
        cout << "Test scores(): FAILED [" << exception.what() << "]" <<  endl;
        return false;
    }
}

/**
 * Tests that getLongRangeScan() works as expected
 * @return true if tests pass, false otherwise
 */
bool GameBoardTest::testGetLongRangeScan()
{
    GameBoard* gb = GameBoard::getInstance("xyzzy");
    //make sure we have a game instance before continuing
    if(gb == nullptr){
        cerr << "GameBoard instance could not be created." << endl;
        return false;
    }

    //sets up squares with specific values
    gb->setSquareColor(1, 1, BLUE);
    gb->setSquareColor(2, 2, RED);
    gb->setSquareColor(3, 3, WHITE);

    ExternalBoardSquare** grid = gb->getLongRangeScan();

    //displays the grid returns from getLongRangeScan()
    cout << "Printing getLongRangeScan()... " << endl;
    PlainDisplay display;
    display.displayScan(grid, 17);

    if(grid[1][1].getSquareColor() != BLUE || grid[2][2].getSquareColor() != RED || grid[3][3].getSquareColor() != WHITE){
        cout << "Test getLongRangeScan(): FAILED" << endl;
        gb->freeScan(grid, 17);
        return false;
    }
    cout << "Test getLongRangeScan(): PASSED" << endl;

    //deletes the list since we are now done using it 
    gb->freeScan(grid, 17);

    return true;
}

/**
 * Tests that getShortRangeScan() works as expected
 * @return true if test passes, otherwise false
 */
bool GameBoardTest::testGetShortRangeScan()
{
    GameBoard* gb = GameBoard::getInstance("xyzzy");
    //make sure we have a game instance before continuing
    if(gb == nullptr){
        cerr << "GameBoard instance could not be created." << endl;
        return false;
    }
    
    try {

    Location position = gb->find(Robot::BLUE);

    //sets some of the surrounding BoardSquares as blue
    gb->setSquareColor(position.x, position.y, BLUE);
    gb->setSquareColor(position.x + 1, position.y, BLUE);
    gb->setSquareColor(position.x, position.y + 1, BLUE);


    ExternalBoardSquare** grid = gb->getShortRangeScan(Robot::BLUE);

    //displays the grid returns from getShortRangeScan()
    cout << "Printing getShortRangeScan()..." << endl;
    PlainDisplay display;
    display.displayScan(grid, 5);

    //checks that the grids we set are blue in the grid, as expected
    if(grid[2][2].getSquareColor() != BLUE && grid[2][3].getSquareColor() != BLUE && grid[3][2].getSquareColor() != BLUE){
        cout << "Test getShortRangeScan(): FAILED" << endl;
        gb->freeScan(grid, 5);
        return false;
    }

    Location p = gb->find(Robot::RED);
    InternalBoardSquare& fog = gb->getSquare(p.x, p.y);
    fog.applySquareType(FOG);

    grid = gb->getShortRangeScan(Robot::RED);
    cout << "Printing getShortRangeScan()..." << endl;
    display.displayScan(grid, 5);

    if(grid[2][2].getSquareType() != FOG){
        cout << "Test getShortRangeScan(): FAILED" << endl;
        gb->freeScan(grid, 5);
        return false;
    }

    //deletes the array we allocated, since we are done using it 
    gb->freeScan(grid, 5);

    } catch(const runtime_error& exception){
        cout << "Test getShortRangeScan(): FAILED [" << exception.what() << "]" << endl;
        return false;
    }


    //this point reached, indicates all tests have passed
    cout <<  "Test getShortRangeScan(): PASSED " << endl;
    return true;
}

/**
 * Tests that the observer is given the right change data 
 * @return true if test passes, otherwise false
 */
bool GameBoardTest::testObserver()
{
    GameBoard* gb = GameBoard::getInstance("xyzzy");
    //ensures we have a valid GameBoard before continuing test. 
    if(gb == nullptr){
        cerr << "GameBoard instance could not be created." << endl;
        return false;
    }

    PlainDisplay *display = new PlainDisplay();
    gb->registerObserver(display);
    
    gb->setSquareColor(1, 1, RED);
    
    ObservableData<GameBoard> *data = display->getLastUpdate();

    //if data returns a nullptr, test failed
    if(data == nullptr){
        cout << "Test observer: FAILED" << endl;
        return false;
    }

    if(data->getEvent() == SQUARE_COLOR &&
       data->getData().SquareColorData.pos.x == 1 &&
       data->getData().SquareColorData.pos.y == 1 &&
       data->getData().SquareColorData.color == RED){
        cout << "Test observer: PASSED" << endl;
        return true;
    }
    //if point reached, failed test
    cout << "Test observer: FAILED" << endl;
    return false;

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