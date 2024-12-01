#include "GameBoard.h"
#include "PlainDisplay.h"
#include <iostream>
using namespace std;

//initializes the gameboard to a null pointer
GameBoard* GameBoard::instance = nullptr;

/**
 * Constructs the GameBoard with the default configuration values
 */
GameBoard::GameBoard() : board(rows, vector<InternalBoardSquare>(cols))
{
    //populates boarder of the GameBoard with WALL BoardSquares
    setWalls();

    //populates rocks for the GameBoard using config
    setRocks(config);

    //sets robots on the GameBoard
    setRobots();

    //sets the fog squares on the GameBoard
    randomizeFogs();
}

/**
 * Constructs a GameBoard using the specific configuration given
 * @param Config 
 */
GameBoard::GameBoard(Config config): board(rows, vector<InternalBoardSquare>(cols))
{
    //populates boarder of the GameBoard with WALL BoardSquares
    setWalls();

    //populates rocks for the GameBoard using config
    setRocks(config);

    //sets robots on the GameBoard
    setRobots();

    //sets the fog squares on the GameBoard
    randomizeFogs();
}

/**
 * Notifies observers about the SquareColor Change
 * @param int x
 * @param int y
 * @param SquareColor col
 */
void GameBoard::notifySquareColorChange(Location pos, SquareColor col)
{   
    //creates the union data
    ObservableData<GameBoard>::Data data;
    data.SquareColorData = {pos, col};

    //creates the ObservableData type
    ObservableData<GameBoard> event(SQUARE_COLOR, data);

    //notifies the observers
    notifyObservers(&event);
}

/**
 * Notifies the observers about the Robot move change
 * @param Robot rb
 * @param Direction dir
 */
void GameBoard::notifyRobotMove(const RobotMoveRequest& mr)
{
    //creates the union data
    ObservableData<GameBoard>:: Data data;
    data.robotMoveData = {mr};

    //creates the ObservableData type
    ObservableData<GameBoard> event(ROBOT_MOVE, data);

    //notifies the observers
    notifyObservers(&event);
}

/**
 * Notifies the observers about the score change
 * @param int score
 */
void GameBoard::notifyScoreUpdate(int score)
{
    //creates the union data
    ObservableData<GameBoard>:: Data data;
    data.scoreUpdateData = {score};

    //creates the ObservableData type
    ObservableData<GameBoard> event(SCORE_UPDATE, data);

    //notifies the observers
    notifyObservers(&event);
}

/**
 * Notifies the observers about the SquareType change
 * @param int location
 * @param SquareType 
 */
void GameBoard::notifySquareTypeChange(Location position, SquareType sq)
{
    //creates the union data
    ObservableData<GameBoard>::Data data;
    data.squareTypeData = {position, sq};

    //creates the ObservableData type
    ObservableData<GameBoard> event(SQUARE_TYPE, data);

    //notifies the observers
    notifyObservers(&event);
}

/**
 * Frees the memory used for LongRangeScan() and ShortRangeScan()
 * @param ExternalBoardSquare** list
 * @param int size of the given list (15x15 for long, 5x5 for short)
 */
void GameBoard::freeScan(ExternalBoardSquare** list, int size)
{  
    //checks that the list is not null
    if(list){
        for(int i = 0; i < size; i++){
            //deletes the element in the list
            delete[] list[i];
        }
        //deletes the list
        delete[] list;
    }
}

/***
 * Resets the board to it's original state
 */
void GameBoard::reset()
{
    //resets the board
    board.clear();
    board.resize(rows, vector<InternalBoardSquare>(cols));

    //reinitialize the game pieces
    setWalls();
    setRocks(config);
    setRobots();
    randomizeFogs();
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

        //registers display as an observer
        PlainDisplay* display = new PlainDisplay();
        instance->registerObserver(display);
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
        //registers display as an observer
        PlainDisplay* display = new PlainDisplay();
        instance->registerObserver(display);
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
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            //if boundary of the grid, set SquareType as WALL
            if(i == 0 || i == (rows - 1) || j == 0 || j == (cols - 1)){
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
        //fixes issues with infinite loops
        int attempts = 0;
        //generates a rand num until it finds an empty square (with no blue or red robot present)
        while(board[x][y].getSquareType() != EMPTY || board[x][y].redRobotPresent() || board[x][y].blueRobotPresent()){
            //ensures x & y is a random number between 1 - 13
            x = RAND_IN_RANGE(1, 15);
            y = RAND_IN_RANGE(1, 15); 

            attempts++;
            if(attempts > 100){
                throw runtime_error("Too many rocks to place on the board, double check config");
            }
        }
        //sets SquareType at x, y
        board[x][y].applySquareType(ROCK);
    }  
}

