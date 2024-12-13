#pragma once
#include "IRobotAgent.h"
#include <cstdlib>
using namespace std;

/**
 * LAZY ROBOT -- Does not move from the initial square and fires a
 * paintblob each turn in a random direction
 */
class LazyRobot : public IRobotAgent
{
    private:
        string name = "LazyRobot";
        string robotcreator = "Sara Theriault";
        RobotColor color;

    public:

        //implemented in .cpp file 
        virtual RobotMoveRequest* getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs); 
        
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
        virtual void setRobotColor(RobotColor c)
        {
            color = c;
        }

};


/**
 * RANDOM ROBOT -- Moves in a random direction to a legal square
 *  (not a rock or wall, or another robot) and never fires.
 */
class RandomRobot : public IRobotAgent{
    private:
        string name = "RandomRobot";
        string robotcreator = "Sara Theriault";
        RobotColor color;

    public:
        //implemented in .cpp file
        virtual RobotMoveRequest* getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs);

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
         * @param RobotColor c (color to set)
         */
        virtual void setRobotColor(RobotColor c)
        {
            color = c;
        }


};
//class Robot;
class AntiRandom : public IRobotAgent 
{
    private:
        string name =  "AntiRandom";
        string robotcreator = "Sara Theriault";
        RobotColor color;
        ExternalBoardSquare** lastlrs;
        vector<RobotMove> moves;

        enum Group {QUADRANT1, QUADRANT2, QUADRANT3, QUADRANT4};

    public:

        //implemented in .cpp file
        virtual RobotMoveRequest* getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs); 
        
        //helps determine move on the board 
        RobotMove determineMove(ExternalBoardSquare** srs);

        //helper method, implemented in .cpp file
        bool isBoundary(SquareType);

        //helper method, implemented in .cpp file
        int checkDangerLevel(ExternalBoardSquare** srs, Group quadrant);

        //helper method to check for corners
        int isCorner(ExternalBoardSquare** srs);

        //establishes move if we are in a corner square
        RobotMove escapeCorner(ExternalBoardSquare** srs);

        //helper method for finding path using long range scan
        RobotMove findPath(ExternalBoardSquare** lrs);

        //helper method for finding the next position
        Location getNextPos(Location pos, Direction dir);

        //helper method to find robot on the board using long range scan
        Location findRobot(ExternalBoardSquare** lrs, RobotColor rc);

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
        virtual void setRobotColor(RobotColor c)
        {
            color = c;
        }

};