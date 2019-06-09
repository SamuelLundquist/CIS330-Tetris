#include <stdlib.h>
#include "definitions.h"


//
// Given array of x y coordinates, sets those coordinates
// to zero in block_data, which removes the piece
//
void clearPiece(int** blocks)
{
  for(int i = 0; i < piece_size; i++)
  {
    block_data[blocks[i][1]][blocks[i][0]] = 0;
  }
}


//move piece left or right 1 (dependent on sign of lr = left right)
void movePiece(int lr)
{
	if(!lr) 
	{
		return;
	}
	
	int* newloc = (int*)malloc(sizeof(int)*2*piece_size);

	clearPiece(piece.blocks);

	int direction = lr/abs(lr);

	for(int i = piece_size; i--;) 
	{

		int nlx = piece.blocks[i][0] + direction;
		int nly = piece.blocks[i][1];
		newloc[2*i] = nlx;
		newloc[2*i+1] = nly;
		
		//if piece is out of range, reconstruct it where it was
		if(nlx < 0 || nlx >= blockWin_width || block_data[nly][nlx])
		{
			reconstructPiece(newloc);
			return;
		}
	}
	updateBlocks(newloc,piece.origin[0] + direction, piece.origin[1]);
}

int checkCandidate(int x, int shift, int* loc);

/*
rotate piece if space available
positive input = clockwise, negative = counterclockwise

create a "sub-graph" with respect to the origin of piece
the x coordinate of each block = x - originx
since y is inverted (starts at 0 from the top)
y = originy - y
clockwise rotation is: x = y, y = -x
therefore, plug in above values of x into this equation
then, check if space is open
if so, update block data and piece data
*/
void rotatePiece(int lr)
{
	if(!lr) //left/right must have value
	{
		return;
	}
	int originx = piece.origin[0];
	int originy = piece.origin[1];

	//possible candidates for shift after rotation
	int numCand = 6;
	//{shift on y or x axis, shift positive or negative}
	int candidates[numCand][2] = {{1,0},{1,1},{1,-1},{0,1},{1,2},{1,-2}};
	
	if(piece.color == 7 && piece_size ==4) //don't rotate squares
	{
		return;
	}
	
	int* newloc = (int*)malloc(sizeof(int)*2*piece_size);

	clearPiece(piece.blocks);

	for(int i = piece_size; i--;)
	{
		int oldx = piece.blocks[i][0] - originx;
		int oldy = originy - piece.blocks[i][1];

		int newx = (lr/abs(lr))*oldy;
		int newy = (lr/abs(lr))*-oldx;

		newloc[2*i] = piece.blocks[i][0] + (newx - oldx);
		newloc[2*i+1] = piece.blocks[i][1] - (newy - oldy);

							
	}
	for(int i = 0; i < numCand; i++) 
	{
		if(checkCandidate(candidates[i][0],candidates[i][1],newloc))
		{
			free(newloc);
			return;
		}
	}
	reconstructPiece(newloc);
	return;

}

/*
checks a candidate for rotation
in order to avoid being unable to rotate because the piece is next to a wall
rotate and then shift n units to the left/right

if x parameter is 1, check the candidate corresponding to a x shift 
if x is 0, perform a y shift (not inverted despite ncurses being inverted with
respect to y coordinates - if shift = 1, piece will go UP 1)

return 1 if the candidate is valid
*/
int checkCandidate(int x, int shift, int* loc)
{
	int* newloc = (int*)malloc(sizeof(int)*2*piece_size);
	for(int i = piece_size; i--;)
	{
		int nlx = newloc[2*i] = loc[2*i] + shift*x;
		int nly = newloc[2*i+1] = loc[2*i+1] + shift*(x-1);
		//if there's a block there, or if the block is
		//outside of the window, this candidate is not valid
		if(nlx < 0 || nly < 0 || nlx >= blockWin_width || nly >= blockWin_height+4 
				|| block_data[nly][nlx])
		{
			free(newloc);
			return 0;
		}
	}
	//if all the blocks are valid, return the candidate
	updateBlocks(newloc, piece.origin[0]+shift*x, piece.origin[1]+shift*(x-1));
	return 1;

}


//drops a piece, returns 1 if piece has hit the ground (bottomed)
int dropPiece()
{

	int* newloc = (int*)malloc(sizeof(int)*2*piece_size);
	clearPiece(piece.blocks);
	for(int i = piece_size; i--;)
	{
		int nly = piece.blocks[i][1]+1;
		int x = piece.blocks[i][0];
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

void updateBlocks(int* newloc, int originx, int originy)
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
void reconstructPiece(int* newloc)
{

	for(int i = piece_size; i--;)
	{
		block_data[piece.blocks[i][1]][piece.blocks[i][0]] = piece.color;
	}
	
	free(newloc);

}


int storedPiece = -1;

void storePiece() 
{

	//if there isn't already a stored piece, 
	if(storedPiece == -1) 
	{
		storedPiece = currentPiece;
		clearPiece(piece.blocks);
		makePiece(nextPiece);
		nextPiece = genPiece();
		return;
	}
	int newPiece = storedPiece;
	storedPiece = currentPiece;
	clearPiece(piece.blocks);
	//since piece array starts at 1, newPiece - 1
	makePiece(newPiece);
	return;
}




