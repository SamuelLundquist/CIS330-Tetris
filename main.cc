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
