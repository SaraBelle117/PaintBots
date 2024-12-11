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

class AntiRandom : public IRobotAgent 
{
    private:
        string name =  "AntiRandom";
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