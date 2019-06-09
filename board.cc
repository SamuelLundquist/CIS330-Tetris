#include <stdlib.h>
#include <stdio.h>
#include "definitions.h"

void initBlockData()
{
  block_data = new unsigned int*[blockWin_width * blockWin_height];
  for(int i = 0; i < blockWin_height + 4; i++) //want to be able to store blocks that go above the screen
  {
        block_data[i] = new unsigned int[blockWin_width];
        for(int j = 0; j < blockWin_width; j++)
        {
            block_data[i][j] = 0;
        }
    }
}

void freeBlockData()
{
    for(int i = 0; i < blockWin_height; i++)
    {
        delete block_data[i];
    }
    delete block_data;
}

//remove horizontal line y
void rmLine(int y)
{
	for(int x = 0; x < blockWin_width; x++)
	{
		block_data[y][x] = 0;
	}
}

//Mallocs array for the fullLines function, keeps track of full lines of piece once done dropping
int* mallocFullLines()
{
  int len = piece_size + 1;
  int* fullLines = new int[len];
  for(int i = 0; i < len; i++)
  {
    fullLines[i] = -1;
  }
  return fullLines;
}

//Check lines returns an array of all lines that are full in current piece
//specifically, the lines of the block that was just placed
//array has -1 values if there is not a full line
int* fullLines()
{
  int* fullLines = mallocFullLines();
  for (int i = 0; i < piece_size; i++)
  {
    int full = 1;
    int y = piece.blocks[i][1];
    for(int x = 0; x < blockWin_width; x++)
  	{
  		if (block_data[y][x] == 0)
      {
        full = 0;
      }
  	}
    if (full)
    {
      fullLines[i] = y;
      rmLine(y);
    }
  }
  insertionSort(fullLines, piece_size);
  int linesDestr = 0, i = 0, points;
  while(fullLines[i] != -1)
  {
      linesDestr++;
      i++;
  }
  //points per line times bonus multiplier times number of lines destroyed
  points = linePoints * linesDestr * linesDestr;
  updateScore(points, linesDestr);
  return fullLines;
}

//A function that drops a specific block down a specific
//amount of lines. This is used in checkLines
void drop(int row, int dropNum)
{
  for (int x = 0; x < blockWin_width; x++)
  {
    block_data[row+dropNum][x] = block_data[row][x];
    block_data[row][x] = 0;
  }
}

//This function checks for possible full lines from a recently placed
//block, if full lines are found, it removes them and then drops
//the rest of the blocks in the block window down
void checkLines()
{
	int* removedLines = fullLines();
	int remRow = removedLines[0];

	//if there was no row removed, return
	if(remRow == -1) 
	{
		return;
	}

	int dropNum = 0;
	int i = 0;
	int toRow;

	//while there are lines to drop
	while(remRow)
	{
		int toRow = removedLines[i+1];

		//case where duplicates in array, skip to next value
		if(remRow == -2) 
		{
			i++;
			remRow = toRow;
			continue;
		}
		
		dropNum++;
		int row = remRow - 1;
		
		//if there is no next line, drop the rest of the board	
		if(toRow == -1) {      
			toRow = 0;
		}
		
		//until you reach the next row, drop all rows by dropNum
		while (row != toRow)
		{
			drop(row, dropNum);
			row--;
		}
		remRow = toRow;
		i++;
	}
	delete removedLines;
}

//Sorts array from greatest to least given array and array length
void insertionSort(int* arr, int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] < key)
        {
			//"remove" duplicates
			if(key == arr[j]) 
			{
				key = -2;
			}
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
