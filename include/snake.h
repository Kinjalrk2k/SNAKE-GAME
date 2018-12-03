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

#define ascii_food 235
#define ascii_wall 176
#define ascii_body 219

using namespace std;

#ifndef GOTOXY_POS
#define GOTOXY_POS
//  position structure
/*  REMEMBER: Console applications run in the 3rd quadrant
    of the cartesian coordinate system. The top-left is (0,0)   */
struct position
{
    int x;  //  x-axis value(left-to-right)
    int y;  //  y-axis value(top-to-bottom)
};

void gotoxy(position pos);
#endif

#ifndef GOTOXY
#define GOTOXY

void gotoxy(int x, int y);

#endif

void gotoxy_offset(int x, int y);
void gotoxy_offset(position pos);

extern position start; //  starting position of the maze
extern int speed;
extern char maze_file_location[100];
extern int difficulty;

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
        void print_snake(int s);
        position move();
        position rotate(direction dir);
};

#endif