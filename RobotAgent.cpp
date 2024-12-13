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

    //randomly selects a move (between rotateleft and rotateright)
    mr->move = (rand() % 2 == 0) ? ROTATELEFT : ROTATERIGHT;

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

    //updates our short range scan 
    updateShortRangeScan(srs);

    //always to do a long range scan
    mr->lrs = true;
    
    //check there are no moves decided already
    if(!moves.empty()){
        //grabs next move from the vector
        RobotMove potentialMove = moves.front();
        moves.erase(moves.begin());

        Location nextPos = getNextPos(pos, rotate(srs[2][2].robotDirection(), potentialMove));

        if(isInBounds(nextPos) && !isBoundary(map[nextPos.x][nextPos.y].type)){
            mr->move = potentialMove;
        }
        else{
            moves.clear();
            if(lrs){
                mr->move = findPath(lrs);
            }
            else{
                mr->move = autoPilot();
            }
        }
    }
    else if(lrs){
        mr->move = findPath(lrs);
        mr->lrs = false;
    }
    else {
        mr->move = autoPilot();
        //attempt to do a better move next time...
        mr->lrs = true;
    }

    return mr;
}

/**
 * The "auto" move for the AntiRandom Robot
 * Only triggered in certain events, and when
 * we do not have access to the full board
 */
RobotMove AntiRandom::autoPilot()
{
    cout << "Autopiloting............" << endl;
    //if the short range scan is not available, return this move as a safety precaution
    if(!shortboard){
        return ROTATELEFT;
    }

    //sets the Squarecolor (corresponding to our robot's color)
    //SquareColor squarecolor = (color == XRED) ? RED : BLUE;

    Direction dir = shortboard[2][2].robotDirection();
    //SquareType type = shortboard[2][2].getSquareType();
    
    //access map data (if available)
    for(RobotMove move : {FORWARD, ROTATELEFT, ROTATERIGHT}){
        Location nextpos = getNextPos(pos, dir);

        if(move != FORWARD){
            dir = rotate(shortboard[2][2].robotDirection(), move);
        }

        //skips invalid points
        if(nextpos.x == -1 && nextpos.y == -1){
            continue;
        }

        if(isBoundary(map[nextpos.x][nextpos.y].type) || map[nextpos.x][nextpos.y].type == WALL){
            continue;
        }

        //prioritizes squares we have not yet visited
        if(map[nextpos.x][nextpos.y].marked){
            continue;
        }
        //mark square as visited
        map[nextpos.x][nextpos.y].marked = true;
        return move;
    }

    //if no valid moves, throw a hail mary
    return hailMary(dir);
   
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
 * Determines move if we have access to long range scan
 * @param ExternalBoardSquare** lrs
 * @return RobotMove 
 */
RobotMove AntiRandom::findPath(ExternalBoardSquare** lrs)
{ 
    cout << "Finding path............" << endl;
    //updates our map
    updateMap(lrs);

    //initially, RobotMove is none
    RobotMove move = NONE;

    //for holding the maximum possible score
    int maxScore = -1;

    //locates our robot's position on the board, & identifies position
    Location position = findRobot(lrs, color);

    if(!isInBounds(position)){
        //if position could not be verified, default to autopilot 
        return autoPilot();
    }
    //update our map
    map[position.x][position.y].marked = true;

    Direction dir = lrs[position.x][position.y].robotDirection();

    //to hold possible moves
    vector<RobotMove> bestPath;

    //assigns corresponding square color
    //SquareColor squarecolor = (color == XRED) ? RED : BLUE;

    for(RobotMove possibleMove : {FORWARD, ROTATELEFT, ROTATERIGHT}){
        //vector to hold possible moves
        vector<RobotMove> tempmoves;
        Location nextpos = position;
        Direction nextdir = dir;

        //simulates making the move on the board
        if(possibleMove == FORWARD){
            nextpos = getNextPos(position, dir);
        }
        else {
            nextdir = rotate(dir, possibleMove);
        }

        //skips invalid moves
        if(!isInBounds(nextpos) || isBoundary(map[nextpos.x][nextpos.y].type)){
            continue;
        }

        //skip points (this indicates we found an invalid getNextPos(...))
        if(nextpos.x == -1 && nextpos.y == -1){
            continue;
        }

        //add to tempmoves
        tempmoves.push_back(possibleMove);
        
        //score the pathway 
        int score = 0;
        Location path = nextpos;

        while(isInBounds(path) && !isBoundary(map[path.x][path.y].type)){
            //prvents the number of moves we can save in a row 
            if(tempmoves.size() > 30){
                break;
            }
            if(!map[path.x][path.y].marked){
                //bonus for unexplored squares
                score += 10;
            }
            tempmoves.push_back(FORWARD);
            path = getNextPos(path, nextdir);
        }

        //choose the best score
        if(score > maxScore){
            maxScore = score;
            bestPath = tempmoves;
        }
    } 
    //if valid path was found, update moves queue
    if(!bestPath.empty()){
        move = bestPath[0];
        moves.insert(moves.end(), bestPath.begin() + 1, bestPath.end());
    }
    else{
        //if no valid pathways found, fall back on autopile
        move = autoPilot();
    }
       
    return move;
}