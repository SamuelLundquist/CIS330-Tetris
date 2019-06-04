#include <time.h>
#include <thread>
#include <stdio.h>
#include "definitions.h"

using namespace std;

Queue moveQueue;

int execute(int move);

int alive;

int nextPiece;

void game()
{
	initGameWindows();

	initBlockData();

	initPieceData();

	//Test for updating score data
	updateScore(0, 0);
   
	thread dropThread(dropFunc);

	thread inputThread(inputFunc);

	alive = 1;

	srand(time(NULL));

	makePiece(rand()%7);

	nextPiece = rand()%7;

	updateBlockWindow();

	while(alive) 
	{
		if(moveQueue.HasMove())
		{
			int move = moveQueue.Dequeue();
			if(execute(move))
			{
				updateBlockWindow();
				checkLines();
				updateBlockWindow();
				if (makePiece(nextPiece)) 
				{
					alive = 0;
				}
				nextPiece = rand()%7;
			}
			updateBlockWindow();	
			
		}
	}

	freePieceData();

	freeBlockData();
  


	dropThread.join();
  
	inputThread.join();
	printf("SDLFDSJFKDLFJ");
	fflush(stdout);

	endwin();
	
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
