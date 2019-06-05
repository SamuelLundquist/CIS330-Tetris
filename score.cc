#include <stdlib.h>
#include "definitions.h"
#include <ncurses.h>
#include <iostream>

//Given a new score value, updates to score window
void updateScoreWin()
{
    mvwprintw(scoreWin, 2, 9, "%d", sc.pts);
    mvwprintw(scoreWin, 4, 9, "%d", sc.lns);
    mvwprintw(scoreWin, 6, 9, "%d", sc.level);
    wrefresh(scoreWin);
    return;
}

//Given a score struct, points and lines to add, updates score struct.
void updateScore(int points, int lines)
{
    sc.pts += points;
    sc.lns += lines;

    //Every 10 lines, change level
    if(lines && !(sc.lns % 10))
    {
      updateLevel();
    }
    updateScoreWin();
    return;
}

void updateLevel()
{
  sc.level++;
  linePoints = 10 * sc.level;

  //If in range increase level speed, else keep speed the same.
  if(sc.level-1 < levels)
  {
    dropSpeed = levelSpeed[sc.level-1];
  }
  return;
}

void initLevelAndScore(int level)
{
  //If statement to handle unexpected level input
  if(level > 0 && level <= levels)
  {
    sc.level = level;
  }
  else
  {
    sc.level = 1;
  }
  dropSpeed = levelSpeed[sc.level-1];
  linePoints = 10 * level;
  updateScore(0,0);
  return;
}
