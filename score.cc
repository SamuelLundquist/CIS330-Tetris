#include <stdlib.h>
#include "definitions.h"
#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Given a new score value, updates to score window
void updateScoreWin()
{
    mvwprintw(scoreWin, 1, 9, "%d", sc.pts);
    mvwprintw(scoreWin, 3, 9, "%d", sc.lns);
    mvwprintw(scoreWin, 5, 9, "%d", sc.level);
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
  sc.pts = 0;
  sc.lns = 0;
  updateScoreWin();
  return;
}

void dis_score()
{
  // display score when the game is over
  ifstream input("highscores.txt");
  int scr;
  input >> scr;
  char ch, str[15];
  delwin(lastWin);
  hScore = newwin(lastWin_height, lastWin_width, lastWin_y, lastWin_x);
  box(hScore, 0, 0);
  mvwprintw(lastWin, 12, lastWin_width/2 - 6, " High Score is: ");
  mvwprintw(lastWin, 14, lastWin_width/2 - 6, " %d ", scr);
  wrefresh(hScore);

  getch();
  //nodelay(stdscr, TRUE);
  endwin();

}

void store_score()
{
  int rank, score, i=0;
  string name;


  dis_score();
 /* ifstream myFile("highscores.txt");


  if(myFile.is_open())
  {
    while(getline(myFile, name))
    {
      mvwprintw(gameWin, 26 + i, (gameWin_width/2)-6, "test

      : %s \n", name);

      i++;
    }
    myFile.close();
  }

    wrefresh(gameWin);*/


}
