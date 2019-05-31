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
