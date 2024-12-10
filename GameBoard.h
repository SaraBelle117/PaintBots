#pragma once
#include "ObserverPattern.h"
#include "InternalBoardSquare.h"
#include "ExternalBoardSquare.h"
#include "Config.h"
#include "Robot.h"
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

#define RAND_IN_RANGE(min, max) ((min) + rand() % ((max) - (min) + 1))

class GameBoard : public Observable<GameBoard> {
    private:
        static GameBoard* instance;

        //actual size of the GameBoard (17x17)
        const int rows = 17;
        const int cols = 17;

        //playable size of the GameBoard (15x15)
        const int playable_rows = 15;
        const int playable_cols = 15;

        vector<vector<InternalBoardSquare>> board;
    
        //for tracking fogsquares on the board
        vector<Location> fogsquares;

        Robot blue;
        Robot red;

        //default constructor
        GameBoard();

        //specific constructor
        GameBoard(Config config);

        //for testing purposes
        friend class GameBoardTest;

        //helper methods

        //for blueScore() and redScore()
        int getScore(Robot::RobotColor col);

        //for setting walls on the GameBoard
        void setWalls();

        //for setting rocks on the GameBoard
        void setRocks(Config config);

        //for setting robot positions on the GameBoard
        void setRobots();

        //finds the BoardSquare that contains the given robot
        Location find(Robot::RobotColor rc);

        //identifies the next position (given direction)
        Location getNextPosition(Location point, Direction dir);

        //checks that we are still within the bounds of the board
        bool checkBounds(int x, int y);

        //set fog squares
        void setFogs();

        //notifies square color change
        void notifySquareColorChange(Location pos, SquareColor col);   

        //notifies robot move change
        void notifyRobotMove(const RobotMoveRequest& mr);

        //notifies score update change
        void notifyScoreUpdate(int score);

        //notifies SquareType change
        void notifySquareTypeChange(Location position, SquareType sq);

        //for handling memory for longRangeScan() and shortRangeScan()
        void freeScan(ExternalBoardSquare** list, int size);

        //might only need for testing
        void reset();

    public:
        /**
         * Destructor for the GameBoard -- ensures proper cleanup
         */
        ~GameBoard()
        {
            //clears the observers of the GameBoard
            for(auto* observer : observers){
                delete observer;
            }
            //clears the vector
            observers.clear();

            //resets the Singleton instance (might not be needed)
            instance = nullptr;
        }
        
        /**
         * Notifies the observers about changing game states 
         * for ObservableData<GameBoard>
         * @param GameBoard *data
         */
        virtual void notifyObservers(ObservableData<GameBoard>* data) override
        {   
            for(Observer<GameBoard> *observer : observers){
                observer->update(data);
            }
        }

        Robot::RobotColor winner;
        Config config;

        static GameBoard* getInstance(string password);
        static GameBoard* getInstance(string password, Config config);
        InternalBoardSquare & getSquare(int row, int col);
        bool moveRobot(RobotMoveRequest & mr);
        bool PaintBlobHit(RobotMoveRequest & mr);
        int blueScore();
        int redScore();
        void setSquareColor(int row, int col, SquareColor sc);
        void setRobotPaintColor(Robot::RobotColor robot, SquareColor sc);
        ExternalBoardSquare** getLongRangeScan();
        ExternalBoardSquare** getShortRangeScan(Robot::RobotColor rc);
        //helper methods (written for GameLogic, Part C)
        void randomizeFog();
        bool isGameOver();


};