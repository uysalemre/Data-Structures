/* @Author
* Student Name: EMRE UYSAL
* Student ID : 150160510
* Date: 01.11.2017
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "listeislemleri.h"

using namespace std;
typedef list email;
email mail;

void menuYazdir()
{
	cout  << endl;
	cout << "\t\t\tEMAIL ADDRESS PROGRAM" << endl;
	cout << "____________________________" << endl;
	cout << "CHOOSE AN OPERATION PLEASE" << endl;
	cout << "____________________________" << endl;
	cout << "1: CREATE" << endl;
	cout << "2: INSERT ALL " << endl;
	cout << "3: INSERT NEW RECORD" << endl;
	cout << "4: DELETE STUDENT" << endl;
	cout << "5: DELETE SURNAME NODE" << endl;
	cout << "6: UPDATE" << endl;
	cout << "7: WRITE TO SCREEN FOR SHOWING THE CURRENT LIST" << endl;
	cout << "8: WRITE TO FILE" << endl;
	cout << "____________________________" << endl;
	cout << endl;
	cout << "Enter an option : ";
}

bool kntrl = false;		//once listenin yaratýlmasý ýcýn kontrol degýskený olusturuldu.
bool kntrl1 = false;	//listede deðiþim yapýlcak iþlemler için insert fonksiyonu calýstýrýlmasý için kontrol degýskený

void listeYarat()
{
	mail.createList();
	cout << "LIST CREATED" << endl;
	kntrl = true;
}

void insertYap()//insertAll fonksiyonu icin 
{	

	if (kntrl==true){
		cout << "PLEASE ENTER NAME OF THE INPUT FILE (sth.txt) :";
		char secim[NAME_UZUNLUK];
		cin.ignore(1000, '\n');
		cin.getline(secim, NAME_UZUNLUK);
		mail.insertAll(secim);
		kntrl1 = true;
	}
	else
		cout << "!--FIRST PLEASE CREATE LIST WITH USING 1. FUNCTION--!" << endl;
}

void ekranayaz(){			//ekrana yazma fonksiyonu ýcýn gecerlý
	mail.printList();
}

void yeniKayitInsert()			//yený kayýt ýnsert etmek ýcýn 
{
	if (kntrl1 == true){
		cout << "PLEASE ENTER NAME OF THE PERSON :";
		string name,surname,mailto;
		cin.ignore(1000, '\n');
		cin>>name;
		cout << "PLEASE ENTER THE SURNAME OF THE PERSON :";
		cin.ignore(1000, '\n');
		cin >> surname;
		cout << "PLEASE ENTER THE MAIL OF THE PERSON :";
		cin >> mailto;
		mail.insertNewRecord(name, surname, mailto);
	}
	else
		cout << "!--PLEASE INSERT RECORDS FROM INPUT FILE WITH USING 2. FUNCTION--!" << endl;
}

void ogrenciNodeSil()		//surname Node fonksýyonu ýcýn
{
	if (kntrl1 == true){
		cout << "PLEASE ENTER THE SURNAME THAT YOU WANT TO DELETE:";
		string surname;
		cin.ignore(1000, '\n');
		cin >> surname;
		mail.deleteSurnameNode(surname);
	}
	else
		cout << "!--PLEASE INSERT RECORDS FROM INPUT FILE WITH USING 2. FUNCTION--!" << endl;
}

void ogrenciSil()		//delete student ýcýn
{
	if (kntrl1 == true){
		cout << "PLEASE ENTER THE STUDENT'S MAIL THAT YOU WANT TO DELETE:" ;
		string mailto,surname;
		cin.ignore(1000, '\n');
		cin >> mailto;
		cout << "PLEASE ENTER THE STUDENT'S SURNAME THAT YOU WANT TO DELETE:" ;
		cin >> surname;
		mail.deleteStudent(mailto,surname);
	}
	else
		cout << "!--PLEASE INSERT RECORDS FROM INPUT FILE WITH USING 2. FUNCTION--!" << endl;
}

void guncelle()		//lýste update ýcýn 
{
	if (kntrl1 == true){
		string name, surname, email;
		cout << "PLEASE ENTER THE NAME OF THE PERSON THAT YOU WANT TO UPDATE:" ;
		cin.ignore(1000, '\n');
		cin >> name;
		cout << "PLEASE ENTER THE SURNAME OF THE PERSON THAT YOU WANT TO UPDATE:" ;
		cin >> surname;
		cout << "PLEASE ENTER THE EMAIL OF THE PERSON THAT YOU WANT TO UPDATE:";
		cin >> email;
		mail.updateList(name, surname, email);
	}
	else
		cout << "!--PLEASE INSERT RECORDS FROM INPUT FILE WITH USING 2. FUNCTION--!" << endl;
}

void dosyayaYaz(){ //dosyaya yazma fonksýyonu ýcýn
	if (kntrl1 == true){
		cout << "--THE OUTPUT WRITTEN IN EMAILLIST.TXT--" << endl;
		mail.writeToFile();
	}
	else
		cout << "!--PLEASE INSERT RECORDS FROM INPUT FILE WITH USING 2. FUNCTION--!" << endl;
}

bool islemYap(int secim){  //ýslem yapýlmasý ýcýn fonksýyon cagýrdýgýmýz fonksýyon
	bool bitir = false;
	switch (secim)
	{
	case 1:
		listeYarat();
		break;
	case 2:
		insertYap();
		break;
	case 3:
		yeniKayitInsert();
		break;
	case 4:
		ogrenciSil();
		break;
	case 5:
		ogrenciNodeSil();
		break;
	case 6:
		guncelle();
		break;
	case 7:
		ekranayaz();
		break;
	case 8:
		dosyayaYaz();
		break;
		bitir = true;
	default:
		cout << "!--ERROR--YOU MADE AN INVALID CHOICE--!" << endl;
		cout << "TRY AGAIN :";
		cin >> secim;
		bitir = islemYap(secim);
		break;
	}
	return bitir;
}

int main(){
	bool control = false;			//sureklý menu yazdýrma ve secým yaptýrma ýcýn
	int secim;
	while (!control)
	{
		menuYazdir();
		cin >> secim;
		control = islemYap(secim);
	}
	getchar();
	return 0;
}