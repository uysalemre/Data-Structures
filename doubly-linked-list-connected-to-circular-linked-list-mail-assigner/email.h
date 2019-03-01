/* @Author
* Student Name: EMRE UYSAL
* Student ID : 150160510
* Date: 01.11.2017
*/
#define _CRT_SECURE_NO_WARNINGS
#define NAME_UZUNLUK 30
#define SURNAME_UZUNLUK 30
#ifndef EMAIL_H
#define EMAIL_H
////kayýt tutacak structlar burada bulunacaktýr//
#include <string>
#include <string.h>
using namespace std;
struct studentInfo  //doubly linked list
{
	string name;
	string surname;
	string email;
	studentInfo *prev;
	studentInfo *next;
};

struct surnameMap  //circular list
{
	string surname;
	surnameMap *next;
	studentInfo *headOfStudentsInfo;
};

#endif 