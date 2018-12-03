#include "ai.h"

double AI::calc_dist(position dummy_head)
{
    return sqrt((pow(dummy_head.x - food.y, 2)) + (pow(dummy_head.x - food.y, 2)));
}

bool AI::equate_position()
{
    if(head.x == food.x && head.y == food.y)
        return true;
    else
        return false;
}

void AI::set_dummy_heads()
{
    for(int i=0; i<4; i++)
        dummy_head[i] = head;

    dummy_head[0].x = head.x + 1;   //  RIGHT
    dummy_head[1].x = head.x - 1;   //  LEFT
    dummy_head[2].y = head.y + 1;   //  DOWN
    dummy_head[3].y = head.y - 1;   //  UP
}

void AI::run_AI()
{
    srand(time(NULL));

    load_maze();
    print_UI();
    start = {1, 1};
    print_maze();
    print_snake(0);

    gotoxy_offset(generate_food());    cout<<(char)ascii_food;
    gotoxy(0, ymax+4);

    getch();

    direction dir_list[xmax * ymax +1];

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

        /*  TODO: Think about an AI algorithm   */
        
        if(validate_position(head) == false)
        {
            print_status(1);
            getch();
            return;
        }

        print_snake(0);
        print_status(1);
        Sleep(speed);
    }
}