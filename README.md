# SNAKE-GAME
The 90s Snakes Game simulation.

[![ForTheBadge built-with-love](http://ForTheBadge.com/images/badges/built-with-love.svg)](https://github.com/Kinjalrk2k)
[![GitHub license](https://img.shields.io/github/license/Naereen/StrapDown.js.svg)](https://github.com/Kinjalrk2k/SNAKE-GAME/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/badge/release-v1.0-blue.svg)](https://github.com/Kinjalrk2k/SNAKE-GAME/releases)





### Instructions for compilation
Compile the code to produce the executable main file by the following command:
````
g++ main.cpp include\snake.cpp include\game.cpp -o main
````
Compile the code to produce the executable mazes\maze_creator.exe file by the following command:
````
g++ mazes\maze_creator.cpp include\snake.cpp -o mazes\maze_creator
````
Run the main.exe file for playing the game and maze_creator.exe for creating a maze
(Note: Maze creator is unstable for use)

### Notes
Strictly meant for compilation and usage under Windows only (preferably using MinGW compiler toolkit).
This project has not been made "cross-platform".
It uses functions like system(), getch(), etc...

This project is still under development. Parts of the source codes may not be well documented.
Also suitable prompts may not be available for the user at the moment.

More features and fixes are yet to come. Meanwhile suggestions, ideas, bug reports are welcomed.

<br>***Kinjal Raykarmakar***
