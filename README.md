# coms3270P2
By Sara Theriault
Com S 3270
Fall 2024

## Project 2:

## Description
This is a video game known as "Paintbots". The game is played on a square board of 15 x 15. Players create robots that maneuver on the board to paint the squares of the board. Only one robot may occupy by a square at a given time. 

Robots may make the following movments: 
- turn 90 degrees left
- turn 90 degrees right
- move forward one square
- move backward one square
- stay in the same spot

Initially, all the squares on the board are white, and each robot is assigned a color of red or blue. The game lasts for 300 moves in total, and each robot moves at the same time. During each turn/move, the robot may make a move, given by its control algorithm. If the robot moves out of the square, the square that it leaves is turned the robot's color. 

Goal: Have more squares of the board painted in your color (than the opposing robot's color)

Additional game rules:
- A robot may shoot a blob of paint, and if it hits the opposing robot, the robot will paint in the opponents color (rather than their own). This will last for a specified number of moves (hitDuration), and is defined in the game configuration. Default hitDuration is 20.
- A robot only has a limited number of paint blobs that it can shoot, also defined in the game configuration (paintBlobLimit). Default paintBlobLimit is 30.
- If a robot runs into a wall, the game will end, and that robot loses automatically.
- If a robot runs into the other robot, the game will end immediately, but the robot with the most amount of painted squares in it's color will win.
- The game board contains squares with rocks in them, which are treated like walls. The default number of rocks is between 10 - 20, chosen randomly. 
- A robot cannot fire a paint blob through a rock.
- The game board also has squares with fog in them, which move randomly during the game. Paint blobs work through fogs (unlike rocks). The default number of fog squares is between 5 - 10, also chosen randomly. Fog squares restrict the view of a robot's local scan.
- If a robot is in a foq square, the 5 x 5 square returned by the local scan consists of all empty squares except for the center square (which indicates fog).
- A robot's control algorithm may also recieve a limited number of long-range scans which give the contents of the entire 15 x 15 board. A long-range scan is available on any move, but the number of scans is limited and specified by configuration file (default is 30).
- At the beginning of the game, rocks are placed randomly on the board, and robots are also placed randomly on the board. Robots are not placed so they start in a fog square.

## Observer Pattern & Singleton Pattern
This project uses the Observer Pattern to notify the various observers of the Observable GameBoard. The current implementation has the PlainDisplay registered as an observer, and I expect us to add the score of the game, and robots as observers in the future. The GameBoard is also an implementation of the Singleton Pattern. 

## Running the Program
To run the test files, type "make", and you can run each test as follows:

./ConfigTest
./InternalBoardSquareTest
./ExternalBoardSquareTest
./BoardSquareTest
./GameBoardTest

## Display of the Game
PlainDisplay shows the 15 x 15 GameBoard with the following rules. 
- if the Square is a WALL, it will be represented as "WWWW"
- otherwise, it is implemented as follows, with each number being the letter (each square is 4 chars):
    1. The first letter represents the square color (R, B, or W)
    2. The second letter represents if a robot is present (R, B, or -)
    3. The third letter represents if a rock sqwuare is present (X, or -)
    4. The third letter represents if a fog square is present (X, or -)
