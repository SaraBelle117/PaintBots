#pragma once
#include "IRobotAgent.h"
#include <cstdlib>
using namespace std;

/**
 * LAZY ROBOT -- Does not move from the initial square and fires a
 * paintblob each turn in a random direction
 */
class lazyRobot : public IRobotAgent
{
    private:
        string name = "lazyRobot";
        string robotcreator = "Sara Theriault";
        Robot::RobotColor color;

    public:
        
        /**
         * Returns the name of the given robot
         * @return string name
         */
        virtual string getRobotName()
        {
            return name;
        }

        /**
         * Returns the name of the given robot creator
         * @return string name
         */
        virtual string getRobotCreator()
        {
            return robotcreator;
        }
        
        /**
         * Gets the given RobotMoveRequest for the Lazy Robot:
         * Does not move from the initial square and fires a 
         * paintblob each turn in a random direction 
         * @param ExternalBoardSquare** srs
         * @param ExternalBoardsquare** lrs
         * @return RobotMoveRequest* mr
         */
        virtual RobotMoveRequest* getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs)
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
         * Sets the given robot color
         * @param RobotColor c to set 
         */
        virtual void setRobotColor(Robot::RobotColor c)
        {
            color = c;
        }

};


/**
 * RANDOM ROBOT -- Moves in a random direction to a legal square
 *  (not a rock or wall, or another robot) and never fires.
 */
class randomRobot : public IRobotAgent{
    private:
        string name = "randomRobot";
        string robotcreator = "Sara Theriault";
        Robot::RobotColor color;

    public:
        /**
         * Returns the name of the given robot
         */
        virtual string getRobotName()
        {
            return name;
        }

        /**
         * Returns the name of the given robot creator
         * @return string name
         */
        virtual string getRobotCreator()
        {
            return robotcreator;
        }

        /**
         * Gets the given RobotMoveRequest for the Random Robot:
         * Moves in a random direction to a legal square and never
         * fires a PaintBlob.
         * @param ExternalBoardSquare** srs
         * @param ExternalBoardsquare** lrs
         * @return RobotMoveRequest* mr
         */
        virtual RobotMoveRequest* getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs)
        {
            RobotMoveRequest* mr = new RobotMoveRequest();

            //sets shoot as false, since we will never fire a PaintBlob
            mr->shoot = false;
            
            //sets the given robot's color
            mr->robot = color;

            //randomly selects a move 
            RobotMove move = static_cast<RobotMove>(rand() % 4);

            if(move == FORWARD){
                //checks that the next square forward is a valid move on the board
                ExternalBoardSquare sq = srs[1][2];

                //checks that the forward square has no robot present, isn't wall or rock square
                if(sq.getSquareType() != ROCK && sq.getSquareType() != FOGANDROCK && sq.getSquareType() 
                    && !(sq.blueRobotPresent()) && !(sq.redRobotPresent())){
                    //sets the valid move
                    mr->move = FORWARD;
                }
                else{
                    do{
                        //generates a random move again
                        move = static_cast<RobotMove>(rand() % 4);

                        //finds a valid move (not FORWARD)
                    } while(move == FORWARD);

                    //sets the valid move
                    mr->move = move;
                }
            }
            else{
                //move is not FORWARD, so return the generated move request
                mr->move = move;
            }

            return mr;
        }

        /**
         * Sets the given robot color
         * @param RobotColor c (color to set)
         */
        virtual void setRobotColor(Robot::RobotColor c)
        {
            color = c;
        }


};

class AntiRandom : public IRobotAgent 
{
    private:
        string name =  "AntiRandom";
        string robotcreator = "Sara Theriault";
        Robot::RobotColor color;

    public: 

        /**
         * Returns the name of the given robot
         * @return string name
         */
        virtual string getRobotName()
        {
            return name;
        }

        /**
         * Returns the name of the given robot creator
         * @return string name
         */
        virtual string getRobotCreator()
        {
            return robotcreator;
        }

        /**
         * Sets the given robot color
         * @param RobotColor c to set
         */
        virtual void setRobotColor(Robot::RobotColor c)
        {
            color = c;
        }

        /**
         * Gets the given RobotMoveRequest for the AntiRandom robot:
         * TODO: BEATS THE RANDOM ROBOT 8/10 TIMES
         * @param ExternalBoardSquare** srs
         * @param ExternalBoardSquare** lrs
         * @return RobotMoveRequest* mr
         */
        virtual RobotMoveRequest* getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs)
        {
            RobotMoveRequest* mr = new RobotMoveRequest();

            //random robot never attemps shooting, so we will
            mr->shoot = true;

            mr->robot = color;

            return mr;
        }


};