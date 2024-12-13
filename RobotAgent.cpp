#include "RobotAgent.h"
//#include "Robot.h"
using namespace std;

//for the static member variable 
RobotAgentRoster* RobotAgentRoster::instance = nullptr;

/**
 * lazyRobot class ~~ Gets the given RobotMoveRequest 
 * for the Lazy Robot: Does not move from the initial 
 * square and fires a paintblob each turn in a random
 * direction 
 * @param ExternalBoardSquare** srs
 * @param ExternalBoardsquare** lrs
 * @return RobotMoveRequest* mr
 */
RobotMoveRequest* LazyRobot::getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs)
{
    RobotMoveRequest* mr = new RobotMoveRequest();
            
    //sets shoot as true (since we will always been shooting a blob)
    mr->shoot = true;
            
    //sets the given robot's color
    mr->robot = color;

    //chooses a random number (0 or 1)
    bool randRotate = rand() % 2;

    //if randRotate = 1, ROTATELEFT
    if(randRotate == 1){
        mr->move = ROTATELEFT;
    }
    else{
    //otherwise, ROTATERIGHT
        mr->move = ROTATERIGHT;
    }

    return mr;
}

/**
 * randomRobot class ~~ gets the given RobotMoveRequest
 * for the Random Robot: moves in a random direction to
 * a legal square and never fires a paintblob
 * @param ExternalBoardSquare** srs (short range scan)
 * @param ExternalBoardSquare** lrs (long range scan)
 */
RobotMoveRequest* RandomRobot::getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs)
{
    RobotMoveRequest* mr = new RobotMoveRequest();

    //randomly chooses to shoot or not shoot 
    mr->shoot = (rand() % 2);
            
    //sets the given robot's color
    mr->robot = color;

    while(true){
        //randomly selects a move 
        RobotMove move = static_cast<RobotMove>(rand() % 4);

        if(move == FORWARD){
            //checks that the next square forward is a valid move on the board
            ExternalBoardSquare sq = srs[1][2];

            //checks that the forward square has no robot present, isn't wall or rock square
            if(sq.getSquareType() != ROCK && sq.getSquareType() != FOGANDROCK &&
             sq.getSquareType() != WALL && !(sq.blueRobotPresent()) && !(sq.redRobotPresent())){
                //sets the valid move
                mr->move = FORWARD;
                return mr;
            } 
        } else {
            //move is not FORWARD, so return the generated move request
            mr->move = move;
            return mr;
        }
    }

}

/**
 * AntiRandom class~~ gets the move for the AntiRandom robot:
 * TODO: Beats the Random robot 8/10 times.
 * @param ExternalBoardSquare** srs (short range scan)
 * @param ExternalBoardSquare** lrs (long range scan)
 * @return RobotMoveRequest* mr
 */
RobotMoveRequest* AntiRandom::getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs)
{
    RobotMoveRequest* mr = new RobotMoveRequest();

    //attempts to shoot a paintblob
    mr->shoot = true;
    mr->robot = color;
    
    //check there are no moves decided already
    if(!moves.empty()){
        //grabs next move from the vector
        mr->move = moves.front();

        //removes the first index (which we just used) from the vector
        moves.erase(moves.begin());

    }
    else if(lrs){
        lastlrs = lrs;
        mr->move = findPath(lrs);
        mr->lrs = false;
    }
    else if(isCorner(srs)){
        mr->move = escapeCorner(srs);
    }
    else{
        mr->move = determineMove(srs);
    }

    return mr;
}

