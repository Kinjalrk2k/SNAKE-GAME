#include "snake.h"

//  standard gotoxy function using seperate x and y arguments
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//  standard gotoxy function using a pointer structure
void gotoxy(position pos)
{
    COORD coord;
    coord.X = pos.x;
    coord.Y = pos.y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void gotoxy_offset(int x, int y)
{
    COORD coord;
    coord.X = x + start.x;
    coord.Y = y + start.y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void gotoxy_offset(position pos)
{
    COORD coord;
    coord.X = pos.x + start.x;
    coord.Y = pos.y + start.y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

maze::maze() : maze_state{0}
{
    strcpy(name, "Default Maze");
    difficulty = 0;
}

void maze::print_maze()
{
    for(int i=0; i<ymax; i++)
    {
        for(int j=0; j<xmax; j++)
        {
            gotoxy_offset(j, i);
            if(maze_state[i][j] == 1)
                cout<<(char)ascii_wall;
        }
    }
    gotoxy(0, ymax+4);
}

int maze::calc_difficulty()
{
    int counter = 0;
    for(int i=0; i<ymax; i++)
    {
        for(int j=0; j<xmax; j++)
            if(maze_state[i][j] == 0)
                counter++;
    }

    difficulty = (counter / (ymax*xmax)) * 100;

    return difficulty;
}

snake::snake()
{
    head = {11, 10};

    body[0] = {10, 10};
    body[1] = {9, 10};
    body[2] = {8, 10};
    body[3] = {7, 10};

    size = 5;

    flow = RIGHT;
}

void snake::print_snake()
{
    gotoxy_offset(head);   cout<<(char)ascii_body;
    for(int i=0; i<size-1; i++)
    {
        gotoxy_offset(body[i]);
        cout<<(char)ascii_body;
    }
}

position snake::move()
{
    position tail = body[size-2];

    for(int i=(size - 2); i>0; i--)
        body[i] = body[i-1];
    body[0] = head;

    switch(flow)
    {
        case RIGHT: head.x++;    break;
        case UP:    head.y--;    break;
        case LEFT:  head.x--;    break;
        case DOWN:  head.y++;    break;    
    }

    if(head.x < 0)
        head.x = xmax-1;
    else if(head.x > xmax-1)
        head.x = 0;
    else if(head.y < 0)
        head.y = ymax-1;
    else if(head.y > ymax-1)
        head.y = 0;

    return tail;
}

position snake::rotate(direction dir)
{
    position tail = body[size-2];
    switch(dir)
    {
        case UP:
            if(flow !=  DOWN)
            {
                flow = UP;
                for(int i=(size - 2); i>0; i--)
                    body[i] = body[i-1];
                body[0] = head;
                head.y--;
            }
            break;

        case DOWN:
            if(flow !=  UP)
            {
                flow = DOWN;
                for(int i=(size - 2); i>0; i--)
                    body[i] = body[i-1];
                body[0] = head;
                head.y++;
            }
            break;

        case LEFT:
            if(flow !=  RIGHT)
            {
                flow = LEFT;
                for(int i=(size - 2); i>0; i--)
                    body[i] = body[i-1];
                body[0] = head;
                head.x--;
            }
            break;
        
        case RIGHT:
            if(flow !=  LEFT)
            {
                flow = RIGHT;
                for(int i=(size - 2); i>0; i--)
                    body[i] = body[i-1];
                body[0] = head;
                head.x++;
            }
            break;
    }

    if(head.x < 0)
        head.x = xmax-1;
    else if(head.x > xmax-1)
        head.x = 0;
    else if(head.y < 0)
        head.y = ymax-1;
    else if(head.y > ymax-1)
        head.y = 0;

    return tail;
}

game::game()
{
    score = 0;
}

void game::load_maze()
{
    fstream f;
    f.open(full_file_location, ios::in);
    for(int i=0; i<ymax; i++)
    {
        for(int j=0; j<xmax; j++)
        {
            f>>maze_state[i][j];
        }
    }
}

bool game::validate_position(position pos)
{
    for(int i=1; i<size-1; i++)
    {
        if(pos.x == body[i].x && pos.y == body[i].y)
            return false;
    }

    if(maze_state[pos.y][pos.x] == 1)
        return false;

    return true;
}

void game::print_UI()
{
    gotoxy(0,0);
    cout<<(char)201;
    for(int i=0; i<xmax; i++)
        cout<<(char)205;
    cout<<(char)187;

    for(int i=0; i<ymax; i++)
    {
        gotoxy(0, i+1); cout<<(char)186;
        gotoxy(xmax+1, i+1);  cout<<(char)186;
    }

    gotoxy(0,26);
    cout<<(char)200;
    for(int i=0; i<xmax; i++)
        cout<<(char)205;
    cout<<(char)188;

    gotoxy(0, ymax+3);   cout<<"Score: "<<score;

    /*TODO: ADD MORE*/
}

position game::generate_food()
{
    do
    {
        food.x = rand()%xmax;
        food.y = rand()%ymax;
    }
    while(this->validate_position(food) == false);

    return food;
}

//  0 = game over   1 = game running
void game::print_status(int s)
{
    gotoxy(0, ymax+4);   cout<<"Score: "<<score;
    gotoxy(0, ymax+3);
    switch(s)
    {
        case 0: cout<<"GAME OVER";  break;
        case 1: cout<<"PLAYING GAME"; break;
    }
}

void game::run_player()
{
    srand(time(NULL));

    print_UI();
    start = {1, 1};
    load_maze();
    print_maze();
    print_snake();

    gotoxy_offset(generate_food());    cout<<(char)ascii_food;
    gotoxy(0, ymax+4);

    getch();

    while(true)
    {
        if(head.x == food.x && head.y == food.y)
        {
            size++;
            score++;
            gotoxy_offset(generate_food());    cout<<(char)ascii_food;
            gotoxy(0, ymax+4);
            continue;
        }

        if((GetAsyncKeyState(VK_UP) & 0x8000) && flow != DOWN)
            gotoxy_offset(rotate(UP));

        else if((GetAsyncKeyState(VK_DOWN) & 0x8000) && flow != UP)
            gotoxy_offset(rotate(DOWN));

        else if((GetAsyncKeyState(VK_LEFT) & 0x8000) && flow !=RIGHT)
            gotoxy_offset(rotate(LEFT));

        else if((GetAsyncKeyState(VK_RIGHT) & 0x8000) && flow != LEFT)
            gotoxy_offset(rotate(RIGHT));

        else
            gotoxy_offset(move());
 
        cout<<" ";
        if(validate_position(head) == false)
        {
            print_status(0);
            return;
        }

        print_snake();
        print_status(1);
        Sleep(speed);
    }
}

