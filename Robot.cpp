#include "Robot.h"
#include "IRobotAgent.h"
#include "RobotAgent.h"
using namespace std;

/**
 * Default constructor -- creates a red lazyRobot 
 */
Robot::Robot()
{
    //sets robot's color as RED
    color = RED;

    //set's the robot's agent as a LazyRobot
    agent = new lazyRobot();
    
    //set's agent color as our robot's color
    agent->setRobotColor(color);
    
    //adds the agent to the roster
    RobotAgentRoster::getInstance()->add(agent);
}

/**
 * Specific constructor
 * @param RobotColor rc
 */
Robot::Robot(RobotColor rc) : color(rc)
{
    //TODO
}

/**
 * Destructor
 */
Robot::~Robot()
{
    delete agent;
}

/**
 * 
 */
void Robot::update(ObservableData<GameBoard> *data)
{   
    //updates the last recieved data
    lastData = data;
    Event event = data->getEvent();

    if(event == SQUARE_COLOR){
        //handle square color
        // = data->getData().squareColorData;
    }
    else if(event == ROBOT_MOVE){
        //handle robot move
        // = data->getData().robotMoveData;
    }
    else if(event == SCORE_UPDATE){
        //handle score update
        // = data->getData().scoreUpdataData;
    }
    else if(event == SQUARE_TYPE){
        //handle square type
        // = data->getData().squareTypeData;
    }
}

/**
 * For getting the last data from the observable
 * @return ObservableData<GameBoard> lastData 
 * recieved by the GameBoard
 */
ObservableData<GameBoard>* Robot::getLastUpdate()
{
    return lastData;
}

/**
 * Sets the given Robot agent
 * @param IRobotAgent* a
 */
void Robot::setRobotAgent(IRobotAgent* a)
{
    agent = a;

    if(agent){
        //ensures the color is updated correctly
        agent->setRobotColor(color);
    }
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

    //sets the robot color for the agent
    if(agent){
        agent->setRobotColor(col);
    }
}

/**
 * Gets the robot's color
 * @return RobotColor col
 */
Robot::RobotColor Robot::getRobotColor()
{
    return color;
}

