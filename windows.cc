#include <stdlib.h>
#include "definitions.h"
#include <ncurses.h>
#include <iostream>

void initColors()
{
    start_color();
    init_pair(0, COLOR_WHITE, COLOR_BLACK);   //Empty Color
    init_pair(1, COLOR_BLACK, COLOR_CYAN);    //Block 1 Color
    init_pair(2, COLOR_BLACK, COLOR_MAGENTA); //Block 2 Color
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);  //Block 3 Color
    init_pair(4, COLOR_BLACK, COLOR_RED);     //Block 4 Color
    init_pair(5, COLOR_BLACK, COLOR_BLUE);    //Block 5 Color
    init_pair(6, COLOR_BLACK, COLOR_GREEN);   //Block 6 Color
    init_pair(7, COLOR_BLACK, COLOR_WHITE);   //Block 7 Color
    init_pair(10, COLOR_BLACK, COLOR_WHITE);  //Title Color
}

void updateBlockWindow()
{
    for (int y = 4; y < blockWin_height + 4; y++)
    {
        for (int x = 0; x < blockWin_width; x++)
        {
            wattrset(blockWin, COLOR_PAIR(block_data[y][x]));
            mvwprintw(blockWin, 2 * y - 8, x * 4, "    ");
            mvwprintw(blockWin, 2 * y - 7, x * 4, "    ");
	    
	//optional checkerboard pattern
	/*if(block_data[y][x]) {
		for(int i = 0; i < 4; i++) {
			mvwaddch(blockWin, 2*y-8, x*4 + i, ACS_CKBOARD);
		}		
		for(int i = 0; i < 4; i++) {
		mvwaddch(blockWin, 2*y-7, x*4 + i, ACS_CKBOARD);
		}
          }
	    
	  else {	
        	mvwprintw(blockWin, 2 * y - 8, x * 4, "    ");
            	mvwprintw(blockWin, 2 * y - 7, x * 4, "    ");
	  }*/
        }
    }
    wrefresh(blockWin);
}

void initWindows()
{
    gameWin = newwin(gameWin_height, gameWin_width, gameWin_y, gameWin_x);
    blockWin = newwin(blockWin_height * 2, blockWin_width * 4, blockWin_y, blockWin_x);
    scoreWin = newwin(scoreWin_height, scoreWin_width, scoreWin_y, scoreWin_x);
    controlsWin = newwin(controlsWin_height, controlsWin_width, controlsWin_y, controlsWin_x);
    hintWin = newwin(hintWin_height, hintWin_width, hintWin_y, hintWin_x);
    titleWin = newwin(titleWin_height, titleWin_width, titleWin_y, titleWin_x);
    refresh();

    //Init Game Win
    box(gameWin,0,0);
    wrefresh(gameWin);

    //Init Block Win
    wrefresh(blockWin);

    //Init Hint Win
    box(hintWin,0,0);
    mvwprintw(hintWin, 0, 4, " NEXT BLOCK ");
    wrefresh(hintWin);

    //Init Title Win
    mvwprintw(titleWin, 1, 2,  " __________");
    mvwprintw(titleWin, 2, 2,  "|___    ___|");
    mvwprintw(titleWin, 3, 2,  "    |  |");
    mvwprintw(titleWin, 4, 2,  "    |  |");
    mvwprintw(titleWin, 5, 2,  "    |__|");
    mvwprintw(titleWin, 6, 2,  " __________");
    mvwprintw(titleWin, 7, 2,  "|   _______|");
    mvwprintw(titleWin, 8, 2,  "|  |___");
    mvwprintw(titleWin, 9, 2,  "|   ___|");
    mvwprintw(titleWin, 10, 2, "|  |_______");
    mvwprintw(titleWin, 11, 2, "|__________|");
    mvwprintw(titleWin, 12, 2, " __________");
    mvwprintw(titleWin, 13, 2, "|___    ___|");
    mvwprintw(titleWin, 14, 2, "    |  |");
    mvwprintw(titleWin, 15, 2, "    |  |");
    mvwprintw(titleWin, 16, 2, "    |__|");
    mvwprintw(titleWin, 17, 2, " ________");
    mvwprintw(titleWin, 18, 2, "|   ___  \\");
    mvwprintw(titleWin, 19, 2, "|  |___)  |");
    mvwprintw(titleWin, 20, 2, "|   __   /");
    mvwprintw(titleWin, 21, 2, "|  |  \\  \\");
    mvwprintw(titleWin, 22, 2, "|__|   \\__\\");
    mvwprintw(titleWin, 23, 2, " __________");
    mvwprintw(titleWin, 24, 2, "|___    ___|");
    mvwprintw(titleWin, 25, 2, "    |  |");
    mvwprintw(titleWin, 26, 2, " ___|  |___");
    mvwprintw(titleWin, 27, 2, "|__________|");
    mvwprintw(titleWin, 28, 2, " __________");
    mvwprintw(titleWin, 29, 2, "/   _______|");
    mvwprintw(titleWin, 30, 2, "|  (_______");
    mvwprintw(titleWin, 31, 2, "\\_______   \\");
    mvwprintw(titleWin, 32, 2, " _______)  |");
    mvwprintw(titleWin, 33, 2, "|__________/");
    wbkgd(titleWin, COLOR_PAIR(10));
    wrefresh(titleWin);

    //Init Score Win
    box(scoreWin, 0, 0);
    mvwprintw(scoreWin, 0, 6, " SCORE ");
    mvwprintw(scoreWin, 2, 2, "Score: 0");
    mvwprintw(scoreWin, 4, 2, "Lines: 0");
    wrefresh(scoreWin);

    //Init Controls Win
    box(controlsWin,0,0);
    mvwprintw(controlsWin, 0, 5, " CONTROLS ");
    mvwprintw(controlsWin, 2, 2, "Left: left arr");
    mvwprintw(controlsWin, 4, 2, "Right: right arr");
    mvwprintw(controlsWin, 6, 2, "Drop: down arr");
    mvwprintw(controlsWin, 8, 2, "Rotate: up arr");
    wrefresh(controlsWin);
}
