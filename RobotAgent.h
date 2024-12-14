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
        Location pos;
        Location enemypos;

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

        /**
         * Updates the robot on the most recent robot
         * moves on the board
         * @param Location position
         * @param RobotColor color
         */
        virtual void getRobotMoveUpdate(Location position, RobotColor col)
        {
            if(col == color){
                pos = position;
            }
            else{
                enemypos = position;
            }
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
        Location pos;
        Location enemypos;

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

        /**
         * Updates the robot on the most recent robot
         * moves on the board
         * @param Location position
         * @param RobotColor color
         */
        virtual void getRobotMoveUpdate(Location position, RobotColor col)
        {
            if(col == color){
                pos = position;
            }
            else{
                enemypos = position;
            }
        }

};

/**
 * ANTI RANDOM -- Beats the RandomRobot 8/10 times :) 
 */
class AntiRandom : public IRobotAgent 
{
    enum Group {QUADRANT1, QUADRANT2, QUADRANT3, QUADRANT4};

    struct Info{
        SquareType type;
        Direction dir;
        //bool marked;
        int visits;

        Info(SquareType t = EMPTY, Direction d = NORTH, int v = 0) 
        : type(t), dir(d), visits(v) {}
    };

    private:
        string name =  "AntiRandom";
        string robotcreator = "Sara Theriault";
        RobotColor color;
        vector<RobotMove> moves;
        vector<vector<Info>> map;
        ExternalBoardSquare** shortboard;
        Location pos;
        Location enemypos;
        bool enemyfound;
        bool found;

        /**
         * Updates the map of the board
         * @param ExternalBoardSquare** lrs
         */
        void updateMap(ExternalBoardSquare** lrs)
        {
            //iterate through the board, updating as needed
            for(int i = 0; i < 17; i++){
                for(int j = 0; j < 17; j++){
                    //updates map type & direction data
                    map[i][j].type = lrs[i][j].getSquareType();
                    map[i][j].dir = lrs[i][j].robotDirection();
                    //increment number of visits (if position is recognized as this point)
                    if(found && pos.x == i && pos.y == j){
                        map[i][j].visits++;
                    }
                }
            }
        }

    public:
        //constructor
        AntiRandom() : shortboard(nullptr), enemyfound(false), found(false) 
        {
            map.resize(17, vector<Info>(17, {EMPTY, NORTH, false}));
        }

