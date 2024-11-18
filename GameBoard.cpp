#include "GameBoard.h"
#include <iostream>
using namespace std;

//initializes the gameboard to a null pointer
GameBoard* GameBoard::instance = nullptr;

GameBoard::GameBoard() : board(row, vector<InternalBoardSquare>(col))
{
    //creates a default game configuration
    //Config config;

    //populates boarder of the GameBoard with WALL BoardSquares
    setWalls();

    //populates rocks for the GameBoard using config
    setRocks(config);

    //sets robots on the GameBoard
    setRobots();

    //sets (randomized) number of fog squares from default config (between 5 - 10)
    numFogSquares = RAND_IN_RANGE(config.getFogLowerBound(), config.getFogUpperBound());
}

GameBoard::GameBoard(Config config): board(row, vector<InternalBoardSquare>(col))
{
    //populates boarder of the GameBoard with WALL BoardSquares
    setWalls();

    //populates rocks for the GameBoard using config
    setRocks(config);

    //sets robots on the GameBoard
    setRobots();

    //sets (randomized) number of fog squares from default config (between 5 - 10)
    numFogSquares = RAND_IN_RANGE(config.getFogLowerBound(), config.getFogUpperBound());
}

/**
 * Returns the instance of the GameBoard (Singleton Pattern)
 * @param string password (xyzzzy)
 * @return instance of the GameBoard
 */
GameBoard* GameBoard::getInstance(string password)
{
    if(password.compare("xyzzy") != 0){
        cerr << "Password does not match." << endl;
        return nullptr;
    }

    if(instance == nullptr){
        instance = new GameBoard();
    }

    return instance;
}
/**
 * Returns the instance of the GameBoard with the given config
 * @param string password (xyzzzy)
 * @return instance of the GameBoard
 */
GameBoard* GameBoard::getInstance(string password, Config config)
{
    if(password.compare("xyzzy") != 0){
        cerr << "Password does not match." << endl;
        return nullptr;
    }

    if(instance == nullptr){
        instance = new GameBoard(config);
    }
    //ignores a new config if given

    return instance;
}

/**
 * Helper function to set the walls of the GameBoard
 */
void GameBoard::setWalls()
{
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            //if boundary of the grid, set SquareType as WALL
            if(i == 0 || i == row || j == 0 || j == col){
                board[row][col].applySquareType(WALL);
            }
        }
    }
}
/**
 * Helper function to set rocks of the GameBoard
 */
void GameBoard::setRocks(Config config)
{
    //sets (randomized) number of rocks from config (if default config: between 10 - 20)
    int numRocks = RAND_IN_RANGE(config.getRockLowerBound(), config.getRockUpperBound());

    for(int i = 0; i < numRocks; i++){
        //for positions of the board we are adding rocks to
        int x, y;
        //generates a rand num until it finds an empty square (with no blue or red robot present)
        while(board[x][y].getSquareType() != EMPTY || board[x][y].redRobotPresent() || board[x][y].blueRobotPresent()){
            //ensures x & y is a random number between 1 - 13
            x = RAND_IN_RANGE(1, 13);
            y = RAND_IN_RANGE(1, 13);            
        }
        //sets SquareType at x, y
        board[x][y].applySquareType(ROCK);
    }  
}

/**
 * Helper function to set robots on the GameBoard
 */
void GameBoard::setRobots()
{
    for(RobotColor rc : {RED, BLUE}){
        //for positions of the board we are adding robots to
        int x, y;
        //generates a rand num until it finds an empty square (with no blue or red robot present)
        while(board[x][y].getSquareType() != EMPTY || board[x][y].redRobotPresent() || board[x][y].blueRobotPresent()){
            //ensures x & y is a random number between 1 - 13
            x = RAND_IN_RANGE(1, 13);
            y = RAND_IN_RANGE(1, 13);
        }

        board[x][y].setRobot(rc, true);
    }
}

/**
 * Gets the BoadSquare at the indicated index. 
 * @param int row
 * @param int col
 * @return InternalBoardSquare at board[row][col]
 */
InternalBoardSquare & GameBoard::getSquare(int row, int col)
{
    //ensures the row and col are valid values
    if(row >= 0 && col >= 0 && row < 15 && col < 15){
        return board[row][col];
    }
    else{
        //throws error if row and col are now valid
        throw out_of_range("Invalid square index.");
    }
}

/**
 * Performs the request move on the designated robot
 */
