#include <stdlib.h>
#include "definitions.h"
#include <ncurses.h>
#include <iostream>

//Given a new score value, updates to score window
void updateScoreWin()
{
    mvwprintw(scoreWin, 2, 9, "%d", sc.pts);
    mvwprintw(scoreWin, 4, 9, "%d", sc.lns);
    wrefresh(scoreWin);
    return;
}

//Given a score struct, points and lines to add, updates score struct.
void updateScore(int points, int lines)
{
    sc.pts += points;
    sc.lns += lines;
    updateScoreWin();
    return;
}
