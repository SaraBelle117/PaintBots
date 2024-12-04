#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "ObserverPattern.h"
#include "ExternalBoardSquare.h"
using namespace std;

class IRobotAgent{

    public:
        virtual string getRobotName() = 0;
        virtual string getRobotCreator() = 0;
        virtual RobotMoveRequest* getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs) = 0;
        virtual void setRobotColor(Robot::RobotColor c) = 0;
};

/**
 * LAZY ROBOT -- Does not move from the initial square and fires a
 * paintblob each turn ina random direction
 */
class lazyRobot : public IRobotAgent
{
    private:
        string name = "lazyRobot";
        string robotcreator = "Sara Theriault";

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
         * 
         */
        virtual RobotMoveRequest* getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs)
        {
            RobotMoveRequest* mr;

            //TODO - 

            return mr;
        }

        /**
         * Sets the given robot color
         */
        virtual void setRobotColor(Robot::RobotColor c)
        {

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
         * 
         */
        virtual RobotMoveRequest* getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs)
        {
            RobotMoveRequest* mr;

            //TODO - 

            return mr;
        }

        /**
         * Sets the given robot color
         */
        virtual void setRobotColor(Robot::RobotColor c)
        {
            
        }


};

class RobotAgentRoster
{
    private:
        //for implementing the Singleton pattern
        static RobotAgentRoster* instance;
        vector<IRobotAgent*> roster;

        /**
         * Constructor for RobotAgentRoster
         * that creates an empty roster
         */
        RobotAgentRoster() = default;

    public:

        /**
         * Gets the instance of the given RobotAgentRoster
         * @return instance of the RobotAgentRoster
         */
        static RobotAgentRoster *getInstance()
        {
            if(instance == NULL){
                instance = new RobotAgentRoster();
            }
            return instance;
        }

        /**
         * Adds an IRobotAgent (pointer) to the roster
         * @param IRobotAgent* agent
         */
        void add(IRobotAgent* agent)
        {
            roster.push_back(agent);
        }

        /**
         * Overloaded operator for returning the ith
         * Agent in the roster at the given index
         * @return IRobotAgent at specified index
         */
        IRobotAgent* operator[](int index) const
        {
            //checks that index is valid
            if(index >= 0 && index < roster.size()){
                return roster[index];
            }
            
            //if index is invalid, return null pointer
            return nullptr;
        }

        /**
         * Overlaoded operator for returning the 
         * IRobotAgent that matches the given name
         * @param string name
         * @return IRobotAgent with matching name
         */
        IRobotAgent* operator[](string name)
        {
            for(IRobotAgent* agent : roster){
                if(agent->getRobotName() == name){
                    return agent;
                }
            }
            //if invalid name
            return nullptr;
        }

        /**
         * 
         */

};