RobotMove AntiRandom::determineMove(ExternalBoardSquare** srs)
{
    Direction dir = srs[2][2].robotDirection();
    SquareType type = srs[2][2].getSquareType();

    //if we are on a square thats a fog, our vision is impaired 
    if(type == FOG || type == FOGANDROCK){
        return ROTATERIGHT;
    }
    
    //sets the Squarecolor 
    SquareColor squarecolor = (color == XRED) ? RED : BLUE;

    ExternalBoardSquare sq;

    //check surrounding squares
    switch(dir){
        case NORTH:
            //checks the square directly above
            sq = srs[1][2];
            if(!isBoundary(sq.getSquareType())){
                //square is not a ROCK, or WALL, and not our color already, so FORWARD is good move
                return FORWARD;
            }
            else{
                //if quadrant 2 is safer than quadrant 1, turn towards that group
                if(checkDangerLevel(srs, QUADRANT2) < checkDangerLevel(srs, QUADRANT1)){
                    return ROTATELEFT;
                }
                else{
                    return ROTATERIGHT;
                }
            }
            break;
        case SOUTH:
            //checks the square directly below
            sq = srs[3][2];
            if(!isBoundary(sq.getSquareType()) && sq.getSquareColor() != squarecolor){
                return FORWARD;
            }
            else{
                //if quadrant 3 is safer than 4, turn towards that group 
                if(checkDangerLevel(srs, QUADRANT3) < checkDangerLevel(srs, QUADRANT4)){
                    return ROTATERIGHT;
                }
                else{
                    return ROTATELEFT;
                }
            }
            break;
        case WEST:
            //checks the square to the left
            sq = srs[2][1];
            if(!isBoundary(sq.getSquareType()) && sq.getSquareColor() != squarecolor){
                return FORWARD;
            }
            else{
                //if quadrant 2 is safer than 3, turn towards that group
                if(checkDangerLevel(srs, QUADRANT2) < checkDangerLevel(srs, QUADRANT3)){
                    return ROTATERIGHT;
                }
                else {
                    return ROTATELEFT;
                }
            }
            break;
        case EAST:
            sq = srs[2][3];
            if(!isBoundary(sq.getSquareType()) && sq.getSquareColor() != squarecolor){
                return FORWARD;
            }
            else{
                //if quadrant 1 is safer than 4, turn towards that group
                if(checkDangerLevel(srs, QUADRANT1) < checkDangerLevel(srs, QUADRANT4)){
                    return ROTATELEFT;
                }
                else{
                    return ROTATERIGHT;
                }
            }
            break;
    }
}

bool AntiRandom::isBoundary(SquareType s)
{
    return (s == ROCK || s == WALL || s == FOGANDROCK);
}

/**
 * Helper method for checking specific groups (for short range scan)
 * @param ExternalBoardSquare** srs
 * @param Group quadrant
 * @return true if group contains a boundary, otherwise false
 */
int AntiRandom::checkDangerLevel(ExternalBoardSquare** srs, Group quadrant)
{
    int threats = 0;

    switch(quadrant){
        case QUADRANT1:
            if(isBoundary(srs[3][0].getSquareType())) threats++;
            if(isBoundary(srs[4][0].getSquareType())) threats++;
            if(isBoundary(srs[3][1].getSquareType())) threats++;
            if(isBoundary(srs[4][1].getSquareType())) threats++;
            return threats;
            break;
        case QUADRANT2:
            if(isBoundary(srs[0][0].getSquareType())) threats++;
            if(isBoundary(srs[0][1].getSquareType())) threats++;
            if(isBoundary(srs[1][0].getSquareType())) threats++;
            if(isBoundary(srs[1][1].getSquareType())) threats++;
            return threats;
            break;
        case QUADRANT3:
            if(isBoundary(srs[0][3].getSquareType())) threats++;
            if(isBoundary(srs[4][0].getSquareType())) threats++;
            if(isBoundary(srs[3][1].getSquareType())) threats++;
            if(isBoundary(srs[4][1].getSquareType())) threats++;
            return threats;
            break;
        case QUADRANT4:
            if(isBoundary(srs[3][3].getSquareType())) threats++;
            if(isBoundary(srs[3][4].getSquareType())) threats++;
            if(isBoundary(srs[4][3].getSquareType())) threats++;
            if(isBoundary(srs[4][4].getSquareType())) threats++;
            return threats;
            break;      
    }
}

/**
 * Checks if we are in a corner of the board
 * (or cornered by rocks)
 * @param ExternalBoardSquare** srs 
 * @return true if in corner, otherwise false
 */
int AntiRandom::isCorner(ExternalBoardSquare** srs)
{
    int blocks = 0;
    //checks if the surrounding squares are blocked
    if(isBoundary(srs[1][2].getSquareType())) blocks++;
    if(isBoundary(srs[3][2].getSquareType())) blocks++;
    if(isBoundary(srs[2][1].getSquareType())) blocks++;
    if(isBoundary(srs[2][3].getSquareType())) blocks++;

    //true if 3 or more blocks are detected (corner found)
    return(blocks >= 2);

}

/**
 * Establishes a corresponding move if we are in a corner square
 * @param ExternalBoardsquare** srs
 */
