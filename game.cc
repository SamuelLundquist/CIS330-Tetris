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
WINDOW * gameWin, *hintWin, *scoreWin, *controlsWin, *titleWin;

/*
Defines different types of blocks we might have
For starters, we have 7 shapes
Then 4 orientations of that shape
And 4 blocks in that shape
*/
const BLOCK blocks[7][4][4] =
{

   {
        {{2,0},{2,1},{2,2},{2,3}},//    0
        {{0,1},{1,1},{2,1},{3,1}},//    0
        {{2,0},{2,1},{2,2},{2,3}},//    0
        {{0,1},{1,1},{2,1},{3,1}} //    0
   },

   {
        {{1,1},{1,2},{2,1},{2,2}},//
        {{1,1},{1,2},{2,1},{2,2}},//    00
        {{1,1},{1,2},{2,1},{2,2}},//    00
        {{1,1},{1,2},{2,1},{2,2}} //
   },

   {
        {{0,2},{1,1},{1,2},{2,2}},//     0
        {{1,1},{2,0},{2,1},{2,2}},//    00
        {{0,1},{1,1},{1,2},{2,1}},//     0
        {{1,0},{1,1},{1,2},{2,1}} //
   },

   {
        {{0,2},{1,1},{1,2},{2,1}},//     0
        {{1,0},{1,1},{2,1},{2,2}},//    00
        {{0,2},{1,1},{1,2},{2,1}},//    0
        {{1,0},{1,1},{2,1},{2,2}} //
   },

   {
        {{0,1},{1,1},{1,2},{2,2}},//    0
        {{1,1},{1,2},{2,0},{2,1}},//    00
        {{0,1},{1,1},{1,2},{2,2}},//     0
        {{1,1},{1,2},{2,0},{2,1}} //
   },

   {
        {{0,1},{0,2},{1,1},{2,1}},//    00
        {{1,0},{1,1},{1,2},{2,2}},//    0
        {{0,2},{1,2},{2,1},{2,2}},//    0
        {{1,0},{2,0},{2,1},{2,2}} //
   },

   {
        {{0,1},{0,2},{1,2},{2,2}},//    00
        {{1,2},{2,0},{2,1},{2,2}},//     0
        {{0,1},{1,1},{2,1},{2,2}},//     0
        {{1,0},{1,1},{1,2},{2,0}} //
   }

};

void initBlockData()
{
    block_data = (char**)malloc(sizeof(char*) * gameWin_height);
    for(int i = 0; i < gameWin_height; i++)
    {
        block_data[i] = (char*)malloc(sizeof(char) * gameWin_width);
        for(int j = 0; j < gameWin_width; j++)
        {
            block_data[i][j] = 0;
        }
    }
}

void freeBlockData()
{
    for(int i = 0; i < gameWin_height; i++)
    {
        free(block_data[i]);
    }
    free(block_data);
}

void initColors()
{
    start_color();
    init_pair(10, COLOR_BLACK, COLOR_WHITE);
}

void initWindows()
{
    gameWin = newwin(gameWin_height, gameWin_width, gameWin_y, gameWin_x);
    scoreWin = newwin(scoreWin_height, scoreWin_width, scoreWin_y, scoreWin_x);
    controlsWin = newwin(controlsWin_height, controlsWin_width, controlsWin_y, controlsWin_x);
    hintWin = newwin(hintWin_height, hintWin_width, hintWin_y, hintWin_x);
    titleWin = newwin(titleWin_height, titleWin_width, titleWin_y, titleWin_x);
    refresh();

    //Init Game Win
    box(gameWin,0,0);
    wrefresh(gameWin);

    //Init Hint Win
    box(hintWin,0,0);
    mvwprintw(hintWin, 0, 4, " NEXT BLOCK ");
    wrefresh(hintWin);  

    //Init Title Win
    mvwprintw(titleWin, 1, 2,  " __________");
    mvwprintw(titleWin, 2, 2,  "|___    ___|");
    mvwprintw(titleWin, 3, 2,  "    |  |");
    mvwprintw(titleWin, 4, 2,  "    |  |");
    mvwprintw(titleWin, 5, 2,  "    |__|");
    mvwprintw(titleWin, 6, 2,  " __________");
    mvwprintw(titleWin, 7, 2,  "|   _______|");
    mvwprintw(titleWin, 8, 2,  "|  |___");
    mvwprintw(titleWin, 9, 2,  "|   ___|");
    mvwprintw(titleWin, 10, 2, "|  |_______");
    mvwprintw(titleWin, 11, 2, "|__________|");
    mvwprintw(titleWin, 12, 2,  " __________");
    mvwprintw(titleWin, 13, 2,  "|___    ___|");
    mvwprintw(titleWin, 14, 2,  "    |  |");
    mvwprintw(titleWin, 15, 2,  "    |  |");
    mvwprintw(titleWin, 16, 2,  "    |__|");
    mvwprintw(titleWin, 17, 2, " ________");
    mvwprintw(titleWin, 18, 2, "|   ___  \\");
    mvwprintw(titleWin, 19, 2, "|  |___)  |");
    mvwprintw(titleWin, 20, 2, "|   __   /");
    mvwprintw(titleWin, 21, 2, "|  |  \\  \\");
    mvwprintw(titleWin, 22, 2, "|__|   \\__\\");
    mvwprintw(titleWin, 23, 2, " __________");
    mvwprintw(titleWin, 24, 2, "|___    ___|");
    mvwprintw(titleWin, 25, 2, "    |  |");
    mvwprintw(titleWin, 26, 2, " ___|  |___");
    mvwprintw(titleWin, 27, 2, "|__________|");
    mvwprintw(titleWin, 28, 2, " __________");
    mvwprintw(titleWin, 29, 2, "/   _______|");
    mvwprintw(titleWin, 30, 2, "|  (_______");
    mvwprintw(titleWin, 31, 2, "\\_______   \\");
    mvwprintw(titleWin, 32, 2, " _______)  |");
    mvwprintw(titleWin, 33, 2, "|__________/");
    wbkgd(titleWin, COLOR_PAIR(10));
    wrefresh(titleWin);

    //Init Score Win
    box(scoreWin, 0, 0);
    mvwprintw(scoreWin, 0, 6, " SCORE ");
    wrefresh(scoreWin);

    //Init Controls Win
    box(controlsWin,0,0);
    mvwprintw(controlsWin, 0, 5, " CONTROLS ");
    mvwprintw(controlsWin, 2, 2, "Left: left arr");
    mvwprintw(controlsWin, 4, 2, "Right: right arr");
    mvwprintw(controlsWin, 6, 2, "Drop: down arr");
    mvwprintw(controlsWin, 8, 2, "Rotate: up arr");
    wrefresh(controlsWin);

    refresh();
}



int main()
{
   initscr();

   initColors();

   initWindows();

   initBlockData();

   getch();

   freeBlockData();
   
   endwin();
   return 0;
}

