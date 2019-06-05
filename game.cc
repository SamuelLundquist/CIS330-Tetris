#include <time.h>
#include <thread>
#include "definitions.h"
#include <ncurses.h>

using namespace std;

Queue moveQueue;

int execute(int move);

unsigned int piece_size, numPieces, linePoints, alive, running, min_piece_size, max_piece_size;
int storeAvailable, nextPiece, dropSpeed;

int game()
{
	//if restart selected, game will restart after ending in main
	int restart = 0;

	//set these in the options menu, however default to 4,4
	min_piece_size = 6;
	max_piece_size = 9;

	//seed the random generator with the current internal timer
	srand(time(NULL));

	initPieces(min_piece_size, max_piece_size);
	initGameWindows();
	initBlockData();
	initPieceData();


	//Sets level and score, parameter is level
	initLevelAndScore(1);

	alive = 1;
	running = 1;
	storeAvailable = 1;

	thread dropThread(dropFunc);
	thread inputThread(inputFunc);


	makePiece(genPiece());

	nextPiece = genPiece();

	updateBlockWindow();

	while(alive)
	{
		if(moveQueue.HasMove())
		{
			int move = moveQueue.Dequeue();

			int handle = execute(move);

			//pauseGame returns -1 if quit is selected
			if(handle < 0)
			{
				restart = 1;
			}
			else if(handle)
			{
				updateBlockWindow();
				checkLines();
				updateBlockWindow();
				if (makePiece(nextPiece))
				{
					alive = 0;
					break;
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


	werase(blockWin);                          // remove block window
	wrefresh(blockWin);
	delwin(blockWin);


    mvwprintw(gameWin, 14, (gameWin_width/2)-6, "# Game Over # ");              // game over window
    //dis_score();                                                                // display score
    store_score();           // mvwprintw(gameWin, 18, (gameWin_width/2)-6, "Your score is: xx");
    wrefresh(gameWin);
    getch();

	endwin();

	return restart;
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
		case(PAUSE_GAME):
			running = 0;
			int handle = pauseGame();
			if(handle < 0)
			{
				alive = 0;
				running = 1;
			}
			else if(handle == 0)
			{
				bottomed = -1;
				alive = 0;
				running = 1;
			}
			else
			{
				running = 1;
			}
			break;

	}
	return bottomed;
}

int restartGame()
{
	initscr(); //Init Ncurses
	noecho(); //function does not print input characters
	curs_set(0); //make blinking cursor invisible
	cbreak(); //ctrl + c will stop function
	initColors();
	int restart = game();
	return restart;
}
