#include "queue.h"
#include <sstream>
#include <fstream>
#include <string>
void Queue::create(){  
	front = NULL;
	back = NULL;
	r_back = NULL;
	r_front = NULL;
	g_back = NULL;
	g_front = NULL;
	y_front = NULL;
	y_back = NULL;
}
//// READING FILE INTO MAIN QUEUE////
void Queue::readFileIntoQ(string filename){
	ifstream dosya;
	dosya.open(filename.c_str());
	if (dosya.is_open())
	{
		getline(dosya, line);
		while (!dosya.eof())
		{
			Node_Patient *hasta = new Node_Patient;
			hasta->next = NULL;
			dosya >> hasta->name >> hasta->arr_time >> hasta->trt_time >> hasta->complaint;
			trttime += hasta->trt_time;		//the sum of the treatment times
			if (!front){
				back = hasta;
				front = back;	
			}
			else
			{
				back->next = hasta;
				back = hasta;
			}
			
		}
	}
	else
	{
		cout << "FILE CANNOT BE OPENED";
	}

	//calling enqueue function for putting the patients into proper queues//
	Node_Patient *traverse = front;		
	while (traverse){
		enqueue(traverse);
		traverse = traverse->next;
	}
}

////PUT THE PATIENTS INTO PROPER QUEUES////
void Queue::enqueue(Node_Patient *traverse){ 
	if (traverse->complaint == "RED"){				//if complaint==red put the patient into red queue
		Node_RED *newnode = new Node_RED;
		newnode->name = traverse->name;
		newnode->arr_time = traverse->arr_time;
		newnode->trt_time = traverse->trt_time;
		newnode->complaint = traverse->complaint;
		newnode->next = NULL;
		if (r_front == NULL)
		{
			r_back = newnode;
			r_front = r_back;
		}
		else
		{
			r_back->next = newnode;
			r_back = newnode;
		}
	}
	if (traverse->complaint == "YELLOW"){		//if complaint==yellow put the patient into red queue
		Node_YELLOW *newnode = new Node_YELLOW;
		newnode->name = traverse->name;
		newnode->arr_time = traverse->arr_time;
		newnode->trt_time = traverse->trt_time;
		newnode->complaint = traverse->complaint;
		newnode->next = NULL;
		if (y_front == NULL)
		{
			y_back = newnode;
			y_front = y_back;
		}
		else
		{
			y_back->next = newnode;
			y_back = newnode;
		}
	}
	if (traverse->complaint == "GREEN"){		//if complaint==green put the patient into red queue
		Node_GREEN *newnode = new Node_GREEN;
		newnode->name = traverse->name;
		newnode->arr_time = traverse->arr_time;
		newnode->trt_time = traverse->trt_time;
		newnode->complaint = traverse->complaint;
		newnode->next = NULL;
		if (g_front == NULL)
		{
			g_back = newnode;
			g_front = g_back;
		}
		else
		{
			g_back->next = newnode;
			g_back = newnode;
		}
	}

}
/// PUSH FUNCTIONS FOR QUEUES THESE PUSH FUNCTIONS USED FOR CREATING RELATION BETWEEN QUEUES ///
void Queue::push_red(Node_Patient *node){
	Node_RED *newnode = new Node_RED;
	newnode->name = node->name;
	newnode->arr_time = node->arr_time;
	newnode->trt_time = node->trt_time;
	newnode->complaint = node->complaint;
	newnode->next = NULL;
	if (r_front == NULL)
	{
		r_back = newnode;
		r_front = r_back;
	}
	else
	{
		r_back->next = newnode;
		r_back = newnode;
	}
}
void Queue::push_yellow(Node_RED *node){
	Node_YELLOW *newnode = new Node_YELLOW;
	newnode->name = node->name;
	newnode->arr_time = node->arr_time;
	newnode->trt_time = node->trt_time-1;
	newnode->complaint = "YELLOW";
	newnode->next = NULL;
	if (y_front == NULL)
	{
		y_back = newnode;
		y_front = y_back;
	}
	else
	{
		y_back->next = newnode;
		y_back = newnode;
	}
}
void Queue::push_green2(Node_GREEN *node){
	Node_GREEN *newnode = new Node_GREEN;
	newnode->name = node->name;
	newnode->arr_time = node->arr_time;
	newnode->trt_time = node->trt_time;
	newnode->complaint = "GREEN";
	newnode->next = NULL;
	if (g_front == NULL)
	{
		g_back = newnode;
		g_front = g_back;
	}
	else
	{
		g_back->next = newnode;
		g_back = newnode;
	}
}
void Queue::push_green(Node_YELLOW *node){
	Node_GREEN *newnode = new Node_GREEN;
	newnode->name = node->name;
	newnode->arr_time = node->arr_time;
	newnode->trt_time = node->trt_time-2;
	newnode->complaint = "GREEN";
	newnode->next = NULL;
	if (g_front == NULL)
	{
		g_back = newnode;
		g_front = g_back;
	}
	else
	{
		g_back->next = newnode;
		g_back = newnode;
	}

}


