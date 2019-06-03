#if !defined(DEFINITIONS_H)
#define DEFINITIONS_H 1

#include <ncurses.h>

const char MOVE_LEFT = 97; //a
const char MOVE_RIGHT = 100; //d
const char DROP_BLOCK = 32; //space
const char ROTATE_BLOCK_RIGHT = 119; //w
const char ROTATE_BLOCK_LEFT = 115; //s
const char MENU_UP = 119; //w
const char MENU_DOWN = 115; //s
const char MENU_SELECT = 10; //enter key
const char EXIT = 27; //esc

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

const int menuWin_height = titleWin_height;
const int menuWin_width = hintWin_x + 18;
const int menuWin_x = 2;
const int menuWin_y = 1;

const int linePoints = 10;

typedef struct piece {
	unsigned int** blocks;
	unsigned int* origin;
	unsigned int color;

} PIECE;


typedef struct score {
	unsigned int pts;
	unsigned int lns;
} SCORE;

extern WINDOW *menuWin, *gameWin, *blockWin, *hintWin, *scoreWin, *controlsWin, *titleWin;

//2d array of integers representing color of block at that location
extern unsigned int **block_data;

//where the current movable piece is stored
extern PIECE piece;

extern SCORE sc;

//moves added by the threads to be executed by the main
extern int moveQueue[5];

//===============
//   main.cc
//===============

//===============
//   game.cc
//===============

void game();

//===============
//   threads.cc
//===============

void dropFunc();

void inputFunc();

//================
//   windows.cc
//================

void initColors();

int menu();

void initMenu();

void initControls();

void initGameWindows();

void updateBlockWindow();

//================
//   score.cc
//================

void updateScoreWin();

void updateScore(int points, int lines);


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
