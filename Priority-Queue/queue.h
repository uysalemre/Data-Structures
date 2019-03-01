#ifndef QUEUE_H
#define QUEUE_H
#include "queueNodes.h"

struct Queue
{
	Node_Patient *front,*back;				//front and back pointers of the queues
	Node_RED *r_front,*r_back;
	Node_YELLOW *y_front,*y_back;
	Node_GREEN *g_front, *g_back;
	string line;							//input file first line keeper
	int trttime = 0;						//for saving the treatment time
	void create();						
	void readFileIntoQ(string filename);	//reading file into main queue
	void enqueue(Node_Patient *node);		//enqueue the patients into proper queues
	void push_red(Node_Patient *node);		//push patient into red queue
	void push_yellow(Node_RED *node);		//push patient into yellow queue
	void push_green(Node_YELLOW *node);		//push patient into green queue
	void push_green2(Node_GREEN *node);		//push patient into itself
	Node_GREEN *g_deque();					//dequeue for patient
	void pop_red();							//popping and giving the memory back red queue
	void pop_yellow();						//popping and giving the memory back yellow queue
	void pop_green();						//popping and giving the memory back green queue
	void islemyap();						//creating the relationship between queues
	void qyaz();							//writing queues to the screen
	void close();							//giving all the memory back

};

#endif 
