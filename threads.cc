#include <chrono>
#include <thread>
#include "definitions.h"

using namespace std;

	

//adds DROP to the moveQueue every period of time 
//dictated by the current falling speed
void dropFunc()
{
	while(alive) 
	{	
		this_thread::sleep_for(chrono::milliseconds(1000));
		moveQueue.Enqueue(AUTO_DROP);

	}	
}

//adds corresponding input to the moveQueue based on user inputted
//characters to be executed by the main
void inputFunc() 
{
	char ch;
	keypad(gameWin, TRUE);
	while(ch = wgetch(gameWin))
	{
		moveQueue.Enqueue(ch);	

	}
}

Queue::Queue() 
{
	size = 5;
	loc = 0;
}

void Queue::Enqueue(int move) 
{
	int next = loc+1;
	if(loc == size - 1) 
	{
		next = 0;
	}
	if(!moves[next]) 
	{
		loc = next;
		moves[loc] = move;
	} 
	//add autodrop to the queue no matter what
	else if(move == AUTO_DROP)
	{
		moves[loc] = move;
	}
	return;
	
}

int Queue::Dequeue()
{
	int val = moves[loc];
	moves[loc] = 0;
	if(loc == 0) 
	{
		loc = 4;
	}
	else
	{
		loc--;
	}
	return val;
}

int Queue::HasMove()
{
	return(moves[loc]);
}
