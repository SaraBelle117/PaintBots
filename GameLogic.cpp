#include "GameLogic.h"
#include "IRobotAgent.h"
#include "Config.h"
#include <iostream>
#include <fstream>
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
 * Destructor for the GameLogic
 * (cleans up resources once GameLogic
 * goes out of scope)
 */
GameLogic::~GameLogic()
{
    delete red;
    delete blue;
    delete gameboard;
}

/**
 * Plays the game PaintBots
 * @param string boardconfig
 * @param string robotconfig
 */
void GameLogic::playGame(string boardconfig, string robotconfig)
{
    //creates the config with the config file
    Config config(boardconfig.c_str());

    //accesses the GameBoard instance
    gameboard = GameBoard::getInstance("xyzzy", config);

    //ensures the robot file is accessed safely
    ifstream robotfile(robotconfig);
    if(!robotfile.is_open()){
        cerr << "Error: could not open robot: " << robotconfig << endl;
        return ;
    }

    string red_strategy_name, blue_strategy_name;

    //sets first line of file as red robot's strategy
    getline(robotfile, red_strategy_name);

    //sets second line of file as blue robot's strategy
    getline(robotfile, blue_strategy_name);
    robotfile.close();

    //update strategies in roster
    RobotAgentRoster* roster = RobotAgentRoster::getInstance();

    IRobotAgent* red_strategy = (*roster)[red_strategy_name];
    IRobotAgent* blue_strategy = (*roster)[blue_strategy_name];

    red = new Robot();
    red->setRobotAgent(red_strategy);
    red->setColor(Robot::RED);

    blue = new Robot();
    blue->setRobotAgent(blue_strategy);
    blue->setColor(Robot::BLUE);
    
    //registers the robots as observers
    gameboard->registerObserver(red);
    gameboard->registerObserver(blue);

    //initializes game state variables
    bool gameover = false;
    Robot* player = red;
    int moves = 0;

    while(!gameover)
    {  
        //fetches short range scan for the robot agent
        ExternalBoardSquare** srs = gameboard->getShortRangeScan(player->getRobotColor());
        ExternalBoardSquare** lrs = nullptr;

        //calls longrange scan if player has enough remaining
        if(player->longrange <= gameboard->config.getLongRangeLimit()){
             lrs = gameboard->getLongRangeScan();
             player->longrange++;
        }

        //fetches move request (lrs is null if not enough calls left)
        RobotMoveRequest& mr = *player->getRobotAgent()->getMove(srs, lrs);

        //apply the move
        gameboard->moveRobot(mr);

        if(pause){
            cout << "Press ENTER to continue." << endl;
            cin.ignore();
        }

        //moves one fog square to another empty square
        gameboard->randomizeFog();

        //switches to the other robot at the end of each move
        player = (player == red) ? blue : red;

        //for tracking # of moves
        moves++;

        //game lasts for 300 moves
        if(moves >= 300) gameover = true;

        //checks game ending events
        gameover = gameboard->isGameOver();
    }

    cout << "GAME OVER" << endl;

    if(gameboard->winner == Robot::RED){
        cout << "RED ROBOT WINS THE GAME!" << endl;
    }
    else{
        cout << "BLUE ROBOT WINS THE GAME!" << endl;
    }
    
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

int main(int argc, char* argv[])
{
    if(argc != 3){
        cerr << "Usage: " << argv[0] << " <boardconfig><robotconfig>" << endl;
        return 1;
    }

    string boardconfig = argv[1];
    string robotconfig = argv[2];
    
    //initializes the game
    GameLogic game;
    
    game.setPause(true);

    game.playGame(boardconfig, robotconfig);

    return 0;
}


