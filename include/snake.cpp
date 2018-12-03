#include "snake.h"

position start = {1, 1}; //  starting position of the maze
int speed = 100;
char maze_file_location[100];
int difficulty;

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
}

void maze::write_maze()
{
    maze m;
    fstream f;

    char n[100];
    cout<<"Enter the name of the maze: ";
    gets(n);

    char file_path[100] = "mazes\\";
    strcat(file_path, n);
    strcpy(m.name, n);
    strcat(file_path, ".dat");

    f.open(file_path, ios::out | ios::binary);

    system("cls");
    cout<<"Create the maze: ";
    _getch();
    start = {0, 0};

    system("cls");
    m.print_maze();

    int x=0, y=0;
    /*while(true)
    {
        gotoxy_offset(x, y);

        system("pause>nul");

        if((GetAsyncKeyState(VK_UP) & 0x8000) && y>0)
            y--;

        else if((GetAsyncKeyState(VK_DOWN) & 0x8000) && y<ymax-1)
            y++;

        else if((GetAsyncKeyState(VK_LEFT) & 0x8000) && x>0)
            x--;

        else if((GetAsyncKeyState(VK_RIGHT) & 0x8000) && x<xmax-1)
            x++;

        else if(GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            if(m.maze_state[y][x] == 0)
                m.maze_state[y][x] = 1;
            else
                m.maze_state[y][x] = 0;
            
            system("cls");
            m.print_maze();
        }
        else if((GetAsyncKeyState(VK_RETURN) & 0x8000))
            break;
    }*/
    
    while(true)
    {
        system("pause>nul");
        if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
        {
            POINT pt;
            GetCursorPos(&pt);
            gotoxy(5, 5);   cout<<pt.x<<", "<<pt.y;
            _getch();
        }
    }

    gotoxy(0, ymax+1);
    cout<<"Press any key to save the maze";
    getch();

    f.write((char*)&m, sizeof(m));

    f.close();
}

void maze::load_maze()
{
    maze m;
    fstream f;
    f.open(maze_file_location, ios::in | ios::binary);

    f.read((char*)&m, sizeof(m));
    f.close();
    *this = m;

    calc_difficulty();
}

void maze::print_maze()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i=0; i<ymax; i++)
    {
        for(int j=0; j<xmax; j++)
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            gotoxy_offset(j, i);
            if(maze_state[i][j] == 1)
                cout<<(char)ascii_wall;
        }
    }
    gotoxy(0, ymax+4);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED	| FOREGROUND_BLUE);
}

int maze::calc_difficulty()
{
    int counter = 0;
    for(int i=0; i<ymax; i++)
    {
        for(int j=0; j<xmax; j++)
            if(maze_state[i][j] == 1)
                counter++;
    }

    difficulty = ((counter*100) / (ymax*xmax));

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


void snake::print_snake(int s)  //  s=0 alive, s=1 dead
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch(s)
    {
        case 0:
           SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED	| FOREGROUND_BLUE);
           break;
        case 1:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            break;
    }
    gotoxy_offset(head);   cout<<(char)ascii_body;

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED	| FOREGROUND_BLUE);    
    for(int i=0; i<size-1; i++)
    {
        switch(s)
        {
            case 0:
               SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED	| FOREGROUND_BLUE);
               break;
            case 1:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                break;
        }
        gotoxy_offset(body[i]);
        cout<<(char)ascii_body;
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED	| FOREGROUND_BLUE);
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