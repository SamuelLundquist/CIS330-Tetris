#include <stdlib.h> //random
#include <cstring> //memcpy
#include "definitions.h"

using namespace std;


void initPieceData()
{
	piece.blocks = new int*[max_piece_size];
	for(int i = 0; i < max_piece_size; i++)
	{
		piece.blocks[i] = new int[2];
	}
	piece.origin = new int[2];

}

void freePieceData()
{
	delete piece.origin;

	for(int i = 0; i < piece_size; i++)
	{
		delete piece.blocks[i];
	}
	delete piece.blocks;
}

int** pieces;
void genPieces(int min, int max);
int* shapePiece(int n, int max, int* genarr);
void addPiece(int piecenum, int max, int* piecedata);
void addPieceToArr(int piecenum, int max, int* piecedata, int*** arrptr);

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

//if using random piece generation, the algorithm is set to
//cap at 7 pieces per size
//the number of pieces of sizes up to the classic tetromino are:
//size 1: 1, size 2: 1, size 3: 2, size 4: 7
void initPieces(int min, int max)
{

	//first calculate the number of pieces
	int i = min;
	numPieces = 0;
	while(i < 4 && i < max+1) 
	{	
		if(i == 1 || i == 2)
		{
			numPieces++;	
		}
		else if(i==3)
		{
			numPieces += 2;
		}
		i++;
	}
	//for the rest of the sizes, have 7 pieces
	numPieces += (max - i + 1)*7;
	pieces = new int*[numPieces];
	for(int i = 0; i < numPieces; i++) 
	{
		pieces[i] = new int[3+2*max];
		for(int j = 0; j < 3+2*max; j++) 
		{
			pieces[i][j] = -1;
		}
	}
	genPieces(min, max);	
}

