#include "PlainDisplay.h"
using namespace std;

//for adding colors to the board
const string PlainDisplay::RESET = "\033[0m";
const string PlainDisplay::PURPLE_C = "\033[35m";
const string PlainDisplay::RED_C = "\033[31m";
const string PlainDisplay::BLUE_C = "\033[36m";
const string PlainDisplay::REDBOLD = "\033[1;31m";
const string PlainDisplay::BLUEBOLD = "\033[1;34m";
const string PlainDisplay::GREEN_C = "\033[32m";
const string PlainDisplay::YELLOW_C = "\033[33m";

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
 * For displaying the "Title screen" of the game
 * PAINTBOTS
 */
void PlainDisplay::titleScreen()
{
    string title = "PAINTBOTS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    string col[] = {REDBOLD, BLUEBOLD};
    
    for(size_t i = 0; i < title.length(); i++){
        //alternates the colors of the title between red and blue
        cout << col[i % 2] << title[i];
    }
    cout << RESET << endl;
}
/**
 * Displays the given Gameboard
 * (Please excuse if formatting is slightly wonky, I originally had this method
 * inside of PlainDisplay.h)
 */
void PlainDisplay::display()
{
    titleScreen();
    printf("\n");
    for(int i = 0; i < 17; i++){
        for(int j = 0; j < 17; j++){
            InternalBoardSquare sq = gb->getSquare(i, j);
            string square;

            //Wall squares always WWWW
            if(sq.getSquareType() == WALL){
                //makes walls purple
                square += PURPLE_C;
                square += "WWWW";
                square += RESET;
            }
            else{
            //sets first letter = R - red, B - blue, W - white
                switch(sq.getSquareColor()){
                    case RED:
                        //makes the square red
                        square += RED_C;
                        square += "R";
                        //resets to the default color
                        square += RESET;
                        break;
                    case BLUE:
                        //makes the square blue
                        square += BLUE_C;
                        square += "B";
                        //resets to the default color
                        square += RESET;
                        break;
                    case WHITE:
                        square += "W";
                        break;
                }

            //sets second letter (R if red robot, B if blue robot, - if neither)
                if(sq.redRobotPresent()){
                        //makes the square bold & red
                        square += REDBOLD;
                        square += "R";
                        //resets to the default color
                        square += RESET;
                }
                else if(sq.blueRobotPresent()){
                        //makes the square bold & blue
                        square += BLUEBOLD;
                        square += "B";
                        //resets to the default color
                        square += RESET;
                }
                else{
                    square += "-";
                }

            //sets third letter (X if rock present, - otherwise)
                if(sq.getSquareType() == ROCK || sq.getSquareType() == FOGANDROCK){
                    //green == rock squares
                    square += GREEN_C;
                    square += "X";
                    //resets color
                    square += RESET;
                }
                else{
                    square += "-";
                }

                //sets fourth letter (X if fog present, - otherwise)
                if(sq.getSquareType() == FOG || sq.getSquareType() == FOGANDROCK){
                    //yellow == fog squares
                    square += YELLOW_C;
                    square += "X";
                    //resets color
                    square += RESET;
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
    printf("\n");
    cout << REDBOLD << "RED SCORE: " << gb->redScore() << RESET << endl;
    cout << BLUEBOLD << "BLUE SCORE: " << gb->blueScore() << RESET << endl;
    printf("\n\n");
}


/**
 * Displays the given array of sq (for testing getShortRangeScan() 
 * & getLongRangeScan()
 * @param ExternalBoardSquare** sq
 * @param int size of the list (5x5 if shortrange, 15x15 if longrange)
 */
void PlainDisplay::displayScan(ExternalBoardSquare** list, int size)
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
           ExternalBoardSquare& sq = list[i][j];
            string square;

            //Wall squares always WWWW
            if(sq.getSquareType() == WALL){
                //makes walls purple
                square += PURPLE_C;
                square += "WWWW";
                square += RESET;
            }
            else{
            //sets first letter = R - red, B - blue, W - white
                switch(sq.getSquareColor()){
                    case RED:
                        //makes the square red
                        square += RED_C;
                        square += "R";
                        //resets to the default color
                        square += RESET;
                        break;
                    case BLUE:
                        //makes the square blue
                        square += BLUE_C;
                        square += "B";
                        //resets to the default color
                        square += RESET;
                        break;
                    case WHITE:
                        square += "W";
                        break;
                }

            //sets second letter (R if red robot, B if blue robot, - if neither)
                if(sq.redRobotPresent()){
                        //makes the square bold & red
                        square += REDBOLD;
                        square += "R";
                        //resets to the default color
                        square += RESET;
                }
                else if(sq.blueRobotPresent()){
                        //makes the square bold & blue
                        square += BLUEBOLD;
                        square += "B";
                        //resets to the default color
                        square += RESET;
                }
                else{
                    square += "-";
                }

            //sets third letter (X if rock present, - otherwise)
                if(sq.getSquareType() == ROCK || sq.getSquareType() == FOGANDROCK){
                    //green == rock squares
                    square += GREEN_C;
                    square += "X";
                    //resets color
                    square += RESET;
                }
                else{
                    square += "-";
                }

                //sets fourth letter (X if fog present, - otherwise)
                if(sq.getSquareType() == FOG || sq.getSquareType() == FOGANDROCK){
                    //yellow == fog squares
                    square += YELLOW_C;
                    square += "X";
                    //resets color
                    square += RESET;
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

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
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