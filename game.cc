/*
Tetris Using C++ and ncurses

Authors:
Matthew Struble
Samuel Lundquist
Qi Han
*/
#include <ncurses.h>
#include <iostream>
#include "definitions.h"

using namespace std;

//Where the information for occupancy of cells will be stored
//max index: block_data[blockHeight - 1][blockWidth-1]

char **block_data;

//Where the current movable piece is stored

PIECE piece;

//Define all windows
WINDOW *gameWin, *blockWin, *hintWin, *scoreWin, *controlsWin, *titleWin;

/*
Defines different types of blocks we might have
For starters, we have 7 shapes with 4 blocks apiece
note that display of y starts at 4

need to indicate: 
piece color 
piece origin upon initialization
x,y of each block upon initialization

Each piece {color, originx, originy, x1, y1, x2, y2, x3, y3, x4, y4}
*/

const int pieces[7][3 + 2 * piece_size] 
{
	{1, 4, 4, 3, 4, 4, 4, 5, 4, 6, 4}, //line piece
	{2, 4, 4, 4, 5, 3, 4, 4, 4, 5, 4}, //T piece
	{3, 4, 4, 3, 5, 3, 4, 4, 4, 5, 4}, //L piece
	{4, 4, 4, 5, 5, 3, 4, 4, 4, 5, 4}, //Flipped L piece
	{5, 4, 5, 3, 5, 4, 5, 4, 4, 5, 4}, //S piece
	{6, 4, 5, 4, 5, 5, 5, 3, 4, 4, 4}, //Z piece
	{7, 5, 5, 4, 5, 5, 5, 4, 4, 5, 4}  //O piece
};

void initBlockData()
{
    block_data = (char**)malloc(sizeof(char*) * blockWin_width*blockWin_height/4);	
	for(int i = 0; i < blockWin_height/2 + 4; i++) //want to be able to store blocks 													//that go above the screen
    {
        block_data[i] = (char*)malloc(sizeof(char) * blockWin_width/2);
        for(int j = 0; j < blockWin_width/2; j++)
        {
            block_data[i][j] = 0;
        }
    }
}

void freeBlockData()
{
	for(int i = 0; i < blockWin_height; i++)
    {
        free(block_data[i]);
    }
    free(block_data);
}

void initPieceData() 
{
	piece.blocks = (char**)malloc(sizeof(char*) * piece_size);
	for(int i = 0; i < piece_size; i++) 
	{
		piece.blocks[i] = (char*)malloc(sizeof(char) * 2);
	}
	piece.origin = (char*)malloc(sizeof(char) * 2);
}

void freePieceData()
{
	free(piece.origin);
	free(piece.blocks);
}

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

//Given a new score value, updates to score window
void updateScore(SCORE score)
{
    mvwprintw(scoreWin, 2, 9, "%d", score.pts);
    mvwprintw(scoreWin, 4, 9, "%d", score.lns);
    wrefresh(scoreWin);
}

void updateBlockWindow()
{
    for (int y = 4; y < blockWin_height/2 + 4; y++)
    {
        for (int x = 0; x < blockWin_width/2; x++)
        {
            wattrset(blockWin, COLOR_PAIR(block_data[y][x]));
            mvwprintw(blockWin, 2 * y - 8, x * 4, "    ");
			mvwprintw(blockWin, 2 * y - 7, x * 4, "    ");
        }
    }
    wrefresh(blockWin);
}