///POP FUNCTIONS  (GIVING THE MEMORY BACK) FOR QUEUES///
void Queue::pop_red(){
	Node_RED *headNode = r_front;
	if (r_front!=NULL)
	{
		r_front = r_front->next;
	}
	else
	{
		r_front = NULL;
	}
	delete headNode;
}

void Queue::pop_yellow(){
	Node_YELLOW *headNode = y_front;
	if (y_front!= NULL)
	{
		y_front = y_front->next;
	}
	else
	{
		 y_front=NULL;
	}
	delete headNode;
}

void Queue::pop_green(){
	Node_GREEN *headNode = g_front;
	if (g_front!= NULL)
	{
		g_front = g_front->next;
	}
	else
	{
		g_front = NULL;
	}
	delete headNode;
}

Node_GREEN* Queue::g_deque(){  //DEQUEUE FUNCTION FOR GREEN QUEUE FOR HOLDING THE PATIENT//
	Node_GREEN *tr = g_front;
	
	if (g_front != NULL){
		g_front = g_front->next;
	}
	else
	{
		pop_green();			//GIVE THE MEMORY BACK IF FRONT->NULL
	}
	tr->trt_time -= 3;			
	return tr;
}
// SELECTING PROPER Q FOR WORK AND MAKING THE PATIENTS TREATMENTS//
void Queue::islemyap(){
	Node_Patient *firstcoming = new Node_Patient;		//founding the first and priorty person
	firstcoming->next = NULL;
	Node_GREEN *greenbas=NULL;
	int time = 0;										//time management for queues
	int counter = 1;									// counter for time slices
	while (trttime!=0)
	{
		if (r_front == NULL && y_front == NULL)			//red and yellow -> null first choice must be green
		{
			firstcoming->name = g_front->name;
			firstcoming->arr_time = g_front->arr_time;
			firstcoming->complaint = g_front->complaint;
			firstcoming->trt_time = g_front->trt_time;

		}
		else if (r_front == NULL)						//red -> null first choice must be yellow
		{
			firstcoming->name = y_front->name;
			firstcoming->arr_time = y_front->arr_time;
			firstcoming->complaint = y_front->complaint;
			firstcoming->trt_time = y_front->trt_time;
		}
		else
		{
			firstcoming->name = r_front->name;			//else first choice must be red
			firstcoming->arr_time = r_front->arr_time;
			firstcoming->complaint = r_front->complaint;
			firstcoming->trt_time = r_front->trt_time;
		}
		if (y_front != NULL && firstcoming->arr_time > y_front->arr_time) //yellow nut null and first choice' s arrive time greater than yellow than first choice is yellow
		{
			firstcoming->name = y_front->name;
			firstcoming->arr_time = y_front->arr_time;
			firstcoming->complaint = y_front->complaint;
			firstcoming->trt_time = y_front->trt_time;
		}
		if (g_front != NULL && firstcoming->arr_time > g_front->arr_time)	//green nut null and first choice' s arrive time greater than green than first choice is green
		{
			firstcoming->name = g_front->name;
			firstcoming->arr_time = g_front->arr_time;
			firstcoming->complaint = g_front->complaint;
			firstcoming->trt_time = g_front->trt_time;
		}
		if (firstcoming->complaint == "RED"){			//if first choice is red
			time = 1;									//time requirement for red
			push_yellow(r_front);						//push it into yellow
			pop_red();									//pop it and give the memory back
		}
		else if (firstcoming->complaint=="YELLOW")		//if first choice yellow
		{				
			if (firstcoming->trt_time < 2){				//if treatment time <yellow's required time
				time = firstcoming->trt_time;			//then time slice equals to first choice's time
			}
			else
			{
				time = 2;								//default time slice
			}
			push_green(y_front);						//push it into green
			pop_yellow();								//pop it from yellow and give the memory back
		}
		else if (firstcoming->complaint == "GREEN")		//if first choice is green
		{
			if (firstcoming->trt_time < 3){				//if treatment time < green's required time
				time = firstcoming->trt_time;			//time equals to first choice time
			}
			else
			{
				time = 3;								//default time slice
			}
			greenbas = g_deque();						//for the excess time we need to take the front front of the greeen
		}
		
		if (greenbas!=NULL)								//if taken front not null
		{
			if (greenbas->complaint == "GREEN")
			{
				if (greenbas->trt_time > 0)				//if its treatment time greater than 0
				{
					push_green2(greenbas);				//push it again to green from back so it will be in order
				}
			}	
		}
		while (time != 0)								//printing screen the time slices
		{
			cout <<endl<<endl <<counter << ". time slice " << firstcoming->name << endl;
			time--;												
			counter++;									//counter for time slice numbers
			trttime--;									//total treatment time control for while loop control

		}
		//qyaz(); //---------> if you want to see the queue ops. step by step, delete the comment 
	}
	
}


