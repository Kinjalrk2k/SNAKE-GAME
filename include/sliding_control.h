#ifndef SLIDING_CONTROL
#define SLIDING_CONTROL

#include <iostream>
#include <windows.h>
#include <math.h>

#define ascii_bar 196
#define ascii_bead 178
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

void gotoxy(position pos)
{
    COORD coord;
    coord.X = pos.x;
    coord.Y = pos.y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#endif

template <typename T>   //  a typename template to work with different data types
T sliding_control(position start, T min, T max, int length, bool display_value = true)
{
    position pos = start;   //  variable current position of the bead
    position ret = start;   //  return position at the end of the function
    position disp_value_position = start;   //  displaying instantaneous value position
    
    ret.y+=2;   //  setting the return position
    disp_value_position.x+=(length + 5);    //  setting the value display position

    double diff = abs(max - min);   //  absolute difference between the ranges
    double step = double (diff / length);   //  difference per unit length
    T value = min;  //  initial value

    int step_id = 0;    //  current step id over the length

    /*  printing the slide with bead at the initial point   */
    gotoxy(pos);
    cout<<">"<<(char)ascii_bead;
    for(int i=0; i<length; i++)
        cout<<(char)ascii_bar;
    cout<<"<";

    pos.x++;   gotoxy(pos);
    while(true)
    {
        value = min + (step_id * step); //  instantaneos value
        if(display_value)   //  if displaying value is set to true
        {
            /*  displaying instantaneos value   */
            gotoxy(disp_value_position); 
            for(int i=0; i<24; i++)
                cout<<" ";
            gotoxy(disp_value_position);
            cout<<value;
        }
        else
            gotoxy(ret);

        system("pause>nul");    //  prompts the system to avoid null bit

        if((GetAsyncKeyState(VK_RIGHT) & 0x8000) && step_id<length) //  move RIGHT, stay within the slide
        {
            gotoxy(pos);    cout<<(char)ascii_bar;
            pos.x++;
            step_id++;
            gotoxy(pos);    cout<<(char)ascii_bead;
        }

        else if((GetAsyncKeyState(VK_LEFT) & 0x8000) && step_id>0)  //  move LEFT, stay within the slide
        {
            gotoxy(pos);    cout<<(char)ascii_bar;
            pos.x--;
            step_id--;
            gotoxy(pos);    cout<<(char)ascii_bead;
        }

        else if(GetAsyncKeyState(VK_RETURN) & 0x8000)   //  return to the calling function
        {
            gotoxy(ret);
            return value;
        }
    }   
}

/*  sample main function for testing
int main(int argc, char const *argv[])
{
    int min = 0, max = 5, length = 15;
    position start = {0, 0};

    int value;
    value = sliding_control(start, min, max, length);
    value = sliding_control<double>(start, min, max, length);

    cout<<"Value: "<<value;

    return 0;
}
*/

#endif