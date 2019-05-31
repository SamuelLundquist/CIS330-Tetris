#include <stdlib.h>
#include "definitions.h"

void initBlockData()
{
  block_data = (unsigned int**)malloc(sizeof(unsigned int*) * blockWin_width * blockWin_height);
	for(int i = 0; i < blockWin_height + 4; i++) //want to be able to store blocks that go above the screen
    {
        block_data[i] = (unsigned int*)malloc(sizeof(unsigned int) * blockWin_width);
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
        free(block_data[i]);
    }
    free(block_data);
}

//remove horizontal line y
void rmLine(int y)
{
	for(int x = 0; x < blockWin_width; x++)
	{
		block_data[y][x] = 0;
	}
}

int* checkLines()
{
  int* fullLines = (int*)malloc(sizeof(int) * piece_size);
  for (int i = 0; i < piece_size; i++)
  {
    int full = 1;
    int y = piece.blocks[i][1];
    for(int x = 0; x < blockWin_width; x++)
  	{
  		if (block_data[y] == 0)
      {
        full = 0;
      }
  	}
    if (full)
    {
      insertionSort(fullLines, y);
      rmLine(y);
    }
  }
  return fullLines;
}

void drop(int row, int dropNum)
{
  for (int x = 0; x < blockWin_width; x++)
  {
    block_data[row+dropNum][x] = block_data[row][x];
    block_data[row][x] = 0;
  }
}

/*
void dropBlockData(int* removedLines)
{
  int dropNum = 1;
  int i = 0;
  int row = removedLines[i] + 1;
  while(removedLines[i] && i < piece_size)
  {

    while (row != removedLines[i])
    {
      drop(row, dropNum);
      row++;
    }
    dropNum++;
    i++;
  }
}
*/

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