RobotMove AntiRandom::escapeCorner(ExternalBoardSquare** srs)
{
    //grabs robot's current direction
    Direction dir = srs[2][2].robotDirection();

    //establishes square types of surrounding squares
    SquareType northsq = srs[1][2].getSquareType();
    SquareType southsq = srs[3][2].getSquareType();
    SquareType eastsq = srs[2][3].getSquareType();
    SquareType westsq = srs[2][1].getSquareType();

    /**
     * TODO: Edit so that we use the direction to determine the next move on the board 
     */

    if(!isBoundary(northsq)){
        //set next move as forward
        moves.push_back(FORWARD);
        return dir == NORTH ? FORWARD : ROTATERIGHT;
    }
    else if(!isBoundary(southsq)){
        moves.push_back(FORWARD);
        return dir == SOUTH ? FORWARD: ROTATELEFT;
    }
    else if(!isBoundary(eastsq)){
        moves.push_back(FORWARD);
        return dir == EAST ? FORWARD : ROTATERIGHT;
    }
    else if(!isBoundary(westsq)){
        moves.push_back(FORWARD);
        return dir == WEST ? FORWARD : ROTATELEFT;
    }
    /*
    //found right corner of the board
    if(isBoundary(northsq) && isBoundary(eastsq) && isBoundary(srs[1][1].getSquareType())){
        if(dir == NORTH){
            //next 3 moves should be: ROTATERIGHT, ROTATERIGHT, and FORWARD
            moves.push_back(ROTATERIGHT);
            moves.push_back(FORWARD);
            return ROTATERIGHT;
        }
        else if(dir == SOUTH){
            return FORWARD;
        }
        else if(dir == EAST){
            moves.push_back(FORWARD);
            return ROTATELEFT;
        }
        else if(dir == WEST){
            moves.push_back(FORWARD);
            return ROTATERIGHT;
        }
        //return ROTATERIGHT;
    }
    else{
        return ROTATELEFT;
    } */

}

/**
 * Determines move if we have access to long range scan
 * @param ExternalBoardSquare** lrs
 * @return RobotMove 
 */
RobotMove AntiRandom::findPath(ExternalBoardSquare** lrs)
{   
    //initially, RobotMove is none
    RobotMove move = NONE;
    //for holding the maximum possible score
    int maxScore = -1;

    //locates our robot's position on the board, & identifies position
    Location pos = findRobot(lrs, color);
    Direction dir = lrs[pos.x][pos.y].robotDirection();

    //assigns corresponding square color
    SquareColor squarecolor = (color == XRED) ? RED : BLUE;

    //for tracking possible score
    int score = 0;

    //while we are still on the bounds of the board
    while(pos.x >= 0 && pos.x < 17 && pos.y >= 0 && pos.y < 17){
        SquareType t = lrs[pos.x][pos.y].getSquareType();
        SquareColor sc = lrs[pos.x][pos.y].getSquareColor();

        //stops on boundaries or squares already painted in our color
        if(isBoundary(t) || sc == squarecolor) break;
            
        //add to score for unpainted squares
        if(sc == WHITE) score++;

        //move further in corresponding direction
        pos = getNextPos(pos, dir);
    }
        
        //updates the maximum possible score
    if(score > maxScore){
        maxScore = score;
        move = FORWARD;
    }

    //prioritizing exploring the board if no FORWARD moves found (chooses randomly between directions)
    if(move == NONE){
        move = (rand() % 2 == 0) ? ROTATELEFT : ROTATERIGHT;
    }

    return move;
}

/**
 * Helper method for finding robot on the board
 * @param ExternalBoardSquare** lrs
 * @return Location of the robot on the board
 */
Location AntiRandom::findRobot(ExternalBoardSquare** lrs, RobotColor rc)
{
    //iterates through the board
    for(int i = 0; i < 17; i++){
        for(int j = 0; j < 17; j++){
            ExternalBoardSquare& sq = lrs[i][j];
            if((sq.blueRobotPresent() && rc == XBLUE) ||(sq.redRobotPresent() && rc == XRED)){
                return{i, j};
            }
        }
    }  
    //if robot not found on the board (should not occur)
    return{-1, -1};
}

/**
 * Gets the next position on the board
 * @param Direction dir
 * @return Location of next position 
 */
Location AntiRandom::getNextPos(Location pos, Direction dir)
{
    switch(dir){
        case NORTH:
            return {(pos.x - 1), pos.y};
        case EAST:
            return {pos.x, (pos.y + 1)};
        case SOUTH:
            return {(pos.x + 1), pos.y};
        case WEST:
            return {pos.x, (pos.y - 1)};
    }
    //if no direction (should not occur)
    return pos;
}
