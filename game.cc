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
//max index: block_data[blockHeight - 1][blockWidth-1]
char** block_data;

//Define all windows
WINDOW *gameWin, *blockWin, *hintWin, *scoreWin, *controlsWin, *titleWin;

/*
Defines different types of blocks we might have
For starters, we have 7 shapes
Then 4 orientations of that shape
And 4 blocks in that shape

for each value ex) {0,0,0}
corresponds to char x, y, color as defined in struct block
*/
const BLOCK blocks[7][4][4] =
{

   {
        {{2,0,0},{2,1,0},{2,2,0},{2,3,0}},//    0
        {{0,1,0},{1,1,0},{2,1,0},{3,1,0}},//    0
        {{2,0,0},{2,1,0},{2,2,0},{2,3,0}},//    0
        {{0,1,0},{1,1,0},{2,1,0},{3,1,0}} //    0
   },

   {
        {{1,1,1},{1,2,1},{2,1,1},{2,2,1}},//
        {{1,1,1},{1,2,1},{2,1,1},{2,2,1}},//    00
        {{1,1,1},{1,2,1},{2,1,1},{2,2,1}},//    00
        {{1,1,1},{1,2,1},{2,1,1},{2,2,1}} //
   },

   {
        {{0,2,2},{1,1,2},{1,2,2},{2,2,2}},//     0
        {{1,1,2},{2,0,2},{2,1,2},{2,2,2}},//    00
        {{0,1,2},{1,1,2},{1,2,2},{2,1,2}},//     0
        {{1,0,2},{1,1,2},{1,2,2},{2,1,2}} //
   },

   {
        {{0,2,3},{1,1,3},{1,2,3},{2,1,3}},//     0
        {{1,0,3},{1,1,3},{2,1,3},{2,2,3}},//    00
        {{0,2,3},{1,1,3},{1,2,3},{2,1,3}},//    0
        {{1,0,3},{1,1,3},{2,1,3},{2,2,3}} //
   },

   {
        {{0,1,4},{1,1,4},{1,2,4},{2,2,4}},//    0
        {{1,1,4},{1,2,4},{2,0,4},{2,1,4}},//    00
        {{0,1,4},{1,1,4},{1,2,4},{2,2,4}},//     0
        {{1,1,4},{1,2,4},{2,0,4},{2,1,4}} //
   },

   {
        {{0,1,5},{0,2,5},{1,1,5},{2,1,5}},//    00
        {{1,0,5},{1,1,5},{1,2,5},{2,2,5}},//    0
        {{0,2,5},{1,2,5},{2,1,5},{2,2,5}},//    0
        {{1,0,5},{2,0,5},{2,1,5},{2,2,5}} //
   },

   {
        {{0,1,6},{0,2,6},{1,2,6},{2,2,6}},//    00
        {{1,2,6},{2,0,6},{2,1,6},{2,2,6}},//     0
        {{0,1,6},{1,1,6},{2,1,6},{2,2,6}},//     0
        {{1,0,6},{1,1,6},{1,2,6},{2,0,6}} //
   }

};

void initBlockData()
{
    block_data = (char**)malloc(sizeof(char*) * blockWin_height);
    for(int i = 0; i < blockWin_height; i++)
    {
        block_data[i] = (char*)malloc(sizeof(char) * blockWin_width);
        for(int j = 0; j < blockWin_width; j++)
        {
            block_data[i][j] = 0;
        }
    }
}

void freeBlockData()
{
    for(int i = 0; i < blockWin_height; i++)
    {
        free(block_data[i]);
    }
    free(block_data);
}

void initColors()
{
    start_color();
    init_pair(0, COLOR_WHITE, COLOR_BLACK);   //Empty Color
    init_pair(1, COLOR_BLACK, COLOR_CYAN);    //Block 1 Color
    init_pair(2, COLOR_BLACK, COLOR_MAGENTA); //Block 2 Color
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);  //Block 3 Color
    init_pair(4, COLOR_BLACK, COLOR_RED);     //Block 4 Color
    init_pair(5, COLOR_BLACK, COLOR_BLUE);    //Block 5 Color
    init_pair(6, COLOR_BLACK, COLOR_GREEN);   //Block 6 Color
    init_pair(7, COLOR_BLACK, COLOR_WHITE);   //Block 7 Color
    init_pair(10, COLOR_BLACK, COLOR_WHITE);  //Title Color
}

//Given a new score value, updates to score window
void updateScore(SCORE score)
{
    mvwprintw(scoreWin, 2, 9, "%d", score.pts);
    mvwprintw(scoreWin, 4, 9, "%d", score.lns);
    wrefresh(scoreWin);
    move(0, 0);//move cursor back to 0,0 so next input isnt accidentally entered in score window
}

void updateBlockWindow()
{
    for (int y = 0; y < blockWin_height; y++)
    {
        for (int x = 0; x < blockWin_width; x++)
        {
            wattrset(blockWin, COLOR_PAIR(block_data[y][x]));
            mvwprintw(blockWin, y, x * 2, "  ");
        }
    }
    wrefresh(blockWin);
    move(0,0);
}

void initWindows()
{
    gameWin = newwin(gameWin_height, gameWin_width, gameWin_y, gameWin_x);
    blockWin = newwin(blockWin_height, blockWin_width * 2, blockWin_y, blockWin_x);
    scoreWin = newwin(scoreWin_height, scoreWin_width, scoreWin_y, scoreWin_x);
    controlsWin = newwin(controlsWin_height, controlsWin_width, controlsWin_y, controlsWin_x);
    hintWin = newwin(hintWin_height, hintWin_width, hintWin_y, hintWin_x);
    titleWin = newwin(titleWin_height, titleWin_width, titleWin_y, titleWin_x);
    refresh();

    //Init Game Win
    box(gameWin,0,0);
    wrefresh(gameWin);

    //Init Block Win
    wrefresh(blockWin);

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
    mvwprintw(titleWin, 12, 2, " __________");
    mvwprintw(titleWin, 13, 2, "|___    ___|");
    mvwprintw(titleWin, 14, 2, "    |  |");
    mvwprintw(titleWin, 15, 2, "    |  |");
    mvwprintw(titleWin, 16, 2, "    |__|");
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
    mvwprintw(scoreWin, 2, 2, "Score: 0");
    mvwprintw(scoreWin, 4, 2, "Lines: 0");
    wrefresh(scoreWin);

    //Init Controls Win
    box(controlsWin,0,0);
    mvwprintw(controlsWin, 0, 5, " CONTROLS ");
    mvwprintw(controlsWin, 2, 2, "Left: left arr");
    mvwprintw(controlsWin, 4, 2, "Right: right arr");
    mvwprintw(controlsWin, 6, 2, "Drop: down arr");
    mvwprintw(controlsWin, 8, 2, "Rotate: up arr");
    wrefresh(controlsWin);

    move(0, 0);//move cursor back to 0,0
}



int main()
{
   initscr();

   initColors();

   initWindows();

   initBlockData();

   getch();

   //Test for updating score data
   SCORE sc = {1000, 10};
   updateScore(sc);

   //Tests for updating block data
   block_data[0][0] = 3;
   block_data[2][4] = 2;
   block_data[14][20] = 2;
   block_data[32][23] = 3; 
   updateBlockWindow();

   getch();

   freeBlockData();
   
   endwin();
   return 0;
}

