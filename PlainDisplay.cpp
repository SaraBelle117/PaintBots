#include "PlainDisplay.h"
using namespace std;

/**
 * Constructs the display, and accesses the given
 * GameBoard instance with the expected password.
 * @throws runtime_error if the GameBoard instance
 * could not be fetched.
 */
PlainDisplay::PlainDisplay()
{
    gb = GameBoard::getInstance("xyzzy");
    //throws error if not given access 
    if(!gb){
        throw runtime_error("Failed to get GameBoard instance.");
    }
}

/**
 * Displays the given GameBoard 
 * @param ObservableData<GameBoard> *data
 */
void PlainDisplay::update(ObservableData<GameBoard> *data) 
{
    //sets the data just received as the most recent
    lastData = data;
    display();
}

/**
 * Displays the given Gameboard
 * (Please excuse if formatting is slightly wonky, I originally had this method
 * inside of PlainDisplay.h)
 */
void PlainDisplay::display()
{
    for(int i = 0; i < 17; i++){
        for(int j = 0; j < 17; j++){
            InternalBoardSquare sq = gb->getSquare(i, j);
            string square;

            //Wall squares always WWWW
            if(sq.getSquareType() == WALL){
                //makes walls purple
                square += "\033[35m";
                square += "WWWW";
                square += "\033[0m";
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
                        square += "\033[36m";
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
                        //makes the square bold & red
                        square += "\033[1;31m";
                        square += "R";
                        //resets to the default color
                        square += "\033[0m";
                }
                else if(sq.blueRobotPresent()){
                        //makes the square bold & blue
                        square += "\033[1;34m";
                        square += "B";
                        //resets to the default color
                        square += "\033[0m";
                }
                else{
                    square += "-";
                }

            //sets third letter (X if rock present, - otherwise)
                if(sq.getSquareType() == ROCK || sq.getSquareType() == FOGANDROCK){
                    //green == rock squares
                    square += "\033[32m";
                    square += "X";
                    //resets color
                    square += "\033[0m";
                }
                else{
                    square += "-";
                }

                //sets fourth letter (X if fog present, - otherwise)
                if(sq.getSquareType() == FOG || sq.getSquareType() == FOGANDROCK){
                    //yellow == fog squares
                    square += "\033[33m";
                    square += "X";
                    //resets color
                    square += "\033[0m";
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


/**
 * Displays the given array of sq (for testing getShortRangeScan() 
 * & getLongRangeScan()
 * @param ExternalBoardSquare** sq
 * @param int size of the list (5x5 if shortrange, 15x15 if longrange)
 */
void PlainDisplay::displayScan(ExternalBoardSquare** list, int size)
{
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
           ExternalBoardSquare& sq = list[i][j];
            string square;

            //Wall squares always WWWW
            if(sq.getSquareType() == WALL){
                //makes walls purple
                square += "\033[35m";
                square += "WWWW";
                square += "\033[0m";
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
                        square += "\033[36m";
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
                        //makes the square bold & red
                        square += "\033[1;31m";
                        square += "R";
                        //resets to the default color
                        square += "\033[0m";
                }
                else if(sq.blueRobotPresent()){
                        //makes the square bold & blue
                        square += "\033[1;34m";
                        square += "B";
                        //resets to the default color
                        square += "\033[0m";
                }
                else{
                    square += "-";
                }

            //sets third letter (X if rock present, - otherwise)
                if(sq.getSquareType() == ROCK || sq.getSquareType() == FOGANDROCK){
                    //green == rock squares
                    square += "\033[32m";
                    square += "X";
                    //resets color
                    square += "\033[0m";
                }
                else{
                    square += "-";
                }

                //sets fourth letter (X if fog present, - otherwise)
                if(sq.getSquareType() == FOG || sq.getSquareType() == FOGANDROCK){
                    //yellow == fog squares
                    square += "\033[33m";
                    square += "X";
                    //resets color
                    square += "\033[0m";
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

/**
 * Returns the last data received by the observer
 * @param ObservableData<GameBoard> last data
 * received by the Observable GameBoard
 */
ObservableData<GameBoard>* PlainDisplay::getLastUpdate()
{
    return lastData;
}