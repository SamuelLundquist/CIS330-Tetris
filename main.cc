/*
Tetris Using C++ and ncurses

Authors:
Matthew Struble
Samuel Lundquist
Qi Han
*/
#include <iostream>
#include "definitions.h"

using namespace std;

unsigned int **block_data;
int setLevel;
int checkerboard = 0;
unsigned int max_piece_size = 4;
unsigned int min_piece_size = 4;
PIECE piece;

SCORE sc = {0,0};

//Define all windows
WINDOW *menuWin, *gameWin, *blockWin, *hintWin, *storeWin, *scoreWin, *controlsWin, *titleWin, *pauseWin, *lastWin, *hScore;

int main()
{
  gameloop:
    int restart = 0;
    int x = menu(); //Returns negative if user decided to quit. Otherwise game will start.

    if( x < 0 )
    {
      endwin();
      return(0);
    }

    restart = game();

    while(restart > 0)
    {
      restart = restartGame();
    }

    if(restart == 0)
    {
      goto gameloop;
    }

  return 0;
}
