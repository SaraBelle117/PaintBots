#pragma once

enum Direction { NORTH, SOUTH, EAST, WEST};

enum SquareType {EMPTY, ROCK, FOG, WALL};

enum Color {RED, BLUE, WHITE};

class BoardSquare{
    private:

    public:
        inline Color getSquareColor() const;
        inline SquareType getSquareType() const;
        inline bool redRobotPresent() const;
        inline bool blueRobotPresent() const;
        inline Direction robotDirection() const;

};