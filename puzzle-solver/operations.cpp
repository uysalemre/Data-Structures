/* @Author
* Name: EMRE UYSAL
* Date: 08.10.2017
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <istream>
#include <cstdio>
#include <cstring>
#include "searchedword.h"
#define public
using namespace std;
#define MAX_LEN 50 ///max uzunluk olarak tanýmlanan deðiþken
int g_row, g_column, g_endrow, g_endcolumn;
///wordlerimizi tersten okumak için olusturdugumuz fonksiyon(strrev fonksiyonu linuxda çalýþmýyor)
char* _strrev(char* word)
{
	char  chr;
	char* word0 = word - 1;
	char* word1 = word;
	while (*word1)
	{
		++word1;
	}
	while (word1-- > ++word0)
	{
		chr = *word0;
		*word0 = *word1;
		*word1 = chr;
	}
	return word;
}

///diagonalSearch iþlemi x yönünde ///
public bool diagonalSearchX(char **puzzleArray, searchedWord *word, bool direction)
{	
	if (!direction){
		word->word = _strrev(word->word);
	}
	char *ss;
	ss = new char[15];
	for (int row = 0; row < 15 - (word->wordLength - 1); row++)//puzzle indisleri aþmamalý
	{
		for (int column = 0; column < 15 - (word->wordLength - 1); column++)//puzzle indisleri aþmamalý
		{
			int i = 0;
				while (*(word->word+i) == *(*(puzzleArray+row + i)+i + column) && row + i < 15 && column + i < 15)
			{
				if (i == word->wordLength - 1){
					int beginrow, endrow,begincolumn,endcolumn;
					g_row=beginrow = row;
					g_column=begincolumn = column;
					g_endcolumn=endcolumn = column + i;
					g_endrow=endrow = row+i;
					if (!direction){///kelimeyi çeviriyoruz
						word->word = _strrev(word->word);
					}
					cout << word->word << " DIAGONAL " <<"["<<beginrow+1<<"]["<<begincolumn+1<< "]--[" << endrow+1<<"]["<<endcolumn+1<<"]"<< endl;
					///bulduðum kelimeyi dosyaya yazma///////////
					ofstream yazfile;
					yazfile.open("foundWordsInfo.txt", ios::app);
					if (yazfile.is_open()){
						yazfile << word->word << " DIAGONAL " << "[" << beginrow + 1 << "][" << begincolumn + 1 << "]--[" << endrow + 1 << "][" << endcolumn + 1 << "]" << endl;
					}
					yazfile.close();
					return true;

				}
				else if (i + column > 15)
					break;
				i++;
			}
			
		}
	}
	if (!direction){////kelimeyi çeviriyoruz
		word->word = _strrev(word->word);
	}
	delete[] ss;
	return false;
}
////diagonalSearch y ekseni yonunde////
public bool diagonalSearchY(char **puzzleArray, searchedWord *word, bool direction)
{
	if (!direction){
		word->word = _strrev(word->word);
	}
	char *ss;
	ss = new char[15];
	for (int row = 0; row < 15 - (word->wordLength - 1); row++)
	{
		for (int column = 15; column > (word->wordLength - 1); column--)
		{
			int i = 0;
			while (*(word->word+i) == *(*(puzzleArray+row + i)+column - i) && row + i < 15 && column - i >= 0)
			{
				if (i == word->wordLength - 1){
					int beginrow, endrow, begincolumn, endcolumn;
					g_row=beginrow = row;
					g_column=begincolumn = column;
					g_endcolumn=endcolumn = column - i;
					g_endrow=endrow = row + i;
					if (i == word->wordLength - 1){
						if (!direction){/////ters çevirme
							word->word = _strrev(word->word);
						}
						cout << word->word << " DIAGONAL " << "[" << endrow + 1 << "][" << endcolumn + 1 << "]--[" << beginrow + 1 << "][" << begincolumn + 1 << "]" << endl;
						/////kelimeleri dosyaya yazma iþelmi//////
						ofstream yazfile;
						yazfile.open("foundWordsInfo.txt", ios::app);
						if (yazfile.is_open()){
							yazfile << word->word << " DIAGONAL " << "[" << endrow + 1 << "][" << endcolumn + 1 << "]--[" << beginrow + 1 << "][" << begincolumn + 1 << "]" << endl;
						}
						yazfile.close();
						return true;
					}
				}
				else if (i + column > 15)
					break;
				i++;
			}

		}
	}
	if (!direction){/////ters çevirme
		word->word = _strrev(word->word);
	}
	delete[] ss;
	return false;
}


///horizontalSearch iþlemi///
public bool horizontalSearch(char **puzzleArray, searchedWord *word, int direction)
{	
	if (!direction){///ters çevirme iþlemi
		word->word = _strrev(word->word);
	}
	char *ss;
	ss = new char[15];
	for (int row = 0; row < 15; row++)
	{
		for (int column = 0; column < 15 - (word->wordLength - 1); column++)
		{
			int i = 0;

			while (*(word->word+i) == *(*(puzzleArray+row)+i+column))
			{
				if (i == word->wordLength - 1){
					int beginrow, endrow, begincolumn, endcolumn;
					g_row=beginrow = row;
					g_column=begincolumn = column;
					g_endcolumn=endcolumn = column + i;
					g_endrow = g_row;
					if (i == word->wordLength - 1){
						if (!direction){
							word->word = _strrev(word->word);
						}
						cout << word->word << " HORIZONTAL " << "[" << beginrow + 1 << "][" << begincolumn + 1 << "]--[" << beginrow + 1 << "][" << endcolumn + 1 << "]" << endl;
						////bulunan kelimeleri dosyaya yazma iþlemi
						ofstream yazfile;
						yazfile.open("foundWordsInfo.txt", ios::app);
						if (yazfile.is_open()){
							yazfile << word->word << " HORIZONTAL " << "[" << beginrow + 1 << "][" << begincolumn + 1 << "]--[" << beginrow + 1 << "][" << endcolumn + 1 << "]" << endl;
						}
						yazfile.close();
						return true;
					}
				}
				else if (i + column > 15)
					break;
				i++;
			}

		}
	}
	if (!direction){
		word->word = _strrev(word->word);
	}
	delete[] ss;
	return false;
}


///verticalSearch iþlemi///
public bool verticalSearch(char **puzzleArray, searchedWord *word, bool direction)
{
	if (!direction){////ters çevirme iþlemi
		word->word = _strrev(word->word);
	}
	char *ss;
	ss = new char[15];
	for (int row = 0; row < 15; row++)
	{
		for (int column = 0; column < 15 - (word->wordLength - 1); column++)
		{
			int i = 0;

			while (*(word->word+i) == *(*(puzzleArray+i + column)+row))
			{
				if (i == word->wordLength - 1)
				{
					int beginrow, endrow, begincolumn, endcolumn;
					g_row=beginrow = column;
					g_column=begincolumn = row;
					g_endrow=endrow = column + i;
					g_endcolumn = g_column;
					if (i == word->wordLength - 1)
					{
						if (!direction)
						{
							word->word = _strrev(word->word);
						}
						cout << word->word << " VERTICAL " << "[" << beginrow + 1 << "][" << begincolumn + 1 << "]--[" << endrow + 1 << "][" << begincolumn + 1 << "]" << endl;
						///bulunan kelimeler dosyaya yazýlýr//
						ofstream yazfile;
						yazfile.open("foundWordsInfo.txt", ios::app);
						if (yazfile.is_open()){
							yazfile << word->word << " VERTICAL " << "[" << beginrow + 1 << "][" << begincolumn + 1 << "]--[" << endrow + 1 << "][" << begincolumn + 1 << "]" << endl;
						}
						yazfile.close();
						return true;
					}
				}
				else if (i + column > 15)
					break;

				i++;

			}
		}

	}
	if (!direction){
		word->word = _strrev(word->word);
	}
	delete[] ss;
	return false;
}



int main(){
	///puzzle 2-d array olarak pointerla okundu////
	int kayitsayisi = 0;
	char **puzzleArray;
	puzzleArray = new char *[15];
	fstream myfile;
	myfile.open("puzzle.txt");
	if (myfile.is_open())
	{
		for (int row = 0; row <= 14; row++){
			*(puzzleArray+row) = new char[15];
			for (int column = 0; column <= 14; column++){
				myfile >>*(*(puzzleArray+row)+column);
			}
		}
		cout << "---------------------------PUZZLEARRAY FILE---------------------------"<<endl<<endl;
		for (int row = 0; row <= 14; row++){
			for (int column = 0; column <= 14; column++){
				cout << *(*(puzzleArray + row) + column) << " ";

			}cout << endl;
		}
	
		cout << endl;
	}
	else cout << "Unable to open file";
	myfile.close();
	////searchedwords okuma iþlemi /////
	searchedWord *temp;
	temp = new searchedWord[15];
	for (int i = 0; i < 15; i++)
	{
		((temp+i)->word) = new char[MAX_LEN];
	}
	myfile.open("searchedwords.txt");
	if (myfile.is_open())
	{
		cout << "--------------------------SEARCHEDWORDS FILE----------------------"<<endl;
		while (myfile >> temp[kayitsayisi].id >> temp[kayitsayisi].word)
		{
			((temp+kayitsayisi)->wordLength) = strlen((temp+kayitsayisi)->word);
			cout << ((temp+kayitsayisi)->id) << " " <<((temp+kayitsayisi)->word) << " " <<"  Wordlength:: " <<((temp+kayitsayisi)->wordLength) << endl;
			kayitsayisi++;
			
		}
		/// SORTING ISLEMI VE SWAP ISLEMI///
		cout << "--------------------AFTER SORTING THE SEARCHEDWORDS FILE--------------------" << endl;
		for (int i = 0; i < kayitsayisi - 1; i++)
		{
			for (int j = 0; j < kayitsayisi - i - 1; j++)
			{
				if (((temp+j)->id)>((temp+j+1)->id))
				{
					searchedWord k;
					k.word = new char[MAX_LEN];
					memcpy(&k, (temp+j), sizeof(searchedWord));
					memcpy((temp + j), (temp + j + 1),  sizeof(searchedWord));
					memcpy((temp + j + 1), &k, sizeof(searchedWord));
				}
			}
		}
		for (int i = 0; i < kayitsayisi; i++){
			cout << ((temp+i)->id) << " " <<(( temp+i)->word) << endl;
			cout << "\t\t" << i + 1 << ". Wordlength:: " << ((temp+i)->wordLength) << endl;
		}
	}
	else cout << "Unable to open file";
	myfile.close();
	cout << endl << endl;
	////gecici array tanýmlayýp bu arraye bilgileri yazacak ve kelimeleri bunda silip dosyaya yazacagýz çünkü puzzleArrayden bilgi silersek ortak harf kullanan kelimeler bulunamaz.////
	char **gecici;
	gecici = new char*[15];
	for (int row = 0; row <= 14; row++){
		*(gecici + row) = new char[15];
		for (int column = 0; column <= 14; column++){
			memcpy((*(gecici+row)+column),(*(puzzleArray+row)+column), sizeof(puzzleArray));//gecici array e bilgileri atadýk
		}
	}
	cout << "-------------------FOUNDED WORDS FROM THE PUZZLE-----------------------"<<endl<<endl;
	//vertical tum kelýmeler yollandý//
	for (int i = 0; i < kayitsayisi; i++)
	{
		verticalSearch(puzzleArray, (temp+i), true);
		verticalSearch(puzzleArray, (temp+i), false);
		///vertical olarak gecici arraya sildigimiz kelimleri atýyoruz//
		for (; g_row <= g_endrow; g_row++)
		{	
				*(*(gecici+g_row)+g_column) = ' ';
		}

	}
	//horizontal tum kelýmeler yollandý//
	for (int i = 0; i < kayitsayisi; i++)
	{
		horizontalSearch(puzzleArray, (temp + i), true);
		horizontalSearch(puzzleArray, (temp + i), false);
		///horizontal olarak sildigimiz kelimeleri gecici arraye atýyoruz//
			for (; g_column <= g_endcolumn; g_column++)
			{
				*(*(gecici + g_row) + g_column) = ' ';
			}
	}
	//diagonalSearchX tum kelýmeler yollandý//
	for (int i = 0; i < kayitsayisi; i++)
	{
		diagonalSearchX(puzzleArray, (temp + i), true);
		diagonalSearchX(puzzleArray, (temp + i), false);
	}
	//diagonalSearchY tum kelýmeler yollandý//
	for (int i = 0; i < kayitsayisi; i++)
	{
		diagonalSearchY(puzzleArray, (temp + i), true);
		diagonalSearchY(puzzleArray, (temp + i), false);
	}
	cout << "----------------------THE LAST VERSION OF THE PUZZLE---------------------";
	ofstream sonyazma;
	sonyazma.open("lastVersionPuzzle.txt",ios::app);
	if (sonyazma.is_open())
	{
		for (int row = 0; row <= 14; row++){
			for (int column = 0; column <= 14; column++){
				sonyazma << *(*(gecici + row) + column) << " ";

			}sonyazma << endl;
		}
	}


	cout << endl << endl;
	for (int row = 0; row <= 14; row++){
		for (int column = 0; column <= 14; column++){
			cout << *(*(gecici + row) + column) << " ";
		}cout << endl;
	}
	///because of dynamic memory allocation we must give the memory back///
	delete[] gecici;
	delete[] puzzleArray;
	delete[] temp;
	system("pause");
	return 0;
}
