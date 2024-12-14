#pragma once

enum Direction { NORTH, SOUTH, EAST, WEST};

enum SquareType {EMPTY, ROCK, FOG, WALL, FOGANDROCK};

enum SquareColor {RED, BLUE, WHITE};

enum RobotColor {XRED, XBLUE};

enum RobotMove{ROTATELEFT, ROTATERIGHT, FORWARD, NONE};

struct RobotMoveRequest{ 
    RobotColor robot;
    RobotMove move;
    bool shoot;
    bool lrs;
};

//for tracking BoardSquares
struct Location{
    int x;
    int y;

    bool operator<(const Location & other) const
    {
        return(x < other.x) || (x == other.x && y < other.y);
    }
};

class BoardSquare{
    private:
        SquareColor b_color;
        SquareType b_square;
        Direction b_dir;
        bool b_redRobot;
        bool b_blueRobot;
        
        //friend class so it can access the private set methods
        friend class InternalBoardSquare;

        //private setter methods
        void setSquareColor(SquareColor col);
        void setSquareType(SquareType sq);
        void setRobotDirection(Direction dir);
        void setRedRobotPresent(bool p);
        void setBlueRobotPresent(bool p);

    public:
        //default constructor (implemented in CPP file)
        BoardSquare();

        //specific constructor (implemented in CPP file)
        BoardSquare(SquareColor col, SquareType sq, Direction dir, bool redRobot, bool blueRobot); 

        //virtual destructor
        virtual ~BoardSquare(){};

        //copy constructor (implemented in CPP file)
        BoardSquare(const BoardSquare & rhs);

        //operator = (implemented in CPP file)
        const BoardSquare & operator = (const BoardSquare & rhs); 

        //getter methods
        inline SquareColor getSquareColor() const {
            return b_color;
        }

        inline SquareType getSquareType() const {
            return b_square;
        }

        inline Direction robotDirection() const {
            return b_dir;
        }

        inline bool redRobotPresent() const {
            return b_redRobot;
        }

        inline bool blueRobotPresent() const {
            return b_blueRobot;
        }

};