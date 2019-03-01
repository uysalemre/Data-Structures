/*
@Author: EMRE UYSAL
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
bool rowchecker();
bool columnchecker();
bool areachecker();
bool sudokuchecker();
int s[9][9];
int row, column;

int main(int argc,char *argv[]){
	
	string filename = argv[1];
	ifstream myfile;
	string line;
	myfile.open("filename");
	if (myfile.is_open())
	{
		for (row = 0; row <= 8;row++){
			for (column = 0; column <= 8;column++){
				myfile >> s[row][column];
			}
		}
		for (row = 0; row <= 8; row++){
			for (column = 0; column <= 8; column++){
				cout<< s[row][column]<<" ";
			}cout << endl;
		}////arrayi arealara bolme islemi

	}
	else cout << "Unable to open file";
	sudokuchecker();
	getchar();
	return 0;


}

bool rowchecker(){
	for (row = 0; row <= 8; row++){
		for (column = 0; column <= 8; column++){
			for (int i = column+1; i <= 8; i++){
				if (s[row][column] == s[row][i]){
					cout << "THIS SUDOKU IS NOT VALID BECAUSE OF ROWS." << endl;
					return false;
				}
			}
		}
		
	}
	
}

bool columnchecker(){
	for (row = 0; row <= 8; row++){
		for (column = 0; column <= 8; column++){
			for (int i = row + 1; i <= 8; i++){
				if (s[row][column] == s[i][column]){
					cout << "THIS SUDOKU IS NOT VALID BECAUSE OF COLUMNS." << endl;
					return false;
				}
			}
		}

	}
}


bool areachecker(){

	int check[10] = { 0 };

	for (row = 1; row <= 3; row++){
		for (column = 1; column <= 3; column++){
			for (int i = 3 * (row - 1); i < 3 * column; i++){
				for (int j = 3 * (column - 1); j < 3 * column; j++)
				{
					check[s[i][j]]++;
				}
			}

		}
	}
	for (int a = 0; a < 10; a++)
	{if (check[a] == 1){
		cout << "THIS SUDOKU IS NOT VALID BECAUSE OF AREA RULE." << endl;
	}

}
	return true;
}

	

bool sudokuchecker(){
	if ((areachecker() && columnchecker() && rowchecker()) == false)
		cout << "THIS SUDOKU IS NOT VALID" << endl;
	else
		cout << "THIS SUDOKU IS VALID" << endl;
	return true;
}






























