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

int main()
{
   initscr();

   WINDOW * gameWin, *scoreWin, *hintWin;
    
   gameWin = newwin(gameWin_height, gameWin_width, gameWin_y, gameWin_x);
   scoreWin = newwin(scoreWin_height, scoreWin_width, scoreWin_y, scoreWin_x);
   hintWin = newwin(hintWin_height, hintWin_width, hintWin_y, hintWin_x);
   refresh();

   box(gameWin,0,0);
   box(scoreWin,0,0);
   box(hintWin,0,0);
   mvwprintw(gameWin, 5, 5, "game window!");
   mvwprintw(scoreWin, 2, 5, "T E T R I S");
   mvwprintw(scoreWin, 15, 6, "Score:");
   mvwprintw(hintWin, 5, 5, "hint window!");

   
   wrefresh(gameWin);
   wrefresh(scoreWin);
   wrefresh(hintWin);

   getch();
   endwin();
   return 0;
}
