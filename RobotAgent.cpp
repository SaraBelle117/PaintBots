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

    //if we are on a fog square (all the surrounding squares are empty in srs)
    if(srs[2][2].getSquareType() == FOG){
        //next move we will have more visibility on the board
        mr->lrs = true;
    }
    
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
            //the move we planned is now invalid, so clear the moves vector
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
    //if the short range scan is not available, return this move as a safety precaution
    if(!shortboard){
        return (rand() % 2 == 0) ? ROTATELEFT : ROTATERIGHT;
    }

    Direction dir = shortboard[2][2].robotDirection();
    //default value that will be overridden (hopefully)
    RobotMove bestmove = ROTATELEFT;
    //for tracking score with minimum number of visits
    int minVisits = 100;
    
    //access map data (if available)
    for(RobotMove move : {FORWARD, ROTATELEFT, ROTATERIGHT}){
        //adjusts the next direction (based on orientation)
        Direction nextdir = (move == FORWARD) ? dir : rotate(dir, move);
        //gets next position on the board
        Location nextpos = getNextPos(pos, nextdir);

        //skips invalid points
        if(nextpos.x == -1 || nextpos.y == -1 || !isInBounds(nextpos)){
            continue;
        }
        //skips bounndary points
        if(isBoundary(map[nextpos.x][nextpos.y].type) || map[nextpos.x][nextpos.y].type == WALL){
            continue;
        }

        if(map[nextpos.x][nextpos.y].visits < minVisits){
            minVisits = map[nextpos.x][nextpos.y].visits;
            bestmove = move;
        }
    }
    //if minvisits is still 100, no suitable moves found
    if(minVisits == 100){
        return hailMary(dir);
    }
    //returns best move found
    return bestmove;
   
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
    //bug fixing
    return threats;
}

/**
 * Determines move if we have access to long range scan
 * @param ExternalBoardSquare** lrs
 * @return RobotMove 
 */
RobotMove AntiRandom::findPath(ExternalBoardSquare** lrs)
{ 
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
    Direction dir = lrs[position.x][position.y].robotDirection();

    //to hold possible moves
    vector<RobotMove> bestPath;

    for(RobotMove possibleMove : {FORWARD, ROTATERIGHT, ROTATELEFT}){
        //vector to hold possible moves
        vector<RobotMove> tempmoves;
        Location nextpos = position;
        Direction nextdir = dir;

        //simulates making the move on the board
        if(possibleMove == FORWARD){
            nextpos = getNextPos(position, dir);
            nextdir = dir;
        }
        else {
            nextdir = rotate(dir, possibleMove);
            nextpos = getNextPos(position, nextdir);
        }

        //skips invalid moves
        if(!isInBounds(nextpos) || isBoundary(map[nextpos.x][nextpos.y].type)){
            continue;
        }

        //skip points (this indicates we found an invalid getNextPos(...))
        if(nextpos.x == -1 && nextpos.y == -1){
            continue;
        }
        
        //score the pathway 
        int score = 0;
        Location path = nextpos;

        while(isInBounds(path) && !isBoundary(map[path.x][path.y].type) && tempmoves.size() <= 10){
            int visits = map[path.x][path.y].visits;
            //higher scores correspond with lower number of visits
            if(visits == 0){
                //score boost for unvisited squares
                score += 50;
            }
            else{
                //score calculates higher visits scores as increasingly less
                score += 20 / (visits + 1);
            }

            //count number of obstacles nearby
            int penalty = 0;

            //iterates nearby points for possible obstacles
            for(int x = -2; x <= 2; x++){
                for(int y = -2; y <= 2; y++){
                    //skip the same point
                    if(x == 0 && y == 0) continue;
                    Location neighbor = {path.x + x, path.y + y};
                    if(!isInBounds(neighbor)) continue;
                    SquareType neighborType = map[neighbor.x][neighbor.y].type;

                    //calculates distance between barriers
                    int distance = abs(x) + abs(y);
                    if(neighborType == WALL){
                        penalty += (30 - distance);
                    }
                    else if(neighborType == ROCK || neighborType == FOGANDROCK){
                        penalty += (25 - distance);
                    }
                }
            }

            //score updates with the obstacle penalty
            score -= penalty;

            tempmoves.push_back(FORWARD);
            path = getNextPos(path, nextdir);
            if(!isInBounds(path)) break;
        }

        //choose the best score
        if(score > maxScore){
            maxScore = score;
            bestPath = tempmoves;
        }
    } 
    //if valid path was found, update moves queue
    if(!bestPath.empty() && isInBounds(getNextPos(position, dir))){
        move = bestPath[0];
        moves.clear();
        moves.insert(moves.end(), bestPath.begin() + 1, bestPath.end());
    }
    else{
        //if no valid pathways found, fall back on autopilot
        move = autoPilot();
    }
       
    return move;
}