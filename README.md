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

Part C: RobotAgentRoster is also a Singleton, and the Robots are also observers of the GameBoard. 

## Running the Program
To run the test files, type "make", and you can run each test as follows:

./ConfigTest
./InternalBoardSquareTest
./ExternalBoardSquareTest
./BoardSquareTest
./GameBoardTest
./paintbots <Config> <RobotConfig>

## Display of the Game
PlainDisplay shows the 17 x 17 GameBoard -- I decided to go with 17 x 17 to show the walls for simplicity, even though the playable area is only 15 x 15. 

Here is how it displays each BoardSquare:
- if the Square is a WALL, it will be represented as "WWWW"
- otherwise, it is implemented as follows, with each number being the letter (each square is 4 chars):
    1. The first letter represents the square color (R, B, or W)
    2. The second letter represents if a robot is present (R, B, or -)
    3. The third letter represents if a rock sqwuare is present (X, or -)
    4. The third letter represents if a fog square is present (X, or -)

I also added colors for the given types of squares just for extra readability. Robots and SquareColors are their actual colors, while the Robots are "bold" to stand out a bit more. Additionally, ROCK squares are green, while FOG squares are yellow, and WALL squares are purple. I added static declarations to allow GameLogic to utilize them when the game is over as well. 

## Playable Robot Strategies [can be found "RobotAgent.h", and "Robot.cpp"]
[LazyRobot] -- Does not move from the initial square, and fires a paintblob each turn into a random direction. 
[RandomRobot] -- Moves in a random direction to a legal square (not a rock or a wall square, or another robot) and never fires a paintblob. 
[AntiRandom] -- Beats the RandomRobot AT LEAST 8/10 times in a game. Always shoots a paintblob, and has a backup method for choosing a RobotMove based on the short range scan. 

## Please Note
As always, I had to make some assumptions for Part B (as we are not quite implementing the full game just yet), so here is a list of some things that were not implemented on purpose:
- There is currently only one Observer of the GameBoard -- PlainDisplay.
- PaintBlobHit() in GameBoard does not increment the number of PaintBlobs for either robot. 
- moveRobot() always returns true as a move can always be made. Part C: Unless a game ending event is found. 
- getLongRangeScan() does not check whether or not the given robot has enough calls left to make.
- There is no game logic (per the specification), so game-ending events are not checked. Part C: Game ending events are now checked in GameLogic! 