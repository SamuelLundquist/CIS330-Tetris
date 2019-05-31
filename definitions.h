#define MOVE_LEFT = 68 //key left
#define MOVE_RIGHT = 67 //key right
#define DROP_BLOCK = 66 //key down
#define ROTATE_BLOCK = 65 //key up


#if !defined(DEFINITIONS_H)
#define DEFINITIONS_H 1

#include <ncurses.h>

const int piece_size = 4;

const int blockWin_height = 20;
const int blockWin_width = 10;
const int blockWin_x = 3;
const int blockWin_y = 2;

const int gameWin_height = blockWin_height*2+2;
const int gameWin_width = blockWin_width*4+2;
const int gameWin_x = 2;
const int gameWin_y = 1;

const int hintWin_height = 10;
const int hintWin_width = 20;
const int hintWin_x = gameWin_width+4;
const int hintWin_y = 1;

const int scoreWin_height = 10;
const int scoreWin_width = 20;
const int scoreWin_x = hintWin_x;
const int scoreWin_y = 11;

const int controlsWin_height = 15;
const int controlsWin_width = 20;
const int controlsWin_x = hintWin_x;
const int controlsWin_y = 21;

const int titleWin_height = 35;
const int titleWin_width = 16;
const int titleWin_x = hintWin_x+22;
const int titleWin_y = 1;

typedef struct piece {
	unsigned int** blocks;
	unsigned int* origin;
	unsigned int color;

} PIECE;


typedef struct score {
	unsigned int pts;
	unsigned int lns;
} SCORE;

extern WINDOW *gameWin, *blockWin, *hintWin, *scoreWin, *controlsWin, *titleWin;

//2d array of integers representing color of block at that location
extern unsigned int **block_data;

//where the current movable piece is stored
extern PIECE piece;

//moves added by the threads to be executed by the main
extern int moveQueue[5];

//===============
//   threads.cc
//===============

void dropFunc();

void inputFunc();

//================
//   windows.cc
//================

void initColors();

void initWindows();

void updateBlockWindow();

//================
//   score.cc
//================

void updateScore(SCORE score);


//================
//   board.cc
//================

void initBlockData();

void freeBlockData();

void rmLine(int y);

int* mallocFullLines();

int* fullLines();

void drop(int row, int dropNum);

void insertionSort(int arr[], int n);

void checkLines();


//================
//   pieces.cc
//================

void initPieceData();

void freePieceData();

void makePiece(int n);

void clearPiece(unsigned int** blocks);

void rotate(int n);

int dropPiece();

void updateBlocks(unsigned int* newloc);

void reconstructPiece(unsigned int* newloc);

#endif