//WRITING THE QUEUES TO SCREEN FUNCTION//
void Queue::qyaz(){
	Node_Patient *traverse = front;
	cout <<endl<<endl<<endl <<"-------------------------------INPUT FILE PATIENTS--------------------------" << endl << endl;
	cout << line << endl;
	while (traverse != NULL)
	{
		cout << traverse->name << "\t\t" << traverse->arr_time << "\t\t" << traverse->trt_time << "\t\t" << traverse->complaint << endl;
		traverse = traverse->next;
	}
	cout <<endl<<endl << "------------------------------PATIENTS IN THE RED---------------" << endl;
	Node_RED *tr = r_front;
	while (tr != NULL)
	{
		cout << tr->name << "\t\t" << tr->arr_time << "\t\t" << tr->trt_time << "\t\t" << tr->complaint << endl;
		tr = tr->next;
	}
	cout << endl << endl << "-----------------------------PATIENTS IN THE YELLOW---------------" << endl;
	Node_YELLOW *tr1 = y_front;
	while (tr1 != NULL)
	{
		cout << tr1->name << "\t\t" << tr1->arr_time << "\t\t" << tr1->trt_time << "\t\t" << tr1->complaint << endl;
		tr1 = tr1->next;
	}
	cout << endl << endl << "------------------------------PATIENTS IN THE GREEN---------------" << endl;
	Node_GREEN *tr2 = g_front;
	while (tr2 != NULL)
	{
		cout << tr2->name << "\t\t" << tr2->arr_time << "\t\t" << tr2->trt_time << "\t\t" << tr2->complaint << endl;
		tr2 = tr2->next;
	}
}

void Queue::close(){
	
	while (front!=NULL)
	{	
		Node_Patient *trvrs = front;
		front = front->next;
		delete trvrs;
	}
}