#ifndef GAME_H
#define GAME_H

#include "snake.h"



void ascii_art(const char* loc, int x, int y);

class game : protected snake, protected maze
{
    protected:
        int score;
        position food;
        int speed;

    public:
        game();
        void print_UI();
        void print_status(int s);
        bool validate_position(position pos);
        position generate_food();
        void run_player();
        
};

#endif