        //implemented in .cpp file
        virtual RobotMoveRequest* getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs); 
        
        //helps determine move on the board 
        RobotMove autoPilot();

        //helper method, implemented in .cpp file
        int checkDangerLevel(ExternalBoardSquare** srs, Group quadrant);

        //helper method for finding path using long range scan
        RobotMove findPath(ExternalBoardSquare** lrs);

        /**
         * Helper method for finding a pathway on the board
         * @param Direction dir
         * @param RobotMove rb
         * @return Direction in the direction of rotation
         */
        Direction rotate(Direction dir, RobotMove mr){
            if(mr == ROTATERIGHT){
                switch(dir){
                    case NORTH: return EAST;
                    case EAST: return SOUTH;
                    case SOUTH: return WEST;
                    case WEST: return NORTH;
                }
            }
            else if(mr == ROTATELEFT){
                switch(dir){
                    case NORTH: return WEST;
                    case WEST: return SOUTH;
                    case SOUTH: return EAST;
                    case EAST: return NORTH;
                }
            }
            //if not rotate left or right
            return dir;
        }

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

        /**
         * Updates the robot on the most recent robot
         * moves on the board
         * @param Location position
         * @param RobotColor color
         */
        virtual void getRobotMoveUpdate(Location position, RobotColor col)
        {
            if(col == color){
                pos = position;
                found = true;
            }
            else{
                enemypos = position;
                enemyfound = true;
            }
        }

        /**
         * Helper method for finding robot on the board
         * @param ExternalBoardSquare** lrs
         * @return Location of the robot on the board
         */
        Location findRobot(ExternalBoardSquare** lrs, RobotColor rc)
        {
            //iterates through the board
            for(int i = 0; i < 17; i++){
                for(int j = 0; j < 17; j++){
                    ExternalBoardSquare& sq = lrs[i][j];
                    if((sq.blueRobotPresent() && rc == XBLUE) ||(sq.redRobotPresent() && rc == XRED)){
                        return{i, j};
                    }
                }
            }  
            //if robot not found on the board (should not occur)
            return{-1, -1};
        }
        /**
         * Gets the next position on the board
         * @param Direction dir
         * @return Location of the next position
         */
        Location getNextPos(Location position, Direction dir)
        {
            Location next = position;
            switch(dir){
                case NORTH:
                    next = {(position.x - 1), position.y};
                    break;
                case EAST:
                    next = {pos.x, (pos.y + 1)};
                    break;
                case SOUTH:
                    next = {(pos.x + 1), pos.y};
                    break;
                case WEST:
                    next = {pos.x, (pos.y - 1)};
                    break;
            }
            //if next is in bounds, we return next, otherwise we return invalid index 
            if(isInBounds(next)){
                return next;
            }
            else{
                return {-1, -1};
            }
        }

        /**
         * Checks if the squaretype is a boundary type
         * @param SquareType s
         * @return true if boundary, otherwise false
         */
        bool isBoundary(SquareType s)
        {
            return (s == ROCK || s == WALL || s == FOGANDROCK);
        }

        /**
         * Checks if we are in a corner of the board
         * (or cornered by rocks)
         * @param ExternalBoardSquare** srs 
         * @return true if in corner, otherwise false
         */
        int isCorner(ExternalBoardSquare** srs)
        {
            int blocks = 0;
            //checks if the surrounding squares are blocked
            if(isBoundary(srs[1][2].getSquareType())) blocks++;
            if(isBoundary(srs[3][2].getSquareType())) blocks++;
            if(isBoundary(srs[2][1].getSquareType())) blocks++;
            if(isBoundary(srs[2][3].getSquareType())) blocks++;

            //true if 3 or more blocks are detected (corner found)
            return(blocks >= 2);

        } 

        /**
         * Checks if the square is within bounds
         * @param Location point
         * @return true if in bounds, otherwise false
         */
        bool isInBounds(Location point)
        {
            return point.x >= 0 && point.y >= 0 && point.x < 17 && point.y < 17;
        }

        /**
         * Cleans up memory for the short range scan
         */
        void clearShortRangeScan()
        {
            if(shortboard){
                for(int i = 0; i < 5; i++){
                    delete[] shortboard[i];
                }
                delete[] shortboard;
                shortboard = nullptr;
            }
        }

        /**
         * Updates the current srs pointer
         * @param ExternalBoardSquare **srs
         */
        void updateShortRangeScan(ExternalBoardSquare** srs)
        {   
            if(!srs){
                return;
            }

            clearShortRangeScan();
            shortboard = srs;
        }

        /**
         * Last ditch effort of calculating a good move on the board
         * @param Direction dir
         * @return RobotMove in the direction desired
         */
        RobotMove hailMary(Direction dir )
        { 
            if(!shortboard){
                return (rand() % 2 == 0) ? ROTATELEFT : ROTATERIGHT;
            }

            ExternalBoardSquare northsq = shortboard[1][2];
            ExternalBoardSquare southsq = shortboard[3][2];
            ExternalBoardSquare westsq = shortboard[2][1];
            ExternalBoardSquare eastsq = shortboard[2][3];

            //default move
            RobotMove bestmove = ROTATERIGHT;

            switch(dir){
                case NORTH:
                    if(!isBoundary(northsq.getSquareType())){
                        bestmove = FORWARD;
                    }
                    else {
                        if(checkDangerLevel(shortboard, QUADRANT2) <  checkDangerLevel(shortboard, QUADRANT1)){
                            bestmove =  ROTATELEFT;
                        }
                        else{
                            bestmove = ROTATERIGHT;
                        }
                    }
                    break;

                case SOUTH:
                    if(!isBoundary(southsq.getSquareType())){
                        bestmove = FORWARD;
                    }
                    else {
                        if(checkDangerLevel(shortboard, QUADRANT3) <  checkDangerLevel(shortboard, QUADRANT4)){
                            bestmove =  ROTATERIGHT;
                        }
                        else{
                            bestmove = ROTATELEFT;
                        }
                    }
                    break;
                case WEST:
                    if(!isBoundary(westsq.getSquareType())){
                        bestmove = FORWARD;
                    }
                    else {
                        if(checkDangerLevel(shortboard, QUADRANT2) <  checkDangerLevel(shortboard, QUADRANT3)){
                            bestmove = ROTATERIGHT;
                        }
                        else{
                            bestmove = ROTATELEFT;
                        }
                    }
                    break;

                case EAST:
                    if(!isBoundary(eastsq.getSquareType())){
                        bestmove = FORWARD;
                    }
                    else {
                        if(checkDangerLevel(shortboard, QUADRANT1) <  checkDangerLevel(shortboard, QUADRANT4)){
                            bestmove = ROTATELEFT;
                        }
                        else{
                            bestmove = ROTATERIGHT;
                        }
                    }
                    break;
                //if point reached
                bestmove = ROTATELEFT;
            }

            //validate that the best move is valid
            if(bestmove == FORWARD){
                Location nextpos = getNextPos(pos, dir);
            
                if(!isInBounds(nextpos) || isBoundary(map[nextpos.x][nextpos.x].type)){
                    return ROTATERIGHT;
                }
            }

            return bestmove;
        }
};