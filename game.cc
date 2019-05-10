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

void windowsInit()
{
    gameWin = newwin(gameWin_height, gameWin_width, gameWin_y, gameWin_x);
    scoreWin = newwin(scoreWin_height, scoreWin_width, scoreWin_y, scoreWin_x);
    controlsWin = newwin(controlsWin_height, controlsWin_width, controlsWin_y, controlsWin_x);
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

   windowsInit();

   initBlockData();

   getch();

   freeBlockData();
   
   endwin();
   return 0;
}

