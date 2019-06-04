#include <stdlib.h>
#include "definitions.h"
using namespace std;

void initPieceData()
{
	piece.blocks = (unsigned int**)malloc(sizeof(unsigned int*) * piece_size);
	for(int i = 0; i < piece_size; i++)
	{
		piece.blocks[i] = (unsigned int*)malloc(sizeof(unsigned int) * 2);
	}
	piece.origin = (unsigned int*)malloc(sizeof(unsigned int) * 2);
}

void freePieceData()
{
	free(piece.origin);

	for(int i = 0; i < piece_size; i++)
	{
	free(piece.blocks[i]);
	}
	free(piece.blocks);
}
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

const int pieces[7][3 + 2 * piece_size] =
{
	{1, 4, 4, 3, 4, 4, 4, 5, 4, 6, 4}, //line piece
	{2, 4, 4, 4, 5, 3, 4, 4, 4, 5, 4}, //T piece
	{3, 4, 4, 3, 5, 3, 4, 4, 4, 5, 4}, //L piece
	{4, 4, 4, 5, 5, 3, 4, 4, 4, 5, 4}, //Flipped L piece
	{5, 4, 5, 3, 5, 4, 5, 4, 4, 5, 4}, //S piece
	{6, 4, 5, 4, 5, 5, 5, 3, 4, 4, 4}, //Z piece
	{7, 5, 5, 4, 5, 5, 5, 4, 4, 5, 4}  //O piece
};


//given piece number (int n), assign piece struct values and update
//block data matrix with piece
//return 1 if there is a piece there already (you lose)
int makePiece(int n)
{
	piece.origin[0] = pieces[n][1];
	piece.origin[1] = pieces[n][2];
	piece.color = pieces[n][0];
	for(int i = 0; i < piece_size; i++)
	{
		int y = pieces[n][2*i+4];
		int x = pieces[n][2*i+3];
		if(block_data[y][x]) 
		{
			return 1;
		}
		block_data[y][x] = piece.color;
		piece.blocks[i][0] = x;
		piece.blocks[i][1] = y;
	}
	return 0;
}

//
// Given array of x y coordinates, sets those coordinates
// to zero in block_data, which removes the piece
//
void clearPiece(unsigned int** blocks)
{
  for(int i = 0; i < piece_size; i++)
  {
    block_data[blocks[i][1]][blocks[i][0]] = 0;
  }
}

void movePiece(int n)
{
	if(!n) 
	{
		return;
	}
	
	unsigned int* newloc = (unsigned int*)malloc(sizeof(unsigned int)*2*piece_size);

	clearPiece(piece.blocks);

	int direction = n/abs(n);

	for(int i = piece_size; i--;) 
	{

		int nlx = piece.blocks[i][0] + direction;
		int nly = piece.blocks[i][1];
		newloc[2*i] = nlx;
		newloc[2*i+1] = nly;
		
		if(nlx < 0 || nlx >= blockWin_width || block_data[nly][nlx])
		{
			reconstructPiece(newloc);
			return;
		}
	}
	updateBlocks(newloc,piece.origin[0] + direction, piece.origin[1]);
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
void rotatePiece(int n)
{
	if(!n) //n must have value
	{
		return;
	}
	unsigned int originx = piece.origin[0];
	unsigned int originy = piece.origin[1];

	if(piece.color == 7) //don't rotate squares
	{
		return;
	}

	unsigned int* newloc = (unsigned int*)malloc(sizeof(unsigned int)*2*piece_size);

	clearPiece(piece.blocks);

	for(int i = piece_size; i--;)
	{
		int oldx = piece.blocks[i][0] - originx;
		int oldy = originy - piece.blocks[i][1];

		int newx = (n/abs(n))*oldy;
		int newy = (n/abs(n))*-oldx;

		int nlx = newloc[2*i] = piece.blocks[i][0] + (newx - oldx);
		int nly = newloc[2*i+1] = piece.blocks[i][1] - (newy - oldy);

		//if there's a block there, or if the block is
		//outside of the window, stop the function
		if(nlx < 0 || nly < 0 || nlx >= blockWin_width || nly >= blockWin_height+4 
				|| block_data[nly][nlx])
		{
			reconstructPiece(newloc);
			return;
		}

	}
	updateBlocks(newloc,piece.origin[0],piece.origin[1]);
}

//drops a piece, returns 1 if piece has hit the ground (bottomed)
int dropPiece()
{

	unsigned int* newloc = (unsigned int*)malloc(sizeof(unsigned int)*2*piece_size);
	clearPiece(piece.blocks);
	for(int i = piece_size; i--;)
	{
		unsigned int nly = piece.blocks[i][1]+1;
		unsigned int x = piece.blocks[i][0];
		newloc[2*i] = x;
		newloc[2*i+1] = nly;

		if(nly>=24 || block_data[nly][x])
		{
			reconstructPiece(newloc);
			return 1;
		}

	}
	updateBlocks(newloc,piece.origin[0],piece.origin[1]+1);
	return 0;
}

void updateBlocks(unsigned int* newloc, unsigned int originx, unsigned int originy)
{
	//update the block data and piece data
	for(int i = piece_size; i--;)
	{
		block_data[newloc[2*i+1]][newloc[2*i]] = piece.color;

		//update blocks in piece, origin should stay the same
		piece.blocks[i][0] = newloc[2*i];
		piece.blocks[i][1] = newloc[2*i+1];

	}
	piece.origin[0] = originx;
	piece.origin[1] = originy;
	free(newloc);
}

//if the block can't move, reconstruct it where it was
void reconstructPiece(unsigned int* newloc)
{

	for(int i = piece_size; i--;)
	{
		block_data[piece.blocks[i][1]][piece.blocks[i][0]] = piece.color;
	}
	
	free(newloc);

}