/**
 * Sets the fog squares for the game (also used to update fog squares randomly)
 */
void GameBoard::randomizeFogs()
{
    //chooses a random value between the bounds (given by the config)
    int numFogs = RAND_IN_RANGE(config.getFogLowerBound(), config.getFogUpperBound());

    //adds that number of fog squares to valid points on the board
    for(int i = 0; i < numFogs; i++){
        //initialize to zero 
        Location p;
        p.x = 0, p.y = 0;

        //fixes infinite loop issue
        int attempts = 0;

        //generates a rand num until it finds a valid square
        while(board[p.x][p.y].getSquareType() == WALL || board[p.x][p.y].redRobotPresent() || board[p.x][p.y].blueRobotPresent()){
            //ensures x & y is a random number between 1 - 13
            p.x = RAND_IN_RANGE(1, 15);
            p.y = RAND_IN_RANGE(1, 15);

            attempts++;
            if(attempts > 1000){
                throw runtime_error("Unable to add fog squares");
            }
        }
        //sets fog square at valid point found (edited to allow rock and fog to share a square)
        if(board[p.x][p.y].getSquareType() == ROCK){
            board[p.x][p.y].applySquareType(FOGANDROCK);
            notifySquareTypeChange(p, FOGANDROCK);
        }
        else{
            board[p.x][p.y].applySquareType(FOG);
            notifySquareTypeChange(p, FOG);
        }

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
            x = RAND_IN_RANGE(1, 15);
            y = RAND_IN_RANGE(1, 15);
        }
        if(rc == XRED){
            board[x][y].applyRedRobotPresent(true);
            setRobotPaintColor(XRED, RED);
        }
        else{
            board[x][y].applyBlueRobotPresent(true);
            setRobotPaintColor(XBLUE, BLUE);
        }
    }
}

/**
 * Gets the BoadSquare at the indicated index. 
 * @param int row
 * @param int col
 * @return InternalBoardSquare at board[row][col]
 * @throws out_of_range expection if given an invalid square index
 */
InternalBoardSquare & GameBoard::getSquare(int row, int col)
{
    //ensures the row and col are valid values
    if(row >= 0 && col >= 0 && row < rows && col < cols){
        return board[row][col];
    }
    else{
        //throws error if row and col are now valid
        throw out_of_range("Invalid square index.");
    }
}

/**
 * Performs the requested move on the designated robot
 * @param RobotMoveRequest & mr
 * @return bool (true if successful, TRUE (for Part B) otherwise)
 */
