/*  maze and sake class defined here    */
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

//  standard gotoxy function
void gotoxy(int x, int y);

#endif

//  gotoxy with offsets
void gotoxy_offset(int x, int y);   
void gotoxy_offset(position pos);

extern position start; //  starting position of the maze
extern int speed;   //  snake speed, readable and editable through a file
extern char maze_file_location[100];    //  dynamic locaton of the current maze file
extern int difficulty;  //  captures the difficulty level of the maze

//  enumerated data type direction to store flow direction and snake rotation
enum direction
{
    UP, DOWN, LEFT, RIGHT
};

//  maze class
class maze
{
    protected:
        char name[50];  //  name of the maze
        /*  possible values of maze_state[i][j]:
            wall present = 1
            wall absent = 0 */
        int maze_state[ymax][xmax]; //  wall state of the maze 

    public:
        maze(); //  default constructor to initialise the members
        void write_maze();  //  write maze to a file:   needs development
        void load_maze();   //  load maze from predefined file
        void print_maze();  //  print maze on the game

        /*  difficulty level:
            0 - 100 :   easiest - toughest  */
        int calc_difficulty();  //  calculate the difficulty level of the maze
};

class snake
{
    protected:
        position head;  //  stores the position of the head f the snake in the maze
        position body[(ymax*xmax)-1];   //  stores the position of the continuous body position following the head
        int size;   //  current size of the snake
        direction flow; //  current flow direction of the snake

    public:
        snake();    //  default constructor to initialise the class members
        void print_snake(int s);    //  print the snake 
        position move();    //  move the snake in the current flow
        position rotate(direction dir); //  rotate the snake as flow passed as argument
};

#endif