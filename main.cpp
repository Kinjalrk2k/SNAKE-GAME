#include "include\\snake.h"

void window()
{
    HWND console = GetConsoleWindow();
    //MoveWindow(window_handle, x, y, width, height, redraw_window);
    MoveWindow(console, 100, 100, 750, 550, TRUE);
}

int main(int argc, char const *argv[])
{
    window();

    system("cls");
    cout<<"PRESS ANY KEY TO START...";
    getch();

    game G;
    strcpy(G.full_file_location, "mazes\\maze0.txt");
    G.run_player();

    getch();
    fflush(stdin);

    system("cls");
    cout<<"PRESS ANY KEY TO EXIT...";
    getch();

    return 0;
}