bool GameBoard::moveRobot(RobotMoveRequest & mr)
{
    Location pos;
    //identifies the given robots position on the board
    pos = find(mr.robot);
    
    InternalBoardSquare sq = getSquare(pos.x, pos.y);

    if(mr.move == ROTATELEFT || mr.move == ROTATERIGHT){
        Direction newDir;
        switch(sq.robotDirection()){
            case NORTH:
                if(mr.move == ROTATELEFT) newDir = WEST;
                if(mr.move == ROTATERIGHT) newDir = EAST;
                break;
            case WEST:
                if(mr.move == ROTATELEFT) newDir = SOUTH;
                if(mr.move == ROTATERIGHT) newDir = NORTH;
                break;
            case EAST:
                if(mr.move == ROTATELEFT) newDir = NORTH;
                if(mr.move == ROTATERIGHT) newDir = SOUTH;
                break;
            case SOUTH:
                if(mr.move == ROTATELEFT) newDir = EAST;
                if(mr.move == ROTATERIGHT) newDir = WEST;
                break;
        }
         sq.applyRobotDirection(newDir);
    }
    else if(mr.move == FORWARD){
        //sets the new position of the Robot
        Location newPos = getNextPosition(pos, sq.robotDirection());

        //sets the old square (the one we are moving from) as the Robot's color
        if(mr.robot == RED){
            setSquareColor(pos.x, pos.y, red.paintcolor);
        }
        else{
            setSquareColor(pos.x, pos.y, blue.paintcolor);
        }
        sq.setRobot(mr.robot, false);
        board[newPos.x][newPos.y].setRobot(mr.robot, true);
    }
    if(mr.shoot){
        PaintBlobHit(mr);
    }

    return true;
}

/**
 * Indicates if the PaintBlob (of the given robot) hits the
 * other or not
 */
bool GameBoard::PaintBlobHit(RobotMoveRequest & mr)
{   
    //checks that the given robot has enough paintBlobs to shoot
    if(mr.robot == RED && red.paintblobs >= config.getPaintBlobLimit())return false;
    if(mr.robot == BLUE && blue.paintblobs >= config.getPaintBlobLimit()) return false;


    Location pos = find(mr.robot);
    RobotColor enemy;
    if(mr.robot == RobotColor::RED) enemy = RobotColor::BLUE;
    if(mr.robot == RobotColor::BLUE) enemy = RobotColor::RED;
    //identifies the enemy color position on the GameBoard
    Location enemy_pos = find(enemy);
    InternalBoardSquare sq;
    
    do{
        sq = getSquare(pos.x, pos.y);
        pos = getNextPosition(pos, sq.robotDirection());
        
        //indicates that we have hit the enemy with our PaintBlob
        if(pos.x == enemy_pos.x && pos.y == enemy_pos.y){
            //increments corresponding limit
            if(mr.robot == RED){
                red.paintblobs++;
                setRobotPaintColor(mr.robot, SquareColor::RED);
            } 
            if(mr.robot == BLUE){
                blue.paintblobs++;
                setRobotPaintColor(mr.robot, SquareColor::BLUE);
            }
            return true;
        }
        //traces the movement until one of these conditions is reached
    } while(sq.getSquareType() != ROCK && sq.getSquareType() != WALL);

    //returns false if this point is reached (would indicate we hit a WALL or ROCK BoardSquare)
    return false;
}

/**
 * Returns the score from the board using the indicated color
 * @param RobotColor col
 * @return int value of score
 */
int GameBoard::getScore(RobotColor col)
{
    int score = 0;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(board[row][col].getSquareColor() == col){
                score++;
            }
        }
    }
    return score;
}

/**
 * Returns the score for the blue team
 * @return int score
 */
int GameBoard::blueScore()
{
    return getScore(BLUE);
}

/**
 * Returns the score for the red team
 * @return int score
 */
int GameBoard::redScore()
{
    return getScore(RED);
}

/**
 * Sets the SquareColor of a BoardSquare at specified index
 * @param int row
 * @param int col
 * @param SquareColor sc
 */
void GameBoard::setSquareColor(int row, int col, SquareColor sc)
{
    //ensures the row and col are valid values
    if(row >= 0 && col >= 0 && row < 15 && col < 15){
        board[row][col].applySquareColor(sc);
    }
    else{
        //throws error if row and col are now valid
        throw out_of_range("Invalid square index.");
    }
}

/**
 * Sets the given robot's paint color
 */
void GameBoard::setRobotPaintColor(RobotColor robot, SquareColor sc)
{
    if(robot == RobotColor::RED) red.paintcolor = sc;
    if(robot == RobotColor::BLUE) blue.paintcolor = sc;
}

ExternalBoardSquare** GameBoard::getLongRangeScan()
{
    if(config.getLongRangeLimit() >= longRangeCalls){

    }
    longRangeCalls++;
}

ExternalBoardSquare** GameBoard::getShortRangeScan(RobotColor rc)
{
    //TODO
}

/**
 * Helper method to return the given location (int x, int y)
 * with the given robot color
 */
Location GameBoard::find(RobotColor rc)
{
    Location p;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            //checks that square contains robot desired
            InternalBoardSquare sq = getSquare(i, j);
            if((sq.redRobotPresent() && rc == RED) || (sq.blueRobotPresent() && rc == BLUE)){
                p.x  = i;
                p.y = j;
                return p;
            }
        }
    }
}

/**
 * Returns the location of the next position in the GameBoard
 * (given Direction)
 * 
 */
Location GameBoard::getNextPosition(Location point, Direction dir){
    switch(dir){
        case NORTH:
            point.y--;
            return point;
        case EAST:
            point.x++;
            return point;
        case SOUTH:
            point.y++;
            return point;
        case WEST:
            point.x--;
            return point;
    }
    //if the direction is invalid, just return the same point
    return point;
}

