/*
Tetris Using C++ and ncurses

Authors:
Matthew Struble
Samuel Lundquist
Qi Han
*/
#include <ncurses.h>
using namespace std;

int main(){

   int height,width, start_x, start_y;
   height = 35;    
   width = 50; 
   start_x = start_y = 1;


   initscr();

   WINDOW * gameWin, *scoreWin, *hintWin;
    
   gameWin = newwin(height, width, start_y, start_x);
   scoreWin = newwin(10,20, 1, 60);
   hintWin = newwin(10,20, 25, 55);
   refresh();

   box(gameWin,0,0);
   box(scoreWin,0,0);
   box(hintWin,0,0);
   mvwprintw(gameWin, 5, 5, "game window!");
   mvwprintw(scoreWin, 5, 5, "hint window!");
   mvwprintw(hintWin, 5, 5, "score window!");

  // move(y,x);
   //printw("yo sup!\n");
   wrefresh(gameWin);
   wrefresh(scoreWin);
   wrefresh(hintWin);

   int c = getch();
  // getch();
   endwin();
   return 0;
}

