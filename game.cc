/*
Tetris Using C++ and ncurses

Authors:
Matthew Struble
Samuel Lundquist
Qi Han
*/
#include <ncurses.h>
#include <iostream>
#include "definitions.h"

using namespace std;

//Where the information for occupancy of cells will be stored
char** block_data;

//Define all windows
WINDOW * gameWin, *scoreWin, *hintWin;


void windowsInit()
{
   gameWin = newwin(gameWin_height, gameWin_width, gameWin_y, gameWin_x);
   scoreWin = newwin(scoreWin_height, scoreWin_width, scoreWin_y, scoreWin_x);
   hintWin = newwin(hintWin_height, hintWin_width, hintWin_y, hintWin_x);

   box(gameWin,0,0);
   box(scoreWin,0,0);
   box(hintWin,0,0);
   mvwprintw(scoreWin, 2, 5, "T E T R I S");
   mvwprintw(hintWin, 1, 3, "hint window!");
   refresh();
   
   wrefresh(gameWin);
   wrefresh(scoreWin);
   wrefresh(hintWin);
   

}

int main()
{
   initscr();

   windowsInit();

   getch();
   endwin();
   return 0;
}

