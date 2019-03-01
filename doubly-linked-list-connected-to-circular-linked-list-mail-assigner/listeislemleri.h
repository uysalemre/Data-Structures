/* @Author
* Student Name: EMRE UYSAL
* Student ID : 150160510
* Date: 01.11.2017
*/
#define _CRT_SECURE_NO_WARNINGS
#ifndef LISTEISLEMLERI_H
#define LISTEISLEMLERI_H
#include <iostream>
#include "email.h"
using namespace std;
struct list{
	surnameMap *head;     //surnameMap �n surekl� head�n� elde tutmak �c�n
	studentInfo *kayit;		//StudentInfonun head �n� elde surekl� tutab�lmek �c�n
	void printList();
	void createList();						
	void insertAll(char []);				
	void insertNewRecord(string c,string b,string a);					
	void deleteStudent(string a,string b);					
	void deleteSurnameNode(string a);
	void updateList(string a,string b,string c);
	void writeToFile();
	void controlCircular();
};
#endif 
