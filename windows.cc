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

	        if(checkerboard)
            {
                if(block_data[y][x]) {
                    for(int i = 0; i < 4; i++) {
                        mvwaddch(blockWin, 2*y-8, x*4 + i, ACS_CKBOARD);
                        mvwaddch(blockWin, 2*y-7, x*4 + i, ACS_CKBOARD);
                    }
                }

                else 
                {
                    mvwprintw(blockWin, 2 * y - 8, x * 4, "    ");
                    mvwprintw(blockWin, 2 * y - 7, x * 4, "    ");
                }
            }
        }
    }
    wrefresh(blockWin);
}
                    


void initGameWindows()
{

    gameWin = newwin(gameWin_height, gameWin_width, gameWin_y, gameWin_x);
    blockWin = newwin(blockWin_height * 2, blockWin_width * 4, blockWin_y, blockWin_x);
    scoreWin = newwin(scoreWin_height, scoreWin_width, scoreWin_y, scoreWin_x);
    controlsWin = newwin(controlsWin_height, controlsWin_width, controlsWin_y, controlsWin_x);
    hintWin = newwin(hintWin_height, hintWin_width, hintWin_y, hintWin_x);
    storeWin = newwin(storeWin_height, storeWin_width, storeWin_y, storeWin_x);
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

    //Init Store Win
    box(storeWin,0,0);
    mvwprintw(storeWin, 0, 4, " STORE BLOCK ");
    wrefresh(storeWin);

    //Init Score Win
    box(scoreWin, 0, 0);
    mvwprintw(scoreWin, 0, 6, " SCORE ");
    mvwprintw(scoreWin, 1, 2, "Score: 0");
    mvwprintw(scoreWin, 3, 2, "Lines: 0");
    mvwprintw(scoreWin, 5, 2, "Level: 0");
    wrefresh(scoreWin);

    //Init Controls Win
    box(controlsWin,0,0);
    mvwprintw(controlsWin, 0, 5, " CONTROLS ");
    mvwprintw(controlsWin, 1, 2, "Left: A");
    mvwprintw(controlsWin, 3, 2, "Right: D");
    mvwprintw(controlsWin, 5, 2, "Right Rotate: W");
    mvwprintw(controlsWin, 7, 2, "Left Rotate: S");
    mvwprintw(controlsWin, 9, 2, "Drop: SPACE");
    mvwprintw(controlsWin, 11, 2, "Pause: P");
    wrefresh(controlsWin);
}

int pauseGame()
{
    pauseWin = newwin(pauseWin_height, pauseWin_width, pauseWin_y, pauseWin_x);
    box(pauseWin,0,0);
    mvwprintw(pauseWin, 0, pauseWin_width/2 - 4, " PAUSED ");

    char ch;
    int i, numItems;
    numItems = 3;
    char options[numItems][15] = {"Resume", "Restart", "Quit"};
    char option[15];

    for (i = 0; i < numItems; i++)
    {
      if(i == 0)
        wattron(pauseWin, A_STANDOUT);
      else
        wattroff(pauseWin, A_STANDOUT);
      sprintf(option, "%s", options[i]);
      mvwprintw(pauseWin, i*2+2, pauseWin_width/2-3, "%s", option);
    }
    i = 0;
    wrefresh(pauseWin);

    keypad(pauseWin, TRUE);
    while(ch = wgetch(pauseWin))
    {
      //Updates options so only one option is highlighted at a time
      sprintf(option, "%s", options[i]);
      mvwprintw(pauseWin, i*2+2, pauseWin_width/2-3, "%s", option);

      switch(ch)
      {
        case MENU_UP:
            i--;
            if( i < 0 ) { i = numItems - 1; }
            break;

        case MENU_DOWN:
            i++;
            if ( i >= numItems ) { i = 0; }
            break;

        case MENU_SELECT:

            //Resume was selected, unpause game, erase menu window and return 1
            if ( i == 0 )
            {
                werase(pauseWin);
                wrefresh(pauseWin);
                delwin(pauseWin);
                return 1;
            }

            //Restar sleected, remove window and return 0
            else if ( i == 1)
            {
                werase(pauseWin);
                wrefresh(pauseWin);
                delwin(pauseWin);
                return 0;
            }

            //Quit selected, return negative value
            else if ( i == 2 )
            {
                werase(pauseWin);
                wrefresh(pauseWin);
                delwin(pauseWin);
                return -1;
            }

        //ESC was pressed, unpause game, erase menu window and return 1
        case EXIT:
          werase(pauseWin);
          wrefresh(pauseWin);
          delwin(pauseWin);
          return 1;
      }
      wattron(pauseWin, A_STANDOUT);
      sprintf(option, "%s",  options[i]);
      mvwprintw(pauseWin, i*2+2, pauseWin_width/2-3, "%s", option);
      wattroff(pauseWin, A_STANDOUT);

    }
    return 1;
}

//returns the minimum x value and next piece size so display function can know how to align piece
int* findpdata(int pnum)
{
	int minx = 9;
	int i = 0;
	int val;	

	while((val = pieces[pnum][2*i+3]) != -1 && i < max_piece_size)
	{
		if(val < minx)
		{
			minx = val;
		}
		i+=1;
	}
	int* ret = new int[2];
	ret[0] = minx;
	ret[1] = i;
	return(ret);
}

void dispPiece(WINDOW* win, int pnum) 
{

	int* pdata = findpdata(pnum);
	int** tgraph = new int*[8];
	//make a temporary graph of the piece and clear the window
	wattrset(win, COLOR_PAIR(0));
	for(int i = 0; i < 8; i++)
	{
		tgraph[i] = new int[8];
		for(int j = 0; j < 8; j++)
		{
			tgraph[i][j] = 0;
		}
		mvwprintw(win, i+1, 1, "                 ");
	}
	
	//insert the piece into the subgraph
	for(int i = 0; i < pdata[1]; i++)
	{
		tgraph[pieces[pnum][2*i+4]-4][pieces[pnum][2*i+3]-pdata[0]] = 1;
	}

	

	wattrset(win, COLOR_PAIR(pieces[pnum][0]));
	//if the piece is too big to display as a small piece
	if(pdata[1] > 4)
	{
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				if(tgraph[i][j])
				{
					mvwprintw(win, i + 1, 2*j + 2, "  ");
				}
			}
		}
	}
	else
	{
		for(int i = 0; i < 4; i++)
		{	
			for(int j = 0; j < 4; j++) {
				if(tgraph[i][j]){
					mvwprintw(win, 2*i + 1 ,4*j + 2, "    ");
					mvwprintw(win, 2*i + 2 ,4*j + 2, "    ");
				}	
			}
		}
	}
	delete pdata;
	wrefresh(win);
	for(int i = 0; i < 8; i++)
	{
		delete tgraph[i];
	}
	delete tgraph;
}


 
