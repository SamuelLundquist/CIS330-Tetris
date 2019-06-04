#include <time.h>
#include <thread>
#include "definitions.h"

using namespace std;

Queue moveQueue;

int execute(int move);

unsigned int piece_size, numPieces, linePoints, alive, min_piece_size, max_piece_size;
int storeAvailable, nextPiece;

void game()
{
	//set these in the options menu, however default to 4,4
	min_piece_size = 1;
	max_piece_size = 4;	

	initPieces(min_piece_size, max_piece_size);	
	initGameWindows();
	initBlockData();
	initPieceData();

	//Test for updating score data
	updateScore(0, 0);
   
	thread dropThread(dropFunc);
	thread inputThread(inputFunc);

	linePoints = 10;
	alive = 1;

	storeAvailable = 1;

	//seed the random generator with the current internal timer
	srand(time(NULL));

	makePiece(genPiece());

	nextPiece = genPiece();

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
				nextPiece = genPiece();
				storeAvailable = 1;
			}
			updateBlockWindow();	
		}
	}

	freePieces();

	freePieceData();
	freeBlockData();

	dropThread.join();
	inputThread.join();

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
		case(MOVE_RIGHT):
			movePiece(1);
			break;
		case(MOVE_LEFT):
			movePiece(-1);
			break;
		case(ROTATE_BLOCK_CLOCKWISE):
			rotatePiece(1);
			break;
		case(ROTATE_BLOCK_COUNTERCLOCKWISE):
			rotatePiece(-1);
			break;
		case(STORE_PIECE):
			if(storeAvailable)
			{
				storePiece();
				storeAvailable = 0;
			}
			break;

	}
	return bottomed;
	getch();
}
