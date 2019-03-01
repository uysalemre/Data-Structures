#include "queue.h"
#include <iostream>
using namespace std;

typedef Queue hospital;
hospital person;							//creating person object 

int main(){
	person.create();						//all queues created
	string filename = "patientsInfo.txt";	//file reading into queue
	person.readFileIntoQ(filename);
	person.qyaz();							//writing to screen the queues
	person.islemyap();						//making the operations
	person.close();							//give memory back
	getchar();
	return 0;
}