bool GameBoard::moveRobot(RobotMoveRequest & mr)
{
    //identifies the given robots position on the board
    Location pos = find(mr.robot);

    if(mr.move == ROTATELEFT || mr.move == ROTATERIGHT){
        Direction newDir;
        switch(board[pos.x][pos.y].robotDirection()){
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
        //applies the new direction
         board[pos.x][pos.y].applyRobotDirection(newDir);
    }
    else if(mr.move == FORWARD){
        //sets the new position of the Robot
        Location newPos = getNextPosition(pos, board[pos.x][pos.y].robotDirection());

        //sets the old square (the one we are moving from) as the Robot's color
        if(mr.robot == XRED){
            board[pos.x][pos.y].applyRedRobotPresent(false);
            board[newPos.x][newPos.y].applyRedRobotPresent(true);
            setSquareColor(pos.x, pos.y, red.paintcolor);
        }
        else{
            board[pos.x][pos.y].applyBlueRobotPresent(false);
            board[newPos.x][newPos.y].applyBlueRobotPresent(true);
            setSquareColor(pos.x, pos.y, blue.paintcolor);
        }
    }
    //shoots a paintblob
    if(mr.shoot){
        PaintBlobHit(mr);
    }
    //notifies the observers about the successful move made on the GameBoard
    notifyRobotMove(mr);

    return true;
}

/**
 * Indicates if the PaintBlob (of the given robot) hits the
 * other or not
 * @param RobotMoveRequest & mr
 * @return bool (true if successful hit, otherwise false)
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
                //notifies Observers of SquareColor Change
                notifySquareColorChange(pos, RED);
            } 
            if(mr.robot == XBLUE){
                blue.paintblobs++;
                setRobotPaintColor(mr.robot, BLUE);
                //notifies Observers of SquareColor Change
                notifySquareColorChange(pos, BLUE);
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
    //sets the RobotColor (to the corresponding SquareColor)
    SquareColor color;
    if(col == XRED){
        color = RED;
    }
    else{
        color = BLUE;
    }

    int score = 0;

    //iterates through the playable area of the board
    for(int i = 1; i <= playable_rows; i++){
        for(int j = 1; j <= playable_cols; j++){
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
 * @throws out_of_range exception
 */
void GameBoard::setSquareColor(int x, int y, SquareColor sc)
{
    //ensures the row and col are valid values
    if(x >= 1 && y >= 1 && x <= playable_rows && y <= playable_cols){
        board[x][y].applySquareColor(sc);
    }
    else{
        //throws error if row and col are now valid
        throw out_of_range("Invalid square index.");
    }
    //sets the point so we can send it to notify the observers
    Location point = {x, y};

    //updates the observers
    notifySquareColorChange(point, sc);
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
    ExternalBoardSquare** longboard = new ExternalBoardSquare*[playable_rows];

    for(int i = 0; i < playable_rows; i++){
        //Allocates each row as an array of ExternalBoardSquares 
        longboard[i] = new ExternalBoardSquare[playable_cols];
        for(int j = 0; j < playable_cols; j++){
            //sets each value according to the board given
            longboard[i][j] = ExternalBoardSquare(board[i + 1][j + 1]);
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

    bool fogSquare = false;
    InternalBoardSquare checkFog = getSquare(point.x, point.y);
    //checks if the square is a fog square
    if(checkFog.getSquareType()== FOG){
        fogSquare = true;
    }

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
            if(checkBounds(board_x, board_y) && !fogSquare){
                shortboard[i][j] = ExternalBoardSquare(board[board_x][board_y]);
            }
            else if(!fogSquare){
                //if not within bounds, set the BoardSquare as WALL
                shortboard[i][j] = ExternalBoardSquare(wallSq);
            }
            else{
                //if we are a fog square, all squares should be empty (unless center)
                InternalBoardSquare empty;
                empty.applySquareType(EMPTY);
                shortboard[i][j] = ExternalBoardSquare(empty);
            }
        }
    }
    //if the robot is on a Fog square, then the center square should be a fog square
    if(fogSquare){
        InternalBoardSquare fog;
        fog.applySquareType(FOG);
        shortboard[2][2] = ExternalBoardSquare(fog);
    }
    return shortboard;
}

/**
 * Helper method to return the given location (int x, int y)
 * with the given robot color
 * @param RobotColor rc
 * @return Location point
 * @throws runtime_error if no robot found
 */
Location GameBoard::find(RobotColor rc)
{
    Location p;

    //iterates through the board until the given robot is found
    for(int i = 0; i < playable_rows; i++){
        for(int j = 0; j < playable_cols; j++){
            //checks that square contains robot desired
            InternalBoardSquare& sq = getSquare(i, j);

            //finds the given robot, and returns the point on the GameBoard
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
 * @param Location point (current)
 * @param Direction dir
 * @return Location of the next point on the board (or the same point
 * if the point is invalid)
 */
Location GameBoard::getNextPosition(Location point, Direction dir){
    switch(dir){
        case NORTH: //move up
            point.y--; 
            return point;
        case EAST:  //move right
            point.x++;
            return point;
        case SOUTH: //move down
            point.y++;
            return point;
        case WEST: //move left
            point.x--;
            return point;
    }
    //if the direction is invalid, just return the same point (this is a placeholder for future logic
    //since in Part B, the robotMove() function must always return true.
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
    return (x >= 0 && x < playable_rows && y >= 0 && y < playable_cols);
}
