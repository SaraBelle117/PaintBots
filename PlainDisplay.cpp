#include "PlainDisplay.h"
using namespace std;

PlainDisplay::PlainDisplay(GameBoard *gameBoard) : gb(gameBoard) {}

void PlainDisplay::update(ObservableData<GameBoard> *data) 
{
    //May need to add specific game state changes
    display();
}

/**
 * Displays the given Gameboard
 * (Please excuse if formatting is slightly wonky, I originally had this method
 * inside of PlainDisplay.h)
 */
void PlainDisplay::display(){
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            InternalBoardSquare sq = gb->getSquare(i, j);
            string square;

            //Wall squares always WWWW
            if(sq.getSquareType() == WALL){
                square += "WWWW";
            }
            else{
            //sets first letter = R - red, B - blue, W - white
                switch(sq.getSquareColor()){
                    case RED:
                        //makes the square red
                        square += "\033[31m";
                        square += "R";
                        //resets to the default color
                        square += "\033[0m";
                        break;
                    case BLUE:
                        //makes the square blue
                        square += "\033[34m";
                        square += "B";
                        //resets to the default color
                        square += "\033[0m";
                        break;
                    case WHITE:
                        square += "W";
                        break;
                }

            //sets second letter (R if red robot, B if blue robot, - if neither)
                if(sq.redRobotPresent()){
                        //makes the square red
                        square += "\033[31m";
                        square += "R";
                        //resets to the default color
                        square += "\033[0m";
                }
                else if(sq.blueRobotPresent()){
                        //makes the square blue
                        square += "\033[34m";
                        square += "B";
                        //resets to the default color
                        square += "\033[0m";
                }
                else{
                    square += "-";
                }

            //sets third letter (X if rock present, - otherwise)
                if(sq.getSquareType() == ROCK){
                    square += "X";
                }
                else{
                    square += "-";
                }

                //sets fourth letter (X if fog present, - otherwise)
                if(sq.getSquareType() == FOG){
                    square += "X";
                }
                else{
                    square += "-";
                }
            }
            //prints the square
            cout << square << " ";
        }
        //newline after each row
        cout << endl;
    }
}