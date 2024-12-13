#include "Robot.h"
#include "RobotAgent.h"
using namespace std;

/**
 * Default constructor -- creates a red lazyRobot 
 */
Robot::Robot() : color(XRED), lastData(nullptr), paintblobs(0), longrange(0)
{   
    //sets robot agent
    agent = new LazyRobot();

    //set's agent color as our robot's color
    agent->setRobotColor(color);
    
    //adds the agent to the roster
    RobotAgentRoster::getInstance()->add(agent);
}

/**
 * Destructor (frees memory)
 */
Robot::~Robot()
{
    delete lastData;
}

/**
 * updates the Robot on game state changes (from GameBoard)
 * @param Observable<Data> *data
 */
void Robot::update(ObservableData<GameBoard> *data)
{   
    //updates the last recieved data
    lastData = data;
    //fetches the event type
    Event event = data->getEvent();

    if(data->getEvent() == ROBOT_MOVE){
        //ensures we are accessing a valid agent 
        if(agent){
            auto robotmove = data->getData().robot_move;
            //updates the robot's new position on the board 
            agent->getRobotMoveUpdate(robotmove.position, robotmove.color);
        }
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
RobotColor Robot::getRobotColor()
{
    return color;
}