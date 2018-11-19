#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

#define xmax 75
#define ymax 25

#define ascii_food 233
#define ascii_wall 178
#define ascii_body 219

using namespace std;

//  position structure
/*  REMEMBER: Console applications run in the 3rd quadrant
    of the cartesian coordinate system. The top-left is (0,0)   */
struct position
{
    int x;  //  x-axis value(left-to-right)
    int y;  //  y-axis value(top-to-bottom)
};

void gotoxy(int x, int y);
void gotoxy(position pos);

void gotoxy_offset(int x, int y);
void gotoxy_offset(position pos);

extern position start; //  starting position of the maze
extern int speed;
extern char maze_file_location[100];

enum direction
{
    UP, DOWN, LEFT, RIGHT
};

//  maze class
class maze
{
    protected:
        char name[50];
        int maze_state[ymax][xmax];
        int difficulty;

    public:
        maze();
        void write_maze();
        void load_maze();
        void print_maze();
        int calc_difficulty();
};

class snake
{
    protected:
        position head;
        position body[(ymax*xmax)-1];
        int size;
        direction flow;

    public:
        snake();
        void print_snake();
        position move();
        position rotate(direction dir);
};

#endif