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
WINDOW * gameWin, *scoreWin, *hintWin, *titleWin;


void windowsInit()
{
    gameWin = newwin(gameWin_height, gameWin_width, gameWin_y, gameWin_x);
    scoreWin = newwin(scoreWin_height, scoreWin_width, scoreWin_y, scoreWin_x);
    hintWin = newwin(hintWin_height, hintWin_width, hintWin_y, hintWin_x);
    titleWin = newwin(titleWin_height, titleWin_width, titleWin_y, titleWin_x);
    refresh();

    //Init Box Win
    box(gameWin,0,0);
    wrefresh(gameWin);

    //Init Hint Win
    box(hintWin,0,0);
    mvwprintw(hintWin, 0, 4, " NEXT BLOCK ");
    wrefresh(hintWin);  

    //Init Title Win
    mvwprintw(titleWin, 1, 0,  " __________");
    mvwprintw(titleWin, 2, 0,  "|___    ___|");
    mvwprintw(titleWin, 3, 0,  "    |  |");
    mvwprintw(titleWin, 4, 0,  "    |  |");
    mvwprintw(titleWin, 5, 0,  "    |__|");
    mvwprintw(titleWin, 6, 0,  " __________");
    mvwprintw(titleWin, 7, 0,  "|    ______|");
    mvwprintw(titleWin, 8, 0,  "|  |___");
    mvwprintw(titleWin, 9, 0,  "|   ___|");
    mvwprintw(titleWin, 10, 0, "|  |_______");
    mvwprintw(titleWin, 11, 0, "|__________|");
    mvwprintw(titleWin, 12, 0,  " __________");
    mvwprintw(titleWin, 13, 0,  "|___    ___|");
    mvwprintw(titleWin, 14, 0,  "    |  |");
    mvwprintw(titleWin, 15, 0,  "    |  |");
    mvwprintw(titleWin, 16, 0,  "    |__|");
    mvwprintw(titleWin, 17, 0, " ________");
    mvwprintw(titleWin, 18, 0, "|   ___  \\");
    mvwprintw(titleWin, 19, 0, "|  |___)  |");
    mvwprintw(titleWin, 20, 0, "|   __   /");
    mvwprintw(titleWin, 21, 0, "|  |  \\  \\");
    mvwprintw(titleWin, 22, 0, "|__|   \\__\\");
    mvwprintw(titleWin, 23, 0, " __________");
    mvwprintw(titleWin, 24, 0, "|___    ___|");
    mvwprintw(titleWin, 25, 0, "    |  |");
    mvwprintw(titleWin, 26, 0, " ___|  |___");
    mvwprintw(titleWin, 27, 0, "|__________|");
    mvwprintw(titleWin, 28, 0, " __________");
    mvwprintw(titleWin, 29, 0, "/   _______|");
    mvwprintw(titleWin, 30, 0, "|  (_______");
    mvwprintw(titleWin, 31, 0, "\\_______   \\");
    mvwprintw(titleWin, 32, 0, " _______)  |");
    mvwprintw(titleWin, 33, 0, "|__________/");
    wrefresh(titleWin);

    //Init Score Win
    box(scoreWin,0,0);
    mvwprintw(scoreWin, 19, 5, "Controls:");
    mvwprintw(scoreWin, 20, 2, "Left: left arr");
    mvwprintw(scoreWin, 21, 2, "Right: right arr");
    mvwprintw(scoreWin, 22, 2, "Drop: down arr");
    mvwprintw(scoreWin, 23, 2, "Rotate: up arr");
    wrefresh(scoreWin);

    refresh();
}



int main()
{
   initscr();

   windowsInit();

   getch();
   endwin();
   return 0;
}

