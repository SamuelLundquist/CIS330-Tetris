#include <stdlib.h>
#include "definitions.h"
#include <ncurses.h>
#include <iostream>

//Given a new score value, updates to score window
void updateScore(SCORE score)
{
    mvwprintw(scoreWin, 2, 9, "%d", score.pts);
    mvwprintw(scoreWin, 4, 9, "%d", score.lns);
    wrefresh(scoreWin);
}


