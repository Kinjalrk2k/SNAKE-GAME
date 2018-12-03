#include "game.h"

/*  the pointer loc takes up the full location of the file from where the art is to be read
    x and y denotes the x and y positions (respectively), where the art is needed to be printed
    (Note: x and y denotes the position where the first character in the file is to be printed)
    (Note2: if you want to print the art at (0,0), then ignore the x and y arguments     */
void ascii_art(const char* loc, int x=0, int y=0)
{
    fstream f;  //  used for file handling
	f.open(loc, ios::in);   //  opened file in reading mode

	gotoxy(x,y);    //  position to start printing

	char t; //  used for reading the character from file
	while(f.get(t)) //  loop for reading the whole file
    {
        if(f.eof())
            break;  //  break the loop if end of file is reached

        if(t=='\n') //  detecting new line character in file
        {
            y++;
            gotoxy(x,y);    //  going to the new line
            continue;
        }

        cout<<t;    //  printing the character read from the file
    }
}

game::game()
{
    score = 0;
    //speed = 100;
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

    gotoxy(0,ymax+1);
    cout<<(char)200;
    for(int i=0; i<xmax; i++)
        cout<<(char)205;
    cout<<(char)188;

    gotoxy(0,ymax+2);
    cout<<(char)201;
    for(int i=0; i<xmax; i++)
        cout<<(char)205;
    cout<<(char)187;

    for(int i=0; i<4; i++)
    {
        gotoxy(0, ymax+3+i); cout<<(char)186;
        gotoxy(xmax+1, ymax+3+i);  cout<<(char)186;
    }

    gotoxy(0,ymax+7);
    cout<<(char)200;
    for(int i=0; i<xmax; i++)
        cout<<(char)205;
    cout<<(char)188;

    gotoxy(1, ymax+3);  cout<<"GAME PAUSED     ";
    gotoxy(1, ymax+4);   cout<<"Score: "<<score;
    gotoxy(1, ymax+5);   cout<<"Maze: "<<name;
    gotoxy(1, ymax+6);  cout<<"Difficulty: "<<difficulty;

    gotoxy(16, ymax+2); cout<<(char)203;
    for(int i=0; i<4; i++)
    {
        gotoxy(16, ymax+3+i);   cout<<(char)186;
    }
    gotoxy(16, ymax+7); cout<<(char)202;

    gotoxy(17, ymax+3);
    for(int i=0; i<(xmax-17-21)/2; i++)
        cout<<" ";

    cout<<"S N A K E S - G A M E";
    gotoxy(17, ymax+4);
    cout<<"Press any key to start the game. Use your arrow keys to";
    gotoxy(17, ymax+5);
    cout<<"move the snake. Eat the apples without hitting the walls or";
    gotoxy(17, ymax+6);
    cout<<"the snake's body. +1 score for each successful apple eating";
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
    gotoxy(1, ymax+4);   cout<<"Score: "<<score;
    gotoxy(1, ymax+3);
    switch(s)
    {
        case 0: cout<<"GAME OVER!   ";  break;
        case 1: cout<<"PLAYING GAME "; break;
        case 2: cout<<"GAME PAUSED  ";  break;
    }
}

void write_score(int score)
{
    fstream f;
    f.open("scores\\scores.dat", ios::out | ios::binary | ios::app);
    f<<" "<<score;
    f.close();
}

void game::run_player()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(NULL));

    load_maze();
    print_UI();
    start = {1, 1};
    print_maze();
    print_snake(0);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    gotoxy_offset(generate_food());    cout<<(char)ascii_food;
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED	| FOREGROUND_BLUE);
    gotoxy(0, ymax+4);

    getch();

    while(true)
    {
        if(head.x == food.x && head.y == food.y)
        {
            //system("start sounds\\sounder.exe sounds\\eat.wav");
            //PlaySound((LPCSTR)"sounds\\eat.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
            size++;
            score++;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            gotoxy_offset(generate_food());    cout<<(char)ascii_food;
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED	| FOREGROUND_BLUE);
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

        else if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            return;

        else if(GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            print_status(2);

            system("pause>nul");
        }

        else
            gotoxy_offset(move());
 
        cout<<" ";
        if(validate_position(head) == false)
        {
            print_status(0);
            print_snake(1);
            write_score(score);
            system("pause>nul");
            while (cin.get() != '\n');
            return;
        }

        print_snake(0);
        print_status(1);
        gotoxy(0,0);
        Sleep(speed);
    }
}

