/*
Tetris Using C++ and ncurses

Authors:
Matthew Struble
Samuel Lundquist
Qi Han
*/
#include <ncurses.h>
#include <iostream>
#include <time.h>
#include <thread>
#include "definitions.h"

using namespace std;

unsigned int **block_data;
PIECE piece;
SCORE sc = {0,0};

//Define all windows
WINDOW *menuWin, *gameWin, *blockWin, *hintWin, *scoreWin, *controlsWin, *titleWin;

int main()
{
   int x = menu(); //Returns negative if user decided to quit. Otherwise game will start.

   if( x < 0 )
   {
       cout << x << endl;
       endwin();
       return(0);
   }

   initGameWindows();

   initBlockData();

   initPieceData();

   getch();

   //Test for updating score data
   updateScore(1000, 10);

   thread dropThread(dropFunc);

   thread inputThread(inputFunc);

   getch();

   makePiece(1);
   updateBlockWindow();
   block_data[19][8] = 3;
   block_data[19][6] = 2;
   block_data[20][8] = 2;
   block_data[20][6] = 3;
   block_data[21][8] = 3;
   block_data[21][6] = 2;
   for(int x = 0; x < blockWin_width; x++)
 	 {
 	  block_data[22][x] = 1;
 	 }
   block_data[22][3] = 0;
   block_data[22][4] = 0;
   block_data[22][5] = 0;
   block_data[23][6] = 2;

   updateBlockWindow();
   getch();
   for (int i = 0; i < 18; i++)
   {
     dropPiece();
   }
   updateBlockWindow();
   getch();

   checkLines();
   updateBlockWindow();
   getch();
   freePieceData();

   freeBlockData();

   endwin();

   dropThread.join();

   inputThread.join();

   return 0;
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
    keypad( menuWin, TRUE );

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
