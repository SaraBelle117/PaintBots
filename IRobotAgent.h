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

};