/*
generate all possible tetrominos of size min to size max
formatted as said above initPieces
if piece is smaller than max_piece_size, all excess entries are filled with -1
pieces of size 5 or greater are generated by randomly adding a block to 
each piece of size n-1
*/
void genPieces(int min, int max)
{
	int csize = 1;
	int i = 0;

	//color + originx&y + 2*max size + 1(space for -1 entry)
	int len = 3+2*max+1;

	//search until reach min, or until need to start generating pieces (size = 5)
	while(csize < min && csize < 4) 
	{
		csize++;
	}
	if(csize == 1)
	{
		//start at (4,4) : x=4 = center rounded left, y=4 = top of visible blocks
		//origin = (4,4). this is the first two entries after color
		int data[len] = {7,4,4,4,4,-1};
		addPiece(i, max, data);
		i++;
		csize++;
	}
	if(csize == 2 && csize <= max)
	{
		//c++ doesn't accept curly braced arrays as parameters to
		//functions, so must make a temporary container for the data
		int data[len] = {6,4,4,4,4,5,4,-1};
		addPiece(i, max, data);
		i++;
		csize++;
	}	
	if(csize == 3 && csize <= max)
	{
		//2 possible pieces this time: corner piece and length 3 line piece
		
		int dataa[len] = {5,4,4,3,4,4,4,5,4,-1};
		addPiece(i, max, dataa);
		i++;
		int datab[len] = {4,4,4,3,4,4,4,4,5,-1};
		addPiece(i, max, datab);
		i++;
		csize++;
	}
	//excess -1 character on pieces of max size is removed
	int tlen = len-1;
	//a generator array used to shape pieces of larger sizes
	int** genarr = new int*[7];
	for(int t = 0; t < 7; t++)
	{
		genarr[t] = new int[tlen];
	}

	if(csize == 4 && csize <= max && 4 >= min)
	{
		//regular tetris pieces
		int dataa[len] = {1, 4, 4, 3, 4, 4, 4, 5, 4, 6, 4, -1};
		addPiece(i, max, dataa); //line piece
		memcpy(genarr[0],pieces[i],sizeof(int)*(tlen));
		i++;
		int datab[len] = {2, 4, 4, 4, 5, 3, 4, 4, 4, 5, 4, -1};
		addPiece(i, max, datab); //T piece
		memcpy(genarr[1],pieces[i],sizeof(int)*(tlen));
		i++;
		int datac[len] = {3, 4, 4, 3, 5, 3, 4, 4, 4, 5, 4, -1};
		addPiece(i, max, datac); //L piece
		memcpy(genarr[2],pieces[i],sizeof(int)*(tlen));
		i++;
		int datad[len] = {4, 4, 4, 5, 5, 3, 4, 4, 4, 5, 4, -1};
		addPiece(i, max, datad); //Flipped L piece
		memcpy(genarr[3],pieces[i],sizeof(int)*(tlen));
		i++;
		int datae[len] = {5, 4, 5, 3, 5, 4, 5, 4, 4, 5, 4, -1};
		addPiece(i, max, datae); //S piece
		memcpy(genarr[4],pieces[i],sizeof(int)*(tlen));
		i++;
		int dataf[len] = {6, 4, 5, 4, 5, 5, 5, 3, 4, 4, 4, -1};
		addPiece(i, max, dataf); //Z piece
		memcpy(genarr[5],pieces[i],sizeof(int)*(tlen));
		i++;
		int datag[len] = {7, 5, 5, 4, 5, 5, 5, 4, 4, 5, 4, -1};
		addPiece(i, max, datag); //O piece
		memcpy(genarr[6],pieces[i],sizeof(int)*(tlen));
		i++;
		csize++;
	}
	//if our minimum size is less than 4, add to genArr but don't add
	//piece to pieces
	else if(min > 4){
		int j = 0;
		int dataa[len] = {1, 4, 4, 3, 4, 4, 4, 5, 4, 6, 4, -1};
		addPieceToArr(j, max, dataa, &genarr); //line piece
		j++;
		int datab[len] = {2, 4, 4, 4, 5, 3, 4, 4, 4, 5, 4, -1};
		addPieceToArr(j, max, datab, &genarr); //T piece
		j++;
		int datac[len] = {3, 4, 4, 3, 5, 3, 4, 4, 4, 5, 4, -1};
		addPieceToArr(j, max, datac, &genarr); //L piece
		j++;
		int datad[len] = {4, 4, 4, 5, 5, 3, 4, 4, 4, 5, 4, -1};
		addPieceToArr(j, max, datad, &genarr); //Flipped L piece
		j++;
		int datae[len] = {5, 4, 5, 3, 5, 4, 5, 4, 4, 5, 4, -1};
		addPieceToArr(j, max, datae, &genarr); //S piece
		j++;
		int dataf[len] = {6, 4, 5, 4, 5, 5, 5, 3, 4, 4, 4, -1};
		addPieceToArr(j, max, dataf, &genarr); //Z piece
		j++;
		int datag[len] = {7, 5, 5, 4, 5, 5, 5, 4, 4, 5, 4, -1};
		addPieceToArr(j, max, datag, &genarr); //O piece
		j++;
		csize++;}


	//for remaining sizes, make 7 pieces of each size
	while(csize <= max)
	{
		for(int j = 0; j < 7; j++)
		{
			//make a new piece out of the jth entry of the genarr
			int* tpiece = shapePiece(csize-1, max, genarr[j]);
			if(csize >= min)
			{
				addPiece(i, max, tpiece);
				memcpy(genarr[j],pieces[i],sizeof(int)*(tlen));
				i++;

			}
			else
			{
				//if size is not in range, only add the 
				//shape to the generation array
				addPieceToArr(j, max, tpiece, &genarr);
			}			
			delete tpiece;

		}

		csize++;
	}

	for(int t = 0; t < 7; t++)
	{
		delete genarr[t];
	}
	delete genarr;
	
		 
}

