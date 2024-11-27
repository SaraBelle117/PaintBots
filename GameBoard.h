#pragma once
#include "InternalBoardSquare.h"
#include "ExternalBoardSquare.h"
#include "Config.h"
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

#define RAND_IN_RANGE(min, max) ((min) + rand() % ((max) - (min) + 1))

//changed to XRED and XBLUE per the announcement 
enum RobotColor{XRED, XBLUE};

enum RobotMove{ROTATELEFT, ROTATERIGHT, FORWARD, NONE};

struct RobotMoveRequest
{
    RobotColor robot; 
    RobotMove move;
    bool shoot;
};

struct Robot
{
    RobotMoveRequest robotmove;
    RobotColor color;
    SquareColor paintcolor;
    int paintblobs;
    int longrange;
};


class GameBoard {
    private:
        static GameBoard* instance;
        int row = 15;
        int col = 15;
        vector<vector<InternalBoardSquare>> board;
        Config config;
        Robot blue;
        Robot red;
        int numFogSquares;

        //default constructor
        GameBoard();

        //specific constructor
        GameBoard(Config config);

        //helper methods
        //for blueScore() and redScore()
        int getScore(RobotColor col);
        //for setting walls on the GameBoard
        void setWalls();
        //for setting rocks on the GameBoard
        void setRocks(Config config);
        //for setting robot positions on the GameBoard
        void setRobots();
        //finds the BoardSquare that contains the given robot
        Location find(RobotColor rc);
        //identifies the next position (given direction)
        Location getNextPosition(Location point, Direction dir);
        //checks that we are still within the bounds of the board
        bool checkBounds(int x, int y);
        

    
    public:
        static GameBoard* getInstance(string password);
        static GameBoard* getInstance(string password, Config config);
        InternalBoardSquare & getSquare(int row, int col);
        bool moveRobot(RobotMoveRequest & mr );
        bool PaintBlobHit(RobotMoveRequest & mr);
        int blueScore();
        int redScore();
        void setSquareColor(int row, int col, SquareColor sc);
        void setRobotPaintColor(RobotColor robot, SquareColor sc);
        ExternalBoardSquare** getLongRangeScan();
        ExternalBoardSquare** getShortRangeScan(RobotColor rc);

};