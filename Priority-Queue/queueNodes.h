#ifndef QUEUENODES_H
#define QUEUENODES_H
#include <iostream>
using namespace std;

struct Node_Patient //main queue for file reading
{
	string name;
	string complaint;
	int arr_time;
	int trt_time;
	Node_Patient *next;
};

typedef Node_Patient Node_RED;
typedef Node_Patient Node_YELLOW;
typedef Node_Patient Node_GREEN;
//
//
//struct Node_RED		//red queue
//{
//	string name;
//	string complaint;
//	int arr_time;
//	int trt_time;
//	Node_RED *next;
//};
//
//struct Node_YELLOW	//yellow queue
//{
//	string name;
//	string complaint;
//	int arr_time;
//	int trt_time;
//	Node_YELLOW *next;
//};
//
//struct Node_GREEN	//green queue
//{
//	string name;
//	string complaint;
//	int arr_time;
//	int trt_time;
//	Node_GREEN *next;
//};

#endif