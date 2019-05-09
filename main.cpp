/*
Tetris Using C++ and ncurses

Authors:
Matthew Struble
Samuel Lundquist
Qi Han
*/
using namespace std;
#include <ncurses.h>

int main()
{
	initscr(); //creates std scr
	WINDOW *win = newwin(12, 20, 15, 10);
	wborder(win, '|', '|', '-','-','+','+','+','+');
	
	mvwin(win, 15, 15);
	wrefresh(win);
	getch();
	delwin(win);
	endwin();
}
