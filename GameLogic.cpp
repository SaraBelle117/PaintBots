#include "GameLogic.h"
#include "IRobotAgent.h"
using namespace std;

/**
 * Constructs a new game - sets up the internal state
 * (initializes to null)
) */
GameLogic::GameLogic() 
{
    gameboard = nullptr;
    red = nullptr;
    blue = nullptr;
    pause = false;
}

/**
 * Plays the game PaintBots
 * @param string boardconfig
 * @param string robotconfig
 */
void GameLogic::playGame(string boardconfig, string robotconfig)
{
    //TODO
}

/**
 * Pauses the game after a move for each Robot
 * (if enabled)
 * @param bool pausemode
 */
void GameLogic::setPause(bool pausemode)
{
    pause = pausemode;
}

//sets the instance before main is called
RobotAgentRoster* RobotAgentRoster::instance = nullptr;

//TODO, FIXME: this will need to have 2 paramters
int main()
{
    return 0;
}


