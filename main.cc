/*
Tetris Using C++ and ncurses

Authors:
Matthew Struble
Samuel Lundquist
Qi Han
*/
#include <ncurses.h>
#include <iostream>
#include <time.h>
#include <thread>
#include "definitions.h"

using namespace std;

unsigned int **block_data;
PIECE piece;

//Define all windows
WINDOW *gameWin, *blockWin, *hintWin, *scoreWin, *controlsWin, *titleWin;

int main()
{
   initscr();

   cbreak(); //ctrl + c will stop function

   noecho(); //function does not print input characters

   curs_set(0); //make blinking cursor invisible

   initColors();

   initWindows();

   initBlockData();

   initPieceData();

   getch();

   //Test for updating score data
   SCORE sc = {1000, 10};
   updateScore(sc);

   thread dropThread(dropFunc);

   thread inputThread(inputFunc);

   getch();

   makePiece(1);
   updateBlockWindow();
   block_data[19][8] = 3;
   block_data[19][6] = 2;
   block_data[20][8] = 2;
   block_data[20][6] = 3;
   block_data[21][8] = 3;
   block_data[21][6] = 2;
   for(int x = 0; x < blockWin_width; x++)
 	 {
 	  block_data[22][x] = 1;
 	 }
   block_data[22][3] = 0;
   block_data[22][4] = 0;
   block_data[22][5] = 0;
   block_data[23][6] = 2;

   updateBlockWindow();
   getch();
   for (int i = 0; i < 18; i++)
   {
     dropPiece();
   }
   updateBlockWindow();
   getch();
   checkLines();
   updateBlockWindow();
   getch();
   freePieceData();

   freeBlockData();

   endwin();

   dropThread.join();

   inputThread.join();

   return 0;
}