//from a piece of size n, create a new piece of size n+1 by adding a block
//to some random empty space next to a block in the original piece
//returns an array to be inputted into addPiece
int *shapePiece(int n, int max, int* genarr)
{

	int** graph = new int*[n+1];
	for(int i = 0; i < n+1; i++)
	{
		graph[i] = new int[10];
		for(int j = 0; j < 10; j++)
		{
			graph[i][j] = 0;
		}
	}	
	int i = 1;
	int entry;	

	while((entry = genarr[2*i+1]) != -1)
	{

		//graph[y-4][x] = color
		graph[genarr[2*i+2]-4][entry] = genarr[0];
		i++;
		
	}

	int found = 0;
	int newx;
	int newy;
	int block;
	while(!found) 
	{	
		//choose block in original piece
		block = rand()%n;
		int blockx = genarr[3+2*block];
		int blocky = genarr[3+2*block+1]-4;

		//possible ways to move from block
		//(don't count up - don't want to go above the window)
		//0: down, 1: right, -1: left
		int* shifts = new int[3];
		shifts[0] = 0;
	        shifts[1] = 1;
		shifts[2] = -1;
		//randomize order of shifts tested
		for(int j = 0; j < 2; j++)
		{
			//psuedo-random number between j and 3:
			//1. find random from 0-2 (rand%3)
			//2. random number from 0-(2-j) = %(3-j)
			//3. random number from 1-2 = + j
			int k = (rand()%3)%(3-j)+j;
			//exchange entries k and j
			int t = shifts[k];
			shifts[k] = shifts[j];
			shifts[j] = t;
		}
		int dir;
		for(int j = 0; j < 3; j++)
		{		
			if(dir = shifts[j])
			{
				//attempt a random shift on the block
				newx = blockx + dir;
				if(!(newx < 0 || newx >9)
					&& !graph[blocky][newx])
				{
					//if the position is valid, the
					//new piece has been created
					found = 1;
					newy = blocky+4;
					break;
				
				}	
			}	
			else
			{
				newy = blocky+1;
				if(!graph[newy][blockx])
				{
					found = 1;
					newx = blockx;
					newy = newy+4;
					break;
				}
			}
		}
		delete shifts;
	}
	int* newPiece= new int[3+2*max + 1];
	int j;

	for(j = 0; j < 3+2*n; j++)
	{
		newPiece[j] = genarr[j];
	}

	newPiece[j] = newx;
	newPiece[j+1] = newy;
	newPiece[j+2] = -1;
	
	for(int t = 0; t < n+1; t++)
	{
		delete graph[t];
	}
	delete graph;

	return newPiece;
}

//add a new piece to the list of possible pieces in current game
void addPiece(int piecenum, int max, int* piecedata)
{
	int i = 0;
	int entry;
	while((entry = piecedata[i]) != -1) 
	{		
		pieces[piecenum][i] = entry;
		i++;

	}
	while(i < 3 + 2*max)
	{
		
		pieces[piecenum][i] = -1;
		i++;
	}

}

//add a new piece to the list of pieces used to generate new random pieces
void addPieceToArr(int piecenum, int max, int* piecedata, int*** arrptr)
{
	int i = 0;
	int entry;
	while((entry = piecedata[i]) != -1) 
	{		
		arrptr[0][piecenum][i] = entry;
		i++;

	}
	while(i < 3 + 2*max)
	{	
		arrptr[0][piecenum][i] = -1;
		i++;
	}
}

void freePieces()
{
	for(int i = 0; i < numPieces; i++) 
	{
		delete pieces[i];
	}
	delete pieces;

}

int currentPiece;

//given piece number (int n), assign piece struct values and update
//block data matrix with piece
//return 1 if there is a piece there already (you lose)
int makePiece(int n)
{
	//determine piece size
	int i = 3;
	while((i-2 < max_piece_size) && pieces[n][2*i-1] != -1)
	{
		i++;
	}
	piece_size = i - 2;
	int game_over = 0;
	piece.origin[0] = pieces[n][1];
	piece.origin[1] = pieces[n][2];
	piece.color = pieces[n][0];
	for(int i = 0; i < piece_size; i++)
	{
		int y = pieces[n][2*i+4];
		int x = pieces[n][2*i+3];
		if(block_data[y][x]) 
		{
			game_over = 1;
		}
		block_data[y][x] = piece.color;
		piece.blocks[i][0] = x;
		piece.blocks[i][1] = y;
	}
	currentPiece = n;
	return game_over;
}

//randomly generate a piece from the possible list of pieces
int randPiece() 
{
	return(rand()%numPieces);
}


