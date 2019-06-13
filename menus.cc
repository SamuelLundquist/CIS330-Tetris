#include <stdlib.h>
#include <ncurses.h>
#include <iostream>
#include "definitions.h"

const int numItems = 4;
const char options[numItems][15] = {"PLAY GAME","CONTROLS","SETTINGS","QUIT"};

int menu()
{
    initscr(); //Init Ncurses
    noecho(); //function does not print input characters
    curs_set(0); //make blinking cursor invisible
    cbreak(); //ctrl + c will stop function
    initColors();
    initMenu();

    //ch = inputted character by user to move over window
    //i = row of menu selected
    char ch;
    int i;
    
    //the currently selected option in menu to be printed with highlighted text
    char option[15];

    //print all options, the cursor automatically starts at the top element
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
		//if reached the top, wrap back around
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
                    if(levelSelect())
                        return 1;
                    printOptions(0);
                    break;
                }

                //Controls selected, load controls guide
                else if ( i == 1 )
                {
		    //print controls guide
                    printControls();
		    //return to options menu with same cursor selected
                    printOptions(1);
                    break;
                }

                //Settings selected, open settings menu
                else if ( i == 2 )
                {
                    
                    settingsMenu();
                    printOptions(2);
                    break;
                }

                //Quit selected, return negative value, should close program in main()
                else if ( i == 3 )
                {
                    return -1;
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
        wrefresh(menuWin);
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

int levelSelect()
{
                    char ch;
                    int level = 1;
                    char lvl[5];
                    werase(menuWin);
                    initMenu(); //Initializes fresh menu window
                    mvwprintw(menuWin, menuWin_height/2, menuWin_width/2-10, "Level Select:");
                    wattron(menuWin, A_STANDOUT);
                    mvwprintw(menuWin, menuWin_height/2-4, menuWin_width/2+6, "w");
                    mvwprintw(menuWin, menuWin_height/2+4, menuWin_width/2+6, "s");
                    wattroff(menuWin, A_STANDOUT);
                    mvwprintw(menuWin, menuWin_height/2-2, menuWin_width/2+6, "|");
                    sprintf(lvl, "%d ",  level);
                    mvwprintw(menuWin, menuWin_height/2, menuWin_width/2+6, lvl);
                    mvwprintw(menuWin, menuWin_height/2+2, menuWin_width/2+6, "|");
                    wrefresh(menuWin);


                    while(ch = wgetch(menuWin))
                    {
                        int exit = 0;
                        switch(ch)
                        {
                            case(MENU_UP):
                                if(level == levels)
                                    level = 1;
                                else
                                    level++;
                                sprintf(lvl, "%d ",  level);
                                mvwprintw(menuWin, menuWin_height/2, menuWin_width/2+6, lvl);
                                wrefresh(menuWin);
                                break;

                            case(MENU_DOWN):
                                if(level == 1)
                                    level = levels;
                                else
                                    level--;
                                sprintf(lvl, "%d ",  level);
                                mvwprintw(menuWin, menuWin_height/2, menuWin_width/2+6, lvl);
                                wrefresh(menuWin);
                                break;

                            case(MENU_SELECT):
                                exit = 1;
                                setLevel = level;
                                werase(menuWin);
                                wrefresh(menuWin);
                                delwin(menuWin);
                                return 1;

                            case(EXIT):
                                exit = 1;
                                break;
                        }
                        if(exit)
                        {
                            break;
                        }  
                    }
                    return 0;
}

void printOptions(int i)
{
    char option[15];
    initMenu();
    for ( int x = 0; x < 4; x++) // Add menu options to window, highlight currently selected option with x == i
    {
        if (x==i)
            wattron(menuWin, A_STANDOUT);
        else
            wattroff(menuWin, A_STANDOUT);
    sprintf(option, "%s", options[x]);
    mvwprintw(menuWin, x*3+9, 27, "%s", option);
    }
    wrefresh(menuWin); //Refresh window
}

void printControls()
{
    char controls[6][25] = {"    Left: A ", "   Right: D   ", "Rotate Right: W  ", "Rotate Left: S  ", "Drop Block: SPACE  ", "Store Block: F  "};
    char control[25];
    int x;
    for ( x = 0; x < 6; x++) //print controls to menu window
    {
        sprintf(control, "%s", controls[x]);
        mvwprintw(menuWin, x*3+6, 25, "%s", control);
    }
    mvwprintw(menuWin, 30, 18, "--Press any key to go back --");
    wrefresh(menuWin);
    wgetch(menuWin);    // Once finished reading, hit any key to go back to main menu
}

void settingsMenu()
{
    char ch;
    int numSettings = 4;
    char setting[25];
    int x, finished;
    char settings[numSettings][20] = {"Max Block Size:", "Min Block Size:", "Checkerboard Theme:", "Apply Changes"};
    initMenu(); //Initializes fresh menu window
    for ( x = 0; x < numSettings; x++) //print settings to menu window
    {
        if(x == 0)
        {
            wattron(menuWin, A_STANDOUT);
        }
        else
        {
            wattroff(menuWin, A_STANDOUT);
        }
        sprintf(setting, "%s", settings[x]);
        mvwprintw(menuWin, x*3+6, 16, "%s", setting);
    }
    mvwprintw(menuWin, 6, 40, "%d", max_piece_size);
    mvwprintw(menuWin, 9, 40, "%d", min_piece_size);
    mvwprintw(menuWin, 12, 40, "Disabled ");

    x, finished = 0;
    wrefresh(menuWin);

    while(ch = wgetch(menuWin))
    {
        sprintf(setting, "%s", settings[x]);
        mvwprintw(menuWin, x*3+6, 16, "%s", setting);
        switch(ch)
        {
            case(MENU_UP):
                x--;
                if(x < 0 ) { x = numSettings -1; }
                break;

            case(MENU_DOWN):
                x++;
                if( x >= numSettings ) { x = 0; }
                break;

            case(MENU_SELECT):
		//run over the cases for which setting is selected
                                
                if (x == 0)
                {
		//case: selected piece size max
                    sprintf(setting, "%s", settings[x]);
                    mvwprintw(menuWin, x*3+6, 16, "%s", setting);
                    wattron(menuWin, A_STANDOUT);
                    mvwprintw(menuWin, 6, 40, "%d", max_piece_size);
                    wrefresh(menuWin);
                    while(ch = wgetch(menuWin))
                    {
                        int exit = 0;

                        switch(ch)
                        {
                            case(MENU_UP):
                                if(max_piece_size < 30)
                                {
				//allow piece sizes up until 30, program is capable of going
				//above 30 but it can be risky, and some maximum must be set
                                    max_piece_size++;
                                    mvwprintw(menuWin, 6, 40, "%d", max_piece_size);
                                }
                                break;

                            case(MENU_DOWN):
				//only allow max piece size to be greater than or equal to min piece size
                                if(max_piece_size > min_piece_size)
                                {

                                    max_piece_size--;
                                    if(max_piece_size == 9)
                                    {
                                        wattroff(menuWin, A_STANDOUT);
                                        mvwprintw(menuWin, 6, 40, "  ");
                                        wattron(menuWin, A_STANDOUT);
                                    }
                                    mvwprintw(menuWin, 6, 40, "%d", max_piece_size);
                                }
                                break;

                            case(MENU_SELECT):
                                exit = 1;
                                break;

                            case(EXIT):
                                exit = 1;
                                break; 
                        }
                        wrefresh(menuWin);

                        if(exit)
                        {
                            break;
                        }
                    }
                    wattroff(menuWin, A_STANDOUT);
                    mvwprintw(menuWin, 6, 40, "%d ", max_piece_size);
                }

                else if (x == 1)
                {
		//case: selected piece size min
                    sprintf(setting, "%s", settings[x]);
                    mvwprintw(menuWin, x*3+6, 16, "%s", setting);
                    wattron(menuWin, A_STANDOUT);
                    mvwprintw(menuWin, 9, 40, "%d", min_piece_size);
                    wrefresh(menuWin);
                    while(ch = wgetch(menuWin))
                    {
                        int exit = 0;
                        switch(ch)
                        {
                            case(MENU_UP):
                                if(min_piece_size < max_piece_size)
                                {
                                    min_piece_size++;
                                    mvwprintw(menuWin, 9, 40, "%d", min_piece_size);
                                }
                                break;

                            case(MENU_DOWN):
                                if(min_piece_size > 1)
                                {
                                    min_piece_size--;
                                    if(min_piece_size == 9)
                                    {
                                        wattroff(menuWin, A_STANDOUT);
                                        mvwprintw(menuWin, 9, 40, "  ");
                                        wattron(menuWin, A_STANDOUT);
                                    }
                                    mvwprintw(menuWin, 9, 40, "%d", min_piece_size);
                                }
                                break;

                            case(MENU_SELECT):
                                exit = 1;
                                break;

                            case(EXIT):
                                exit = 1;
                                break;
                        }
                        wrefresh(menuWin);

                        if(exit)
                        {
                            break;
                        }
                    }
                    wattroff(menuWin, A_STANDOUT);
                    mvwprintw(menuWin, 9, 40, "%d ", min_piece_size);
                }

                else if (x == 2)
                {
		//case: selected piece design
                    if(checkerboard)
                    {
                        checkerboard = 0;
                        mvwprintw(menuWin, 12, 40, "Disabled ");
                    }
                    else
                    {
                        checkerboard = 1;
                        mvwprintw(menuWin, 12, 40, "Enabled ");
                    }

                }

                else if (x == 3)
                {
                    finished = 1;
                    break;
                }
                break;

            case(EXIT):
                finished = 1;
                break;
        }
                        
        if (finished)
        {
            break;
        }
        wattron(menuWin, A_STANDOUT);
        sprintf(setting, "%s",  settings[x]);
        mvwprintw(menuWin, x*3+6, 16, "%s", setting);
        wattroff(menuWin, A_STANDOUT);
        wrefresh(menuWin);
    }
    
}
