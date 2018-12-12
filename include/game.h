/*  game class defination: controls the UI/UX of the general gameplay   */
#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include <mmsystem.h>

//  loads ascii art from a file and print it on the console window
void ascii_art(const char* loc, int x, int y);

class game : public snake, public maze
{
    protected:
        int score;     //   saves current game state score
        position food;  //  position of the current food in the map

    public:
        game();     //  default constructor: to seed the nominal game variables
        void print_UI();    //  prints the general game UI
        void print_status(int s);   //  prints the lates updated status: PAUSED/DEAD/ALIVE
        bool validate_position(position pos);   //  validate the passed position upon constraints
        position generate_food();   //  generate new food position
        void run_player();  //  run the game
};

#endif