#include "include\\snake.h"
#include "include\\game.h"
#include "include\\ai.h"    //  unfinished... dont use :/
#include "include\\menu_creator.h"
#include "include\\sliding_control.h"

//  adjusts window size to a predefined value
void window()
{
    HWND console = GetConsoleWindow();
    //MoveWindow(window_handle, x, y, width, height, redraw_window);
    MoveWindow(console, 100, 100, 750, 650 , TRUE);
}

//  read the scores file and print the values from the same
void read_score()
{
    int score, max=0;
    fstream f;
    f.open("scores\\scores.dat", ios::in | ios::binary);

    while(!f.eof())
    {
        f>>score;
        if(score > max)
            max = score;    //  getting the highest score while reading
        cout<<score<<endl;  //  displaying all the scores
    }    

    cout<<endl<<"Highest Score: "<<max; //  displaying the higest score
    f.close();
}

int main(int argc, char const *argv[])
{
    window();   //  makes out the console window

    system("cls");
    cout<<"PRESS ANY KEY TO START...";
    getch();

    main_menu:
    system("cls");
    cout<<" S N A K E S - G A M E";

    gotoxy(1, 14);  cout<<"Developed by: Kinjal Raykarmakar";
    gotoxy(1, 15);  cout<<"GitHub: https://github.com/Kinjalrk2k";

    //  main menu
    position menu_start_p;
	menu_start_p.x=0;
	menu_start_p.y=2;

	int no_items = 5;
	char menu_items[no_items][260]={"Play Game","Scoreboard(Comming Soon)", "Options(Restricted UI)","Create a maze(Beta)", "Exit"};
	int menu_id;
	int gap=1;

	menu_id=menu(menu_start_p, menu_items, no_items, gap);

    switch(menu_id)
    {
        case 0: //  Play Game
        {
            system("cls");

            //  loading current set configurations from the config file
            fstream config_file;
            config_file.open("config\\config.dat", ios::in | ios::binary);

            int speed_config;
            char maze_file_name[100];

            config_file>>speed_config>>maze_file_name;  //  reading the config file

            config_file.close();

            speed = speed_config;

            //  setting the maze file location
            strcpy(maze_file_location, "mazes\\");
            strcat(maze_file_location, maze_file_name);

            game G; //  creating game instance
            G.run_player(); //  playing the game

            goto main_menu; //  when game over :(
            break;
        } 

        case 1: //  Scoreboard
        {
            system("cls");
            cout<<"Your Scoreboard"<<endl<<endl;
            read_score();   //  read and print the scoes file
            _getch();
            goto main_menu;
            break;
        }

        case 2: //  Options
        {
            system("cls");

            //  loading config file for filling data
            fstream config_file;
            config_file.open("config\\config.dat", ios::out | ios::binary);

            int speed_config;
            char maze_file_name[100];

            //  speed selection slider
            cout<<"Select speed: ";
            gotoxy(14, 1);  cout<<"Fastest";
            gotoxy(16 + 25, 1); cout<<"Slowest";
            position slide_p = {17, 0};
            speed_config = sliding_control(slide_p, 25, 100, 25, true);

            //  maze file name input(w/o .dat)
            cout<<endl<<"Enter maze file name: ";
            cin>>maze_file_name;
            strcat(maze_file_name, ".dat");

            config_file<<speed_config<<maze_file_name;  //  writing to the config file

            config_file.close();

            goto main_menu;
            break;
        }

        case 3: //  maze creator
        {
            system("cls");
            cout<<"Warning! The maze creator functionality is under beta access. Much of its features"<<endl;
            cout<<"might not be operational and may cause unstability. P R O C E E D  W I T H  C A U T I O N !";

            cout<<endl<<endl<<"Press any key too continue...";
            _getch();
            system("mazes\\maze_creator.exe");

            goto main_menu;
        }

        case 4: //  Exit
            exit(0);
            
    }
    
    getch();
    fflush(stdin);

    system("cls");
    cout<<"PRESS ANY KEY TO EXIT...";
    getch();

    return 0;
}