void initWindows()
{
    gameWin = newwin(gameWin_height, gameWin_width, gameWin_y, gameWin_x);
    blockWin = newwin(blockWin_height, blockWin_width * 2, blockWin_y, blockWin_x);
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

//given piece number (int n), assign piece struct values and update
//block data matrix with piece 
void makePiece(int n) 
{
	piece.origin[0] = pieces[n][1];
	piece.origin[1] = pieces[n][2];
	for(int i = 0; i < piece_size; i++) 
	{
		int y = pieces[n][2*i+4];
		int x = pieces[n][2*i+3];
		block_data[y][x] = pieces[n][0];
		piece.blocks[i][0] = x;				
		piece.blocks[i][1] = y;
	}
}

//remove horizontal line y
void rmLine(int y) 
{
	for(int x = 0; x < blockWin_width/2; x++) 
	{
		block_data[y][x] = 0;
	}
}

//rotate piece if space available
//positive input = clockwise, negative = counterclockwise
//
//create a "sub-graph" with respect to the origin of piece
//the x coordinate of each block = x - originx
//since y is inverted (starts at 0 from the top)
//y = originy - y
//clockwise rotation is: x = y, y = -x
//therefore, plug in above values of x to this equation
//then, check if space is open
//if so, update block data and piece data
void rotate(int n) 
{
	if(!n) //n must have value
	{
		return;
	}
	unsigned int originx = piece.origin[0];
	unsigned int originy = piece.origin[1];

	unsigned int color = block_data[originy][originx];

	if(color == 7) //don't rotate squares
	{
		return;
	}

	int* newloc = (int*)malloc(sizeof(int)*2*piece_size);


	//clear the original blocks from block data
	for(int i = piece_size; i--;) 
	{
		block_data[piece.blocks[i][1]][piece.blocks[i][0]] = 0;
	}


	for(int i = piece_size; i--;) 
	{
		int oldx = piece.blocks[i][0] - originx;
		int oldy = originy - piece.blocks[i][1];
	
		int newx = (n/abs(n))*oldy;
		int newy = (n/abs(n))*-oldx;
		
		int nlx = newloc[2*i] = piece.blocks[i][0] + (newx - oldx);
		int nly = newloc[2*i+1] = piece.blocks[i][1] - (newy - oldy);
		printf("co(%d,%d)o(%d,%d)n(%d,%d),cn(%d,%d)",
				piece.blocks[i][0] ,piece.blocks[i][1], oldx, oldy,
		     		newx, newy, nlx, nly);
		printf("%d",blockWin_width);
		fflush(stdout);
		//if there's a block there, or if the block is
		//outside of the window, stop the function
		if(block_data[nly][nly] || nlx < 0 || nly < 0 
						|| nlx >= blockWin_width/2 || nly >= blockWin_height/2) 
			
		{
			//reconstruct the piece
			for(int i = piece_size; i--;) 
			{
				block_data[piece.blocks[i][1]][piece.blocks[i][0]] = color;
			}
			free(newloc);
			return;
		}
	}


	
	//update the block data and piece data
	for(int i = piece_size; i--;) 
	{
		block_data[newloc[2*i+1]][newloc[2*i]] = color;
		
		//update blocks in piece, origin should stay the same
		piece.blocks[i][0] = newloc[2*i];
		piece.blocks[i][1] = newloc[2*i+1];
			
	}	

	free(newloc);
}


int main()
{
   initscr();

   cbreak(); //ctrl + c will stop function

   noecho(); //function does not print input characters

   curs_set(0); //make blinking cursor invisible

   initColors();

   initWindows();

   initBlockData();

   initPieceData();

   getch();

   //Test for updating score data
   SCORE sc = {1000, 10};
   updateScore(sc);

   //Tests for updating block data
   /*
   block_data[4][0] = 3;
   block_data[4][1] = 4;
   block_data[5][1] = 3;
   block_data[4][19] = 3;
   block_data[5][4] = 2;
   block_data[10][6] = 2;
   block_data[23][9] = 3; 
   updateBlockWindow();
   */

   getch();
   
   for (int i = 0; i < 7; i++) 
   {
      makePiece(i);
	  updateBlockWindow();
	  getch();
	  rotate(1);
	  updateBlockWindow();
	  getch();
	  rotate(1);
	  updateBlockWindow();
	  getch();
	  rotate(1);
	  updateBlockWindow();
	  getch();
	  rotate(1);
	  updateBlockWindow();
	  getch();
	  rotate(-1);
	  updateBlockWindow();
	  getch();
	  rmLine(2);
	  rmLine(3);
	  rmLine(4);
	  rmLine(5);
	  rmLine(6);
	  rmLine(7);
   }

   freePieceData();

   freeBlockData();
   
   endwin();
   return 0;
}

