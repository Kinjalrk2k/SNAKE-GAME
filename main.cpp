#include "include\\snake.h"
#include "include\\game.h"
#include "include\\ai.h"    //  unfinished... dont use :/
#include "include\\menu_creator.h"
#include "include\\sliding_control.h"

void window()
{
    HWND console = GetConsoleWindow();
    //MoveWindow(window_handle, x, y, width, height, redraw_window);
    MoveWindow(console, 100, 100, 750, 570 , TRUE);
}

int main(int argc, char const *argv[])
{
    window();

    system("cls");
    cout<<"PRESS ANY KEY TO START...";
    getch();

    main_menu:
    system("cls");
    cout<<" S N A K E S - G A M E";

    gotoxy(1, 14);  cout<<"Developed by: Kinjal Raykarmakar";
    gotoxy(1, 15);  cout<<"GitHub: https://github.com/Kinjalrk2k";

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
            fstream config_file;
            config_file.open("config\\config.dat", ios::in | ios::binary);

            int speed_config;
            char maze_file_name[100];

            config_file>>speed_config>>maze_file_name;

            config_file.close();

            speed = speed_config;
            strcpy(maze_file_location, "mazes\\");
            strcat(maze_file_location, maze_file_name);

            game G;
            G.run_player();

            goto main_menu;
            break;
        } 

        case 1: //  Scoreboard
        {
            system("cls");
            cout<<"This feature is not yet implemented. Will be updated in the updates to come!";
            _getch();
            goto main_menu;
            break;
        }

        case 2: //  Options
        {
            system("cls");
            fstream config_file;
            config_file.open("config\\config.dat", ios::out | ios::binary);

            int speed_config;
            char maze_file_name[100];

            cout<<"Select speed: ";
            gotoxy(14, 1);  cout<<"Fastest";
            gotoxy(16 + 25, 1); cout<<"Slowest";
            position slide_p = {17, 0};
            speed_config = sliding_control(slide_p, 25, 100, 25, true);

            cout<<endl<<"Enter maze file name: ";
            cin>>maze_file_name;
            strcat(maze_file_name, ".dat");

            config_file<<speed_config<<maze_file_name;

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
