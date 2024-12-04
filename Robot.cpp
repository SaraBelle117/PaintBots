#include "Robot.h"
using namespace std;

/**
 * Sets the given Robot agent
 * @param IRobotAgent* a
 */
void Robot::setRobotAgent(IRobotAgent* a)
{
    agent = a;
}

/**
 * Returns a pointer to the active robot agent
 * @return IRobotAgent* 
 */
IRobotAgent* Robot::getRobotAgent()
{
    return agent;
}

/**
 * Sets the robot's color 
 * @param RobotColor col
 */
void Robot::setColor(RobotColor col)
{
    color = col;
}

/**
 * Gets the robot's color
 * @return RobotColor col
 */
Robot::RobotColor Robot::getRobotColor()
{
    return color;
}

