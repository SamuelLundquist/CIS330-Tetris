#include <time.h>
#include <thread>
#include "definitions.h"

using namespace std;

Queue moveQueue;

int execute(int move);

void game()
{
	initGameWindows();

	initBlockData();

	initPieceData();

	//Test for updating score data
	updateScore(1000, 10);
   
	thread dropThread(dropFunc);

	thread inputThread(inputFunc);

	int alive = 1;

	makePiece(1);

	while(alive) 
	{
		if(moveQueue.HasMove())
		{
			int move = moveQueue.Dequeue();
			execute(move);
		updateBlockWindow();	
		}
	}
/*
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
   */
	freePieceData();

	freeBlockData();
  
	endwin();

	dropThread.join();
   
	inputThread.join();

	return;
}


int execute(int move) 
{
	int bottomed = 0;
	switch(move){
		case(DROP_BLOCK): 
			bottomed = dropPiece();	
			break;
		case(AUTO_DROP):
			bottomed = dropPiece();
			break;
		case(ROTATE_BLOCK_CLOCKWISE):
			rotatePiece(1);
			break;
		case(ROTATE_BLOCK_COUNTERCLOCKWISE):
			rotatePiece(-1);
			break;
		case(MOVE_RIGHT):
			movePiece(1);
			break;
		case(MOVE_LEFT):
			movePiece(-1);
			break;
	}
	return bottomed;
	getch();
}