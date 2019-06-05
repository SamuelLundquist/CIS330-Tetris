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
PIECE piece;
SCORE sc = {0,0};

//Define all windows
WINDOW *menuWin, *gameWin, *blockWin, *hintWin, *scoreWin, *controlsWin, *titleWin, *pauseWin, *lastWin;

int main()
{
  int restart = 0;
  int x = menu(); //Returns negative if user decided to quit. Otherwise game will start.

  if( x < 0 )
  {
      cout << x << endl;
      endwin();
      return(0);
  }

  restart = game();

  while(restart)
  {
     restart = restartGame();
  }

  return 0;
}
