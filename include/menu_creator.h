#ifndef MENU_CREATOR
#define MENU_CREATOR
#include<iostream>
#include<conio.h>
#include<windows.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

#ifndef GOTOXY
#define GOTOXY
struct position	//	structure of position, used for specifing the cursor position
{
	int x,y;
};

void gotoxy(position pos)
{
	CursorPosition.X = pos.x; // Locates column
	CursorPosition.Y = pos.y; // Locates Row
	SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed
}
#endif

int menu(position str_pos, char menu_items[][260], int no_items, int gap=0)	//	the actual function
{
	int ac_gap=gap+1;	//	actual gap provides the next line

	position m;	//	used in printing the menu
	gotoxy(str_pos);	//	sets cursor to the starting point
	m=str_pos;

	for(int i=0; i<no_items; i++)	//	loop to print the menu items
	{
		cout<<"   ";	//	intial space for the menu handler '->'
		cout<<menu_items[i];	//	printing array of strings

		for(int i=0; i<ac_gap; i++)	//	loop to print newline for the appropriate gaps
			cout<<endl;

		m.y+=ac_gap;
		gotoxy(m);
	}

	gotoxy(str_pos);
	cout<<"->";	//	printing the menu handler

	position ctr, ret;	//	the control and return postion respectively
						/*	the contol postion holds the instantaneous cursor postion and,
							the return postion hold the fixed postion where the cursor is moved
							while returning from the function
						*/

	ctr=str_pos;
	int menu_id=0;	/*	this menu id hold the value of the menu item selected.
						the first items has a menu id: 0(zero)
					*/

	while(1)	//	seems to be an infinite loop
	{
		/*	setting the postion of return variable and the cursor is moved	*/
		ret.x=str_pos.x+2;
		ret.y=str_pos.y+((no_items-1)*ac_gap)+2;
		gotoxy(ret);

		system("pause>nul"); //	the >nul bit causes it the print no message

		if(GetAsyncKeyState(VK_DOWN)) //	down button pressed
		{
			if(menu_id>=0 && menu_id<(no_items-1))	//	checking legal menu id
			{
				gotoxy(ctr);
				cout<<"  ";	//	printing space on the previous loction of the menu handler
				ctr.y+=ac_gap;	//	new location for the menu handler
				gotoxy(ctr);
				cout<<"->";	//	printing the menu handler in the new loaction
				menu_id++;	//menu id changed
			}

		}

		else if(GetAsyncKeyState(VK_UP)) //	up button pressed
		{
			if(menu_id>0 && menu_id<no_items)	//	checkin legal menu id
			{
				gotoxy(ctr);
				cout<<"  ";	//	printing space on the previous loction of the menu handler
				ctr.y-=ac_gap;	//	new location for the menu handler
				gotoxy(ctr);
				cout<<"->";	//	printing the menu handler in the new loaction
				menu_id--;	//menu id changed
			}
		}

		else if(GetAsyncKeyState(VK_RETURN))	//	return(ENTER) button pressed
			return menu_id;
	}
}

/*	NOTE: x and y postion elements are based on the coordinate system
		It looks like as if the whole program is in the 4th quadrant
		(0,0)	x(1)	x(2)	x(3)	.	.	.
		y(1)
		y(2)
		y(3)
		.
		.
		.
	*/


/*	SAMPLE MAIN function
int main()
{


	position str;
	str.x=0;
	str.y=0;

	int no_items=7;
	char menu_items[no_items][260]={"Apples","Bananas","Grapes","Guava","Potato","Tomato","Ginger"};
	int menu_id;
	int gap=1;

	menu_id=menu(str, menu_items, no_items, gap);

	cout<<"You entered menu_id: "<<menu_id;

	return 0;
}
*/

#endif