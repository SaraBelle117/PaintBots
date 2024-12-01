# Project 2 - COM S 3270
By Sara Theriault
Com S 3270
Fall 2024

## Table of Contents
1. [Overview](#overview)
2. [Project Structure](#project-structure)
3. [Setup for Development](#setup-for-development)
4. [Challenges Encountered](#challenges-encountered)
5. [Testing](#testing)

## Overview
This project is a robot game called "PaintBots" (with the rules included in the README files).
The project does have a clear design in mind, but there are a few things that we had to make some decisions for -- most of those decisions I've made can be found in this list:
- The playable GameBoard is 15x15 BoardSquares, but I decided to have a 17x17 vector represent the GameBoard with the WALL squares included. Note that getLongRangeScan() still only returns the 15x15 grid, so only the given playable area. 
- I chose to do the "Direct Access Method" for passing changes to PlainDisplay (as it is an observer for the GameBoard), at least at this point in my implementation. 

## Project Structure
The board for the game is made up of 15 x 15 "board squares", and the internalboard cannot be viewed from the 
externalboard. 
- InternalBoardSquare: represents the tru (hidden) game state, and tracks the changes of the game.
- ExternalBoardSquare: represents what the player/observers of the game can see (visible state), and it updates notifications based on the InternalBoard 
- GameBoard: implemented using the Observer Pattern, with the following breakdown:
Observable: GameBoard (also utilizing the Singleton Pattern, as we have only one instance of the GameBoard)
Observers: PlainDisplay, with future observers TBD (likely a ScoreBoard, and Robot Observers)
ObservableData: there are three notable changes in the game state -- when the score changes, when the robot moves, and when a square changes color. 
NOTE: I am not 100% certain why we are failing to update the change in SquareType, such as when we randomize the fog squares on the board. Will be asking in Piazza to clarify. 
- PlainDisplay: this is our observer for the GameBoard, and it shows the GameBoard, representation of which is detailed in the README files. 


## Challenges Encountered
Setting up the first few files (the internal & external boards squares) was relatively straightforward due to the instructions given, but the first trouble I ran into was when I was working on the constructor using the configuration file. Parsing the strings wasn't too difficult (as I used "string" which has many useful methods), but I did decided to convert the string back to a regular C "character array" since I couldn't find a way to compare strings without being case-sensitive using C++ string methods. Additionally, I did have some issues with
ensuring that the "value" integer (parsed from the file) was a valid number, so I added error checking for that as well. The toughest portion I encountered in this part was surprisingly (to me) getting rid of white space. I found a few suggestions on Stack Overflow, but I hate using other peoples' code, so I ended up taking a combination of things that were taught in class (from the Observable template), and I ended up adding a lambda function that returned
each character from the string, and checked if it was a space character. If it was a space character, it would remove that from the string. I used this to trim the white space from "keyword" as well as "value" (the integer):

            //removes all spaces in the value string
            valueStr.erase(remove_if(valueStr.begin(), valueStr.end(),
            [](unsigned char c) {return isspace(c);}), valueStr.end());

I'm aware that there are more "readable" ways to implement this, but the other design ideas I had ended up not working, and I wanted to try something new that I haven't used before (a lambda function, in this case, as well as the new methods in C++ I haven't used before). 


## Testing
I created 10 test configuration files for my project, and also opted to make a "testinternalboardsquare" file since
this was my first time programming in C++, so I wanted to make sure everything worked as I expected it to. 

Essentially, each file for the program has a test file as follows:
- ConfigTest
- BoardSquareTest
- InternalBoardSquareTest
- ExternalBoardSquareTest
- GameBoardTest

