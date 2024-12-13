#include "GameLogic.h"
#include "RobotAgent.h"
#include "PlainDisplay.h"
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
    red_lrs = false;
    blue_lrs = false;
}

/**
 * Destructor for the GameLogic
 * (cleans up resources once GameLogic
 * goes out of scope)
 */
GameLogic::~GameLogic()
{
    //delete gameboard;
}

/**
 * Plays the game PaintBots
 * @param string boardconfig
 * @param string robotconfig
 */
void GameLogic::playGame(string boardconfig, string robotconfig)
{
    printf("\n\n\n\n");
    PlainDisplay::titleScreen();
    printf("\n\n\n\n");

    //waits for user input
    cout << "Press ENTER to play the game." << endl;
    string userinput;
    getline(cin, userinput);

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
    RobotAgentRoster* roster = RobotAgentRoster::getInstance();\

    vector<string> strategies = {red_strategy_name, blue_strategy_name};
    for(const string& strategy : strategies){
        if(strategy == "LazyRobot"){
            roster->add(new LazyRobot());
        }
        else if(strategy == "RandomRobot"){
            roster->add(new RandomRobot());
        }
        else if(strategy == "AntiRandom"){
            roster->add(new AntiRandom());
        }
        else {
            cerr << "Error: Unknown strategy: " << strategy << endl;
            return;
        }
    }

    IRobotAgent* red_strategy = (*roster)[red_strategy_name];
    IRobotAgent* blue_strategy = (*roster)[blue_strategy_name];

    //if red or blue strategy is null, handle error
    if(!red_strategy || !blue_strategy){
        cerr << "Could not read strategy." << endl;
        return;
    }

    red = new Robot();
    red->setRobotAgent(red_strategy);
    red->setColor(RobotColor::XRED);

    blue = new Robot();
    blue->setRobotAgent(blue_strategy);
    blue->setColor(RobotColor::XBLUE);
    
    //registers the robots as observers
    gameboard->registerObserver(red);
    gameboard->registerObserver(blue);

    //initializes game state variables
    bool gameover = false;
    Robot* player = red;
    int moves = 0;

    while(!gameover && moves < 300)
    {  
        //for tracking # of moves
        moves++;

        //fetches short range scan for the robot agent
        ExternalBoardSquare** srs = gameboard->getShortRangeScan(player->getRobotColor());
        ExternalBoardSquare** lrs = nullptr;

        //if the player requested lrs on their last move (and has enough calls left)
        if(player == red && red_lrs  && player->longrange <= gameboard->config.getLongRangeLimit()){
            //fetches the long range scan
            lrs = gameboard->getLongRangeScan();
            //increments # of long range scans
            player->longrange++;
            //resets variable
            red_lrs = false;
        }

        if(player == blue && blue_lrs && player->longrange <= gameboard->config.getLongRangeLimit()){
            //fetches long range scan
            lrs = gameboard->getLongRangeScan();
            //increments # of scans
            player->longrange++;
            blue_lrs = false;
        }

        //fetches move request (lrs is null if not enough calls left)
        RobotMoveRequest& mr = *player->getRobotAgent()->getMove(srs, lrs);

        //checks if the player requested a long range scan (in the previous move)
        if(mr.lrs){
            if(player == red){
                red_lrs = true;
            }
            else{
                blue_lrs = true;
            }
        }

        //apply the move & and check game ending events
        gameover = gameboard->moveRobot(mr);

        //checks game ending events
        gameover = gameboard->isGameOver();

        //pauses the game (until user provides input)
        if(pause){
            cout << "Press ENTER to continue." << endl;
            string userinput;
            getline(cin, userinput);
        }

        //moves one fog square to another empty square
        gameboard->randomizeFog();

        //switches to the other robot at the end of each move
        player = (player == red) ? blue : red;
    }

    string winner;
    string winningcolor;

    if(gameboard->winner == RobotColor::XRED){
        winningcolor += PlainDisplay::REDBOLD;
        winner += "RED";
    }
    else if(gameboard->winner == RobotColor::XBLUE){
        winningcolor += PlainDisplay::BLUEBOLD;
        winner += "BLUE";
    }
    else {
        winner += "NOBODY.... (aka, something went quite wrong).";
    }

    cout << winningcolor <<  "GAME OVER" << endl;
    cout << "THE " << winner << " ROBOT WINS THE GAME!" << PlainDisplay::RESET <<endl;
    printf("\n\n");
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


