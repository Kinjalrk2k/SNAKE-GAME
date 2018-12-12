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

/*  initialises the score with 0(starting score with)   */
game::game()
{
    score = 0;
    //speed = 100;
}

bool game::validate_position(position pos)
{
    for(int i=1; i<size-1; i++)
    {
        if(pos.x == body[i].x && pos.y == body[i].y)    //  if the posotion coincide with the snake body
            return false;
    }

    if(maze_state[pos.y][pos.x] == 1)   //  if the posoition coincide with the maze wall
        return false;

    return true;
}

/*  printing the whole UI: self explanatory   */
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
        //  randomize the position for the new food
        food.x = rand()%xmax;
        food.y = rand()%ymax;
    }
    while(this->validate_position(food) == false);
    //  checks whether the position of the new food is valid, or else create another one

    return food;
}

/*  prints current game status  */
void game::print_status(int s)
{
    /*  possible values of s:
        0 = game over   
        1 = game running    */
    gotoxy(1, ymax+4);   cout<<"Score: "<<score;
    gotoxy(1, ymax+3);
    switch(s)
    {
        case 0: cout<<"GAME OVER!   ";  break;
        case 1: cout<<"PLAYING GAME "; break;
        case 2: cout<<"GAME PAUSED  ";  break;
    }
}

/*  standalone function to append the scores in the score.dat file  */
void write_score(int score)
{
    fstream f;
    f.open("scores\\scores.dat", ios::out | ios::binary | ios::app);
    f<<" "<<score;
    f.close();
}

/*  runs the game   */
void game::run_player()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(NULL));

    load_maze();    //  loads the maze from the targetted .dat file
    print_UI();     //  prints the UI
    start = {1, 1}; //  offset starting point
    print_maze();   //  print the maze walls/boundaries
    print_snake(0); //  print the initial snake position

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    gotoxy_offset(generate_food());    cout<<(char)ascii_food;  //  generate and print food
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED	| FOREGROUND_BLUE);
    gotoxy(0, ymax+4);

    getch();

    while(true)
    {
        //  if heads of the snakes coinside with the food
        if(head.x == food.x && head.y == food.y)
        {
            /*  trying out sound >_< */
            //system("start sounds\\sounder.exe sounds\\eat.wav");
            //PlaySound((LPCSTR)"sounds\\eat.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
            size++;     //  size of the snake increases by 1
            score++;    //  score increases by 1
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            gotoxy_offset(generate_food());    cout<<(char)ascii_food;  //  generate and print a new food
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED	| FOREGROUND_BLUE);
            gotoxy(0, ymax+4);
            continue;
        }

        //  when UP key is pressed once and the current flow is not DOWN
        if((GetAsyncKeyState(VK_UP) & 0x8000) && flow != DOWN)
            gotoxy_offset(rotate(UP));  //  rotate the snake head UP and also gotoxy to the last snake tail

        //  when DOWN key is pressed once and the current flow is not UP
        else if((GetAsyncKeyState(VK_DOWN) & 0x8000) && flow != UP)
            gotoxy_offset(rotate(DOWN));    //  rotate the snake head DOWN and also gotoxy to the last snake tail

        //  when LEFT key is pressed once and the current flow is not RIGHT
        else if((GetAsyncKeyState(VK_LEFT) & 0x8000) && flow !=RIGHT)
            gotoxy_offset(rotate(LEFT));    //  rotate the snake head LEFT and also gotoxy to the last snake tail

        //  when RIGHT key is pressed once and the current flow is not LEFT
        else if((GetAsyncKeyState(VK_RIGHT) & 0x8000) && flow != LEFT)
            gotoxy_offset(rotate(RIGHT));   //  rotate the snake head RIGHT and also gotoxy to the last snake tail

        //  when ESC key is pressed once
        else if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            return; //  exit current game

        //  when SPACE key is pressed once
        else if(GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            //  pause current game till another key is pressed
            print_status(2);    //  print game PAUSED

            system("pause>nul");
        }

        else    //  if no keys are pressed :)
            gotoxy_offset(move());  //  keep moving with the current flow and gotoxy to the last snake tail
 
        cout<<" ";  //  print space of 1 unit at the gotoxy position

        if(validate_position(head) == false)    //  if head reaches an invalid position
        {
            //  you are DEAD! :(
            print_status(0);    //  prints GAME OVER
            print_snake(1);     //  prints snake in RED colour
            write_score(score); //  writes the score to the file

            //  wait till another key is pressed
            system("pause>nul");
            while (cin.get() != '\n');
            return;
        }

        //  print the snake and status in normal conditions
        print_snake(0);
        print_status(1);
        gotoxy(0,0);
        Sleep(speed);   //  restricts the seed of the snake to the defined value
    }
}

