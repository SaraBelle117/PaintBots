#pragma  once
#include "BoardSquare.h"

class InternalBoardSquare : public BoardSquare{

    public:
        //constructor
        InternalBoardSquare();

        //specific constructor
        InternalBoardSquare(SquareColor col, SquareType sq, Direction dir, bool redRobot, bool blueRobot);

        //since InternalBoardSquare is a friend of BoardSquare (this allows us to use these in GameBoard):

        //sets SquareColor
        void applySquareColor(SquareColor sc)
        {
            setSquareColor(sc);
        }

        //sets SquareType
        void applySquareType(SquareType sq)
        {
            setSquareType(sq);
        }

        //sets RobotDirection
        void applyRobotDirection(Direction dir)
        {
            setRobotDirection(dir);
        }

        //sets RedRobotPresent
        void applyRedRobotPresent(bool p)
        {
            setRedRobotPresent(p);
        }

        //sets BlueRobotPresent
        void applyBlueRobotPresent(bool p)
        {
            setBlueRobotPresent(p);
        }
    
};