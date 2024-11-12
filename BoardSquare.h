#pragma once

enum Direction { NORTH, SOUTH, EAST, WEST};

enum SquareType {EMPTY, ROCK, FOG, WALL};

enum Color {RED, BLUE, WHITE};

class BoardSquare{
    private:
        Color b_color;
        SquareType b_square;
        Direction b_dir;
        bool b_redRobot;
        bool b_blueRobot;

        //private setter methods
        void setSquareColor(Color col);
        void setSquareType(SquareType sq);
        void setRobotDirection(Direction dir);
        void setRedRobotPresent(bool p);
        void setBlueRobotPresent(bool p);

        //friend class so it can access the private set methods
        friend class InternalBoardSquare;

    public:
        //default constructor
        BoardSquare();

        //specific constructor
        BoardSquare(Color col, SquareType sq, Direction dir, bool redRobot, bool blueRobot);

        //virtual destructor
        virtual ~BoardSquare(){};

        //copy constructor
        BoardSquare(const BoardSquare & rhs);

        //operator = 
        const BoardSquare & operator = (const BoardSquare & rhs);

        //getter methods
        inline Color getSquareColor() const {
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