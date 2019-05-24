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

   //Tests for updating block data
   /*
   block_data[4][0] = 3;
   block_data[4][1] = 4;
   block_data[5][1] = 3;
   block_data[4][19] = 3;
   block_data[5][4] = 2;
   block_data[10][6] = 2;
   block_data[23][9] = 3; 
   updateBlockWindow();
   */

   getch();
   
   for (int i = 0; i < 7; i++) 
   {
      makePiece(i);
	  updateBlockWindow();
	  getch();
	  rotate(1);
	  updateBlockWindow();
	  getch();
	  rotate(1);
	  updateBlockWindow();
	  getch();
	  rotate(1);
	  updateBlockWindow();
	  getch();
	  dropPiece();
	  updateBlockWindow();
	  getch();
	  rotate(1);
	  updateBlockWindow();
	  getch();
	  rotate(-1);
	  updateBlockWindow();
	  getch();
	  dropPiece();
	  updateBlockWindow();
	  getch();
	  rmLine(2);
	  rmLine(3);
	  rmLine(4);
	  rmLine(5);
	  rmLine(6);
	  rmLine(7);
	  rmLine(8);
	  rmLine(9);
   }

   freePieceData();

   freeBlockData();
   
   endwin();
   return 0;
}

