#include "RobotAgent.h"
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

    /**
     * TODO: Finish this shiz
     */

    return mr;
}