#if !defined(DEFINITIONS_H)
#define DEFINITIONS_H 1

#include <ncurses.h>



//===============
//   execution
//     codes
//===============

const char AUTO_DROP = 1;

const char MOVE_LEFT = 97; //a
const char MOVE_RIGHT = 100; //d
const char DROP_BLOCK = 32; //space
const char ROTATE_BLOCK_CLOCKWISE = 115; //s
const char ROTATE_BLOCK_COUNTERCLOCKWISE = 119; //w
const char STORE_PIECE = 102; //f
const char MENU_UP = 119; //w
const char MENU_DOWN = 115; //s
const char MENU_SELECT = 10; //enter key
const char EXIT = 27; //esc



//===============
//   objects
//===============

typedef struct piece {
	int** blocks;
	int* origin;
	unsigned int color;

} PIECE;


typedef struct score {
	unsigned int pts;
	int lns;
	int level;
} SCORE;

extern WINDOW *menuWin, *gameWin, *blockWin, *hintWin, *scoreWin, *controlsWin, *titleWin, *lastWin;

//2d array of integers representing color of block at that location
extern unsigned int **block_data;

//where the current movable piece is stored
extern PIECE piece;

extern SCORE sc;

//===============
//   options
//===============

extern unsigned int min_piece_size;

extern unsigned int max_piece_size;

extern unsigned int numPieces;

extern int** pieces;

//===============
//   status
//===============

extern unsigned int linePoints;

extern unsigned int piece_size;

extern unsigned int alive;

extern int dropSpeed;

extern int storeAvailable;

extern int currentPiece;

extern int storedPiece;

extern int nextPiece;

//Set block speed based on level and number of levels
const int levels = 10;

const int levelSpeed[levels] = {1000, 850, 750, 650, 500, 400, 300, 200, 150, 100};


//=======================
//         FILES
//=======================

//===============
//   game.cc
//===============

void game();

//===============
//   threads.cc
//===============

class Queue
{
	private:
		int moves[5];
		int size;
		int loc;
	public:
		Queue();
		void Enqueue(int move);
		int Dequeue();
		int HasMove();

};

//moves added to queue by threads to be executed in game()
extern Queue moveQueue;

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

void killAllWindows();

//================
//   score.cc
//================

void updateScoreWin();

void updateScore(int points, int lines);

void updateLevel();

void initLevelAndScore(int level);


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

void initPieces(int min, int max);

void freePieces();

int makePiece(int n);

int genPiece();

void clearPiece(unsigned int** blocks);

void movePiece(int n);

void rotatePiece(int n);

int dropPiece();

void updateBlocks(int* newloc, int originx, int originy);

void reconstructPiece(int* newloc);

void storePiece();


//===============
//   menus
//===============

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



#endif
