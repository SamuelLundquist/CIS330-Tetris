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

void initControls()
{
    controlsWin = newwin(controlsWin_height, controlsWin_width, controlsWin_y - 2, controlsWin_x - 4);

    box(controlsWin,0,0);
    mvwprintw(controlsWin, 0, 5, " CONTROLS ");
    mvwprintw(controlsWin, 2, 2, "Left: A");
    mvwprintw(controlsWin, 4, 2, "Right: D");
    mvwprintw(controlsWin, 6, 2, "Drop: SPACE");
    mvwprintw(controlsWin, 8, 2, "Rotate: W");
    wrefresh(controlsWin);
}

int menu()
{
    initscr(); //Init Ncurses
    noecho(); //function does not print input characters
    curs_set(0); //make blinking cursor invisible
    cbreak(); //ctrl + c will stop function
    initColors();
    initMenu();

    char ch;
    int i, numItems, numControls;
    numControls = 5;
    numItems = 3;
    char options[numItems][15] = {"PLAY GAME","CONTROLS","QUIT"};
    //Spaces keep control options centered, don't remove plz.
    char controls[numControls][25] = {"     Left: A  ", "    Right: D  ", " Rotate Right: W", "  Rotate Left: S", "Drop Block: SPACE"};
    char option[15];
    char control[25];

    for ( i = 0; i < numItems; i++)
    {
        if (i==0)
            wattron(menuWin, A_STANDOUT);
        else
            wattroff(menuWin, A_STANDOUT);
        sprintf(option, "%s", options[i]);
        mvwprintw(menuWin, i*3+9, 27, "%s", option);
    }

	i=0;
    wrefresh(menuWin);

    keypad( menuWin, TRUE ); //use wgetch() for menu, fetches character with respect to menu window
    while(ch = wgetch(menuWin))
    {
        //Updates options so only one option is highlighted at a time
        sprintf(option, "%s",  options[i]);
		mvwprintw(menuWin, i*3+9, 27, "%s", option);

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

                //Play game was selected, erase menu window and return 1
                if ( i == 0 )
                {
                    werase(menuWin);
                    wrefresh(menuWin);
                    delwin(menuWin);
                    return 1;
                }

                //Controls selected, load controls guide
                else if ( i == 1 )
                {
                    int x;
                    for ( x = 0; x < numControls; x++) //print controls to menu window
		    {
                        sprintf(control, "%s", controls[x]);
                        mvwprintw(menuWin, x*3+6, 24, "%s", control);
                    }
                    mvwprintw(menuWin, 30, 18, "--Press any key to go back --");
                    wrefresh(menuWin);
                    getch();    // Once finished reading, hit any key to go back to main menu
                    werase(menuWin); //Clears the menu window
                    initMenu(); //Initializes fresh menu window
                    for ( x = 0; x < numItems; x++) // Add menu options to window, highlight currently selected option with x == i
                    {
                        if (x==i)
                            wattron(menuWin, A_STANDOUT);
                        else
                            wattroff(menuWin, A_STANDOUT);
                        sprintf(option, "%s", options[x]);
                        mvwprintw(menuWin, x*3+9, 27, "%s", option);
                    }
                    wrefresh(menuWin); //Refresh window
                    keypad( menuWin, TRUE ); //Keeps menu from exiting while loop upon return to main from controls menu
                    break;
                }

                //Quit selected, return negative value, should close program in main()
                else if ( i == 2 )
                {
                    return -1;
                }

                //Input was not an expected input, break and try again
                else
                {
                    break;
                }

            //ESC was pressed, return negative value, should close program in main()
            case EXIT:
                return -1;
        }
        //Updates the current highlighted option in menu
        wattron(menuWin, A_STANDOUT);
		sprintf(option, "%s",  options[i]);
		mvwprintw(menuWin, i*3+9, 27, "%s", option);
		wattroff(menuWin, A_STANDOUT);
    }
    //Shouldn't reach this point.
    return -2;
}


void initMenu()
{
    menuWin = newwin(titleWin_height, menuWin_width, menuWin_y, menuWin_x);
    titleWin = newwin(titleWin_height, titleWin_width, titleWin_y, titleWin_x);
    refresh();

    //Init menuWin
    box(menuWin, 0, 0);
    mvwprintw(menuWin, 0, 27, " MAIN MENU ");
    mvwprintw(menuWin, titleWin_height - 1, (menuWin_width - 49)/2, " ESC - EXIT | SELECT - ENTER | W - UP | S - DOWN ");
    wrefresh(menuWin);

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
}

void initGameWindows()
{

    gameWin = newwin(gameWin_height, gameWin_width, gameWin_y, gameWin_x);
    blockWin = newwin(blockWin_height * 2, blockWin_width * 4, blockWin_y, blockWin_x);
    scoreWin = newwin(scoreWin_height, scoreWin_width, scoreWin_y, scoreWin_x);
    controlsWin = newwin(controlsWin_height, controlsWin_width, controlsWin_y, controlsWin_x);
    hintWin = newwin(hintWin_height, hintWin_width, hintWin_y, hintWin_x);
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

    //Init Score Win
    box(scoreWin, 0, 0);
    mvwprintw(scoreWin, 0, 6, " SCORE ");
    mvwprintw(scoreWin, 2, 2, "Score: 0");
    mvwprintw(scoreWin, 4, 2, "Lines: 0");
    mvwprintw(scoreWin, 6, 2, "Level: 0");
    wrefresh(scoreWin);

    //Init Controls Win
    box(controlsWin,0,0);
    mvwprintw(controlsWin, 0, 5, " CONTROLS ");
    mvwprintw(controlsWin, 2, 2, "Left: A");
    mvwprintw(controlsWin, 4, 2, "Right: D");
    mvwprintw(controlsWin, 6, 2, "Drop: SPACE");
    mvwprintw(controlsWin, 8, 2, "Rotate: W");
    wrefresh(controlsWin);
}

void pauseGame()
{
    pauseWin = newwin(pauseWin_height, pauseWin_width, pauseWin_y, pauseWin_x);
    box(pauseWin,0,0);
    mvwprintw(pauseWin, 0, pauseWin_width/2 - 4, " PAUSED ");
    wrefresh(pauseWin);
    getch();
    werase(pauseWin);
    wrefresh(pauseWin);
    delwin(pauseWin);
    updateBlockWindow();

}
