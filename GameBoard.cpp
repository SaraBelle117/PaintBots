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
    else{
        cerr << "Warning: GameBoard already exists, new configuration has been ignored." << endl;
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
            if(i == 0 || i == (row - 1) || j == 0 || j == (col - 1)){
                board[i][j].applySquareType(WALL);
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
        int x = 0, y = 0;
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
    for(RobotColor rc : {XRED, XBLUE}){
        //for positions of the board we are adding robots to
        int x = 0, y = 0;
        //generates a rand num until it finds an empty square (with no blue or red robot present)
        while(board[x][y].getSquareType() != EMPTY || board[x][y].redRobotPresent() || board[x][y].blueRobotPresent()){
            //ensures x & y is a random number between 1 - 13
            x = RAND_IN_RANGE(1, 13);
            y = RAND_IN_RANGE(1, 13);
        }
        if(rc == XRED){
            board[x][y].applyRedRobotPresent(true);
        }
        else{
            board[x][y].applyBlueRobotPresent(true);
        }
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
        if(mr.robot == XRED){
            setSquareColor(pos.x, pos.y, red.paintcolor);
            sq.applyRedRobotPresent(false);
            board[newPos.x][newPos.y].applyRedRobotPresent(true);
        }
        else{
            setSquareColor(pos.x, pos.y, blue.paintcolor);
            sq.applyBlueRobotPresent(false);
            board[newPos.x][newPos.y].applyBlueRobotPresent(true);
        }
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
    if(mr.robot == XRED && red.paintblobs >= config.getPaintBlobLimit())return false;
    if(mr.robot == XBLUE && blue.paintblobs >= config.getPaintBlobLimit()) return false;


    Location pos = find(mr.robot);
    RobotColor enemy;
    if(mr.robot == XRED) enemy = XBLUE;
    if(mr.robot == XBLUE) enemy = XRED;
    //identifies the enemy color position on the GameBoard
    Location enemy_pos = find(enemy);
    InternalBoardSquare sq;
    
    do{
        //checks we are are still in bounds!
        if(!checkBounds(pos.x, pos.y)) break;

        sq = getSquare(pos.x, pos.y);
        pos = getNextPosition(pos, sq.robotDirection());
        
        //indicates that we have hit the enemy with our PaintBlob
        if(pos.x == enemy_pos.x && pos.y == enemy_pos.y){
            //increments corresponding limit
            if(mr.robot == XRED){
                red.paintblobs++;
                setRobotPaintColor(mr.robot, RED);
            } 
            if(mr.robot == XBLUE){
                blue.paintblobs++;
                setRobotPaintColor(mr.robot, BLUE);
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
    SquareColor color;
    if(col == XRED){
        color = RED;
    }
    else{
        color = BLUE;
    }
    
    int score = 0;
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            if(board[i][j].getSquareColor() == color){
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
    return getScore(XBLUE);
}

/**
 * Returns the score for the red team
 * @return int score
 */
int GameBoard::redScore()
{
    return getScore(XRED);
}

/**
 * Sets the SquareColor of a BoardSquare at specified index
 * @param int row
 * @param int col
 * @param SquareColor sc
 */
void GameBoard::setSquareColor(int x, int y, SquareColor sc)
{
    //ensures the row and col are valid values
    if(x >= 0 && y >= 0 && x < 15 && y < 15){
        board[x][y].applySquareColor(sc);
    }
    else{
        //throws error if row and col are now valid
        throw out_of_range("Invalid square index.");
    }
}

/**
 * Sets the given robot's paint color
 * @param RobotColor 
 * @param SquareColor
 */
void GameBoard::setRobotPaintColor(RobotColor robot, SquareColor sc)
{
    if(robot == XRED) red.paintcolor = sc;
    if(robot == XBLUE) blue.paintcolor = sc;
}

/**
 * Returns the GameBoard represented as a 2D array of 
 * ExternalBoardSquares
 * @return ExternalBoardSquares as a 15x15 array
 */
ExternalBoardSquare** GameBoard::getLongRangeScan()
{
    //Allocates row of pointers (for 2D array)
   ExternalBoardSquare** longboard = new ExternalBoardSquare*[row];

   for(int i = 0; i < row; i++){
        //Allocates each row as an array of ExternalBoardSquares 
        longboard[i] = new ExternalBoardSquare[col];
    for(int j = 0; j < col; j++){
        //sets each value according to the board given
        longboard[i][j] = ExternalBoardSquare(board[i][j]);
    }
   }
   return longboard;
}

/**
 * Returns the shortrange scan centered on the specified robot
 * as a 2-D array of ExternalBoardSquares
 * @param RobotColor rc
 * @return ExternalBoardSquares as a 5x5 array
 */
ExternalBoardSquare** GameBoard::getShortRangeScan(RobotColor rc)
{   
    //locates the given robot's position on the board
    Location point = find(rc);

    //Allocates a 5x5 array
    ExternalBoardSquare** shortboard = new ExternalBoardSquare*[5];
    //Wall Square to be added (if we are out of bounds of the board)
    InternalBoardSquare wallSq;
    wallSq.applySquareType(WALL);

    for(int i = 0; i < 5; i++){
        shortboard[i] = new ExternalBoardSquare[5];
        for(int j = 0; j < 5; j++){
            //identifies the corresponding index (x & y values) on the GameBoard (15x15)
            int board_x = (point.x - 2) + i;
            int board_y = (point.y - 2) + j;

            //checks we are within bounds of the GameBoard
            if(checkBounds(board_x, board_y)){
                shortboard[i][j] = ExternalBoardSquare(board[board_x][board_y]);
            }
            else{
                //if not within bounds, set the BoardSquare as WALL
                shortboard[i][j] = ExternalBoardSquare(wallSq);
            }
        }
    }
    return shortboard;
}

/**
 * Helper method to return the given location (int x, int y)
 * with the given robot color
 * @throws runtime_error if no robot found
 */
Location GameBoard::find(RobotColor rc)
{
    Location p;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            //checks that square contains robot desired
            InternalBoardSquare& sq = getSquare(i, j);
            if((sq.redRobotPresent() && rc == XRED) || (sq.blueRobotPresent() && rc == XBLUE)){
                p.x  = i;
                p.y = j;
                return p;
            }
        }
    }
    //throws error if no robot found, since something must be wrong (should always have both on board)
    throw runtime_error("Robot not found on the board.");
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

/**
 * Helper method to ensure we are still within the bounds of the board
 * @param int x
 * @param int y
 * @return bool true if within bounds, false otherwise
 */
bool GameBoard::checkBounds(int x, int y)
{
    return (x >= 0 && x < row && y >= 0 && y < col);
}
