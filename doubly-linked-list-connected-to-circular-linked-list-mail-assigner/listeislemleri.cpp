/* @Author
* Student Name: EMRE UYSAL
* Student ID : 150160510
* Date: 01.11.2017
*/
#define _CRT_SECURE_NO_WARNINGS
#include "listeislemleri.h"
#include <fstream>
#include <string.h>
#include <string>
#include <sstream>
#include <cstring>
#include <stdio.h>
using namespace std;
		/*ODEV SURESINCE STRCMP KULLANILDI BU YUZDEN BUYUK KUCUK HARF HASSASIYETI BULUNMAKTADIR STRICMP LINUXDA STRCASECMP DE WINDOWSDA OLMADIGINDAN KULLANILAMADI*/
char sayac[10] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '10' };	//10 taneye kadar ayn� isimde ki�i eklemek i�in olu�turuldu.
int i = 0;																//ayn� ki�i eklenebilmesi i�in saya� olusturuldu.

void list::createList()
{
	kayit = NULL;														//headler�m�z� null yaparak l�steler �c�n �lk �slem� yapm�s oluyoruz
	head = NULL;
}

void list::insertAll(char secim[])
{
	//dosyadan verilerimizi okuduk//
	ifstream file;
	file.open(secim);
	if (file.is_open()) 
	{
		studentInfo *traverse = kayit, *tail = NULL;			//oncelikle verilerimizi double linked list olan studentInfoya att�k
		while (!file.eof())													//*** Bu durumda el�m�zde haz�r name ve surnameler�n oldugu double l�nked l�st�m�z olur.
		{																	//*** DOUBLE LINKED LISTI CIRCULAR I OLUSTURURKEN PARCALAYARAK ILGILI NODELARIN ALTINA YERLESTIRECEGIZ VE DAHA HIZLI BIR SEKILDE YAPI OLUSTURULACAK
			studentInfo *dosyadan;											//*** Bu herhang�b�r problem olusturmaz yine i�lem ak���m�z (circular a double baglama sekl�nde) odevde istendi�i gibi olacakt�r.
			dosyadan = new studentInfo;										//*** Sadece veri b�t�nl���n�n korunmas� ve dosya i�lemini hemen bitirme amac�yla yap�lm�st�r.
			dosyadan->prev = NULL;								//next ve prev �m�z� null yapt�k
			dosyadan->next = NULL;

			getline(file, dosyadan->name, '\t');				//getline ile once tab a kadar daha sonra bosluga kadar okuyup �nputumuza att�k
			getline(file, dosyadan->surname);
			if (dosyadan->surname.compare("") == 0)			//bos kay�tla kars�lasma �ht�mal�ne kars� 
				break;


			if (!kayit)									//record her zaman listenin bas�n� tutacak --eger record yoksa
			{				
				kayit = dosyadan;							//record yan� l�sten�n bas� d�rek �nputa es�t olacak
			}
			else if (strcmp(dosyadan->surname.c_str(), kayit->surname.c_str()) < 0)	//eger gelen dosyadan->surname i normal recordunkinden alfebetik olarak onceyse	
			{
				dosyadan->next = kayit;						//basa ekleme yap�l�r						
				kayit = dosyadan;							//record yine bas� gosterir	
			}
			else											
			{
				traverse = kayit;							//record u traverse e es�tled�k l�ste ustunde dolasmak �c�n
				while (traverse && strcmp(dosyadan->surname.c_str(), traverse->surname.c_str()) >= 0) {	//eger alfabet�k olarak dosyadan sonra gel�yorsa
					tail = traverse;																	//burada traverse ile listede dosyadan u eklememiz gereken noktaya kadar geld�k
					traverse = traverse->next;															
				}
				if (traverse) {								//eger traverse varsa dosyadanu istedi�imiz noktada araya sokmus olduk
					dosyadan->next = traverse;
					dosyadan->prev = tail;
					tail->next = dosyadan;
					traverse->prev = dosyadan;
				}
				else {
					tail->next = dosyadan;						//eger traverse yoksa da �nputu sondan eklem�s olduk
					dosyadan->prev = tail;
				}
			}
		}
	}
	else {
		cerr << "!--ERROR--FILE CANNOT BE OPENED--!";		//dosya ac�lamazsa hata mesaj� yazd�r�ld�
		getchar();
		return;
	}
	file.close();											//dosya kapat�ld�

	//------------------------DOSYA OKUMA ILE ISIMIZ BITTI SURNAME MAP E YER ALIP CIRCULAR LISTIMIZE BAGLI DOUBLE LINKED LISTLERI EKLEYECEGIZ --------------------------//
	
	studentInfo *gezici;
	gezici = kayit;										//recordlar uzer�nde gezmek �c�n olusturdugumuz po�nter
	while (gezici != NULL) 
	{
		if (gezici->next != NULL) {
			surnameMap *temp = new surnameMap;				//surnameMap e ekleme yapab�lmek �c�n bos node olusturuldu.
			studentInfo *tempStudentInfo0 = new studentInfo;// studentInfoya ekleme yapab�lmek �c�n bos node olusturuldu.

			if (head == NULL) {								//eger head NULL sa 
				head = temp;								
				head->surname = gezici->surname;
				head->next = NULL;
				head->headOfStudentsInfo = tempStudentInfo0;	//SurnameMap i studentInfoya baglayacak node a yer ald�k
				head->headOfStudentsInfo->name = gezici->name;				//gez�c�n�n name ve surname �n� atad�k
				head->headOfStudentsInfo->surname = gezici->surname;
				head->headOfStudentsInfo->email = gezici->surname + "@itu.edu.tr";	
				head->headOfStudentsInfo->next = NULL;						
				head->headOfStudentsInfo->prev = NULL;
				gezici = gezici->next;							//gez�c�y� 1 art�r�p donguden c�kt�k
				continue;
			}

			if (gezici->surname != gezici->prev->surname) {		//bulundugumuz surname 1 oncek�ne es�t deg�lse
				temp->surname = gezici->surname;				//surnamem�z� surnameMap �n b�r sonrak� nodu na at�yoruz
				temp->next = head;
				temp->headOfStudentsInfo = tempStudentInfo0;
				temp->headOfStudentsInfo->name = gezici->name;				//StudentInfo baglant�s� �c�n node a yer ald�k ve b�lg�ler� att�k
				temp->headOfStudentsInfo->surname = gezici->surname;
				temp->headOfStudentsInfo->email = gezici->surname + "@itu.edu.tr";
				temp->headOfStudentsInfo->next = NULL;
				temp->headOfStudentsInfo->prev = NULL;
				head = temp;											//listeye bastan ekleme yapt�g�m�z �c�n head � surekl� basta tutmam�z gerekt�g� �c�n head=temp oldu
			}
			else if (gezici->surname == gezici->prev->surname) {		//eger es�tl�k saglan�rsa 1 oncek�yle surnamemapde bulunulan nodun studentInfosuna ekleme yap�l�r.
				studentInfo *tempStudentInfo = new studentInfo;
				head->headOfStudentsInfo->next = tempStudentInfo;
				head->headOfStudentsInfo->next->name = gezici->name;
				head->headOfStudentsInfo->next->surname = gezici->surname;
				//headofstudentInfonun alt�na gelecek ema�ller buradan baslad�g� �c�n kontroller� burada yap�yoruz//
				if (head->headOfStudentsInfo->name == head->headOfStudentsInfo->next->name)
				{
					head->headOfStudentsInfo->next->email = gezici->surname+gezici->name+ "@itu.edu.tr";
					if (head->headOfStudentsInfo->name == head->headOfStudentsInfo->prev->name)	//ayni isimli mail gelirse say� eklenecek k�s�m
					{
						head->headOfStudentsInfo->next->email = gezici->surname + gezici->name+sayac[i]+ "@itu.edu.tr";
						i++;
					}
					
				}
				else{
					if (strncmp(head->headOfStudentsInfo->name.c_str(), head->headOfStudentsInfo->next->name.c_str(), 1)==0)
					{
						if (strncmp(head->headOfStudentsInfo->name.c_str(), head->headOfStudentsInfo->next->name.c_str(), 2)==0)
						{
							head->headOfStudentsInfo->next->email = gezici->surname + gezici->name.at(0) + gezici->name.at(1) + gezici->name.at(2) + "@itu.edu.tr";
							
						}
						else
						{
							head->headOfStudentsInfo->next->email = gezici->surname + gezici->name.at(0)+gezici->name.at(1) + "@itu.edu.tr";
							
						}
					}
					else
					{
						head->headOfStudentsInfo->next->email = gezici->surname + gezici->name.at(0) + "@itu.edu.tr";
						
					}
				}
				head->headOfStudentsInfo->next->prev = head->headOfStudentsInfo;
				head->headOfStudentsInfo = head->headOfStudentsInfo->next;
			}
		}
		gezici = gezici->next;											//geziciyi art�r�yoruz ki dongu tum kay�tlar �c�n donsun
	}
	controlCircular();														//last node's next pointing the head now 
}

void list::printList() {												//multilisti ekrana yazd�rmak i�in belirledi�im bir formatta fonksiyon
	surnameMap *traverse;
	studentInfo *traverse2;
	traverse = head;
	do {
		cout << traverse->surname<< endl;
		cout << "__________________" << endl;
		traverse2 = traverse->headOfStudentsInfo;
		while (traverse2) {
			cout << " -> " << traverse2->email << " -> " << traverse2->name << " -> " << traverse2->surname << endl;
			traverse2 = traverse2->prev;
		}

		cout << "____________________________________________________________" << endl;
		traverse = traverse->next;
	} while (traverse->next != head->next);
}

void list::insertNewRecord(string nm,string srnm,string ml)  
{
	
	surnameMap *traverse, *tail = NULL;
	traverse = head;
	surnameMap *newnode = new surnameMap;
	newnode->surname = srnm;
	newnode->next = NULL;
	studentInfo *nw = new studentInfo;
	newnode->headOfStudentsInfo = NULL;
	nw->email = ml;
	nw->name = nm;
	nw->surname = srnm;
	nw->next = NULL;
	nw->prev = NULL;
	//kay�tlar� kars�last�r�p ekleme yap�yoruz bu sek�lde sort �slem� �c�n ayr� b�r fonks�yona gerek kalm�yor
	if (strcmp(newnode->surname.c_str(), head->surname.c_str()) > 0){		//bastan ekleme
		newnode->next = head;
		head = newnode;
		newnode->headOfStudentsInfo = nw;
		head->headOfStudentsInfo->name = nw->name;
		head->headOfStudentsInfo->surname = nw->surname;
		head->headOfStudentsInfo->email = nw->email;
		return;
	}
	while (traverse && strcmp(traverse->surname.c_str(), newnode->surname.c_str()) >= 0){	//elimizdeki kay�t alfebet�k olarak buyuk oldukca
		if (strcmp(newnode->surname.c_str(), traverse->surname.c_str()) == 0){
			studentInfo *rr=new studentInfo;
			rr->name = nw->name;
			rr->email = nw->email;
			rr->surname = nw->surname;
			traverse->headOfStudentsInfo->next=rr;
			rr->prev = traverse->headOfStudentsInfo;
			rr->next = NULL;
			traverse->headOfStudentsInfo = rr;
			return;
		}
		tail = traverse;														//kayd� ekl�yceg�m�z yer� buluyoruz 
		traverse = traverse->next;
	}
	if (traverse){																//kayd� araya sokuyoruz
		studentInfo *kk=new studentInfo;
		tail->next = newnode;
		newnode->headOfStudentsInfo = kk;
		newnode->headOfStudentsInfo->next = NULL;
		newnode->headOfStudentsInfo->prev = NULL;
		newnode->headOfStudentsInfo->name = nw->name;
		newnode->headOfStudentsInfo->surname = nw->surname;
		newnode->headOfStudentsInfo->email = nw->email;
		newnode->next = traverse;
	}
	else																		//araya gelmeyecekse sona ekl�yoruz
	{
		studentInfo *kk = new studentInfo;
		tail->next = newnode;
		newnode->headOfStudentsInfo = kk;
		newnode->headOfStudentsInfo->next = NULL;
		newnode->headOfStudentsInfo->prev = NULL;
		newnode->headOfStudentsInfo->name = nw->name;
		newnode->headOfStudentsInfo->surname = nw->surname;
		newnode->headOfStudentsInfo->email = nw->email;
		newnode->next = NULL;	
	}
	
}
void list::deleteStudent(string mail,string srnm) 
{
	surnameMap *traverse;
	traverse = head;
	while (traverse!= NULL){
		if (strcmp(srnm.c_str(), traverse->surname.c_str())==0)						//surname kars�last�rmas�
		{	
			while (traverse->headOfStudentsInfo!=NULL)
			{
				if (strcmp(traverse->headOfStudentsInfo->email.c_str(), mail.c_str()) == 0)		//sileceg�m�z yer� bulup  mailler tek oldugu �c�n ma�le gore s�l�yoruz
				{
					
					 traverse->headOfStudentsInfo->email="";										//bu sek�lde atama yapt�g�m�zda ekstra node �slem� yapmadan s�lm�s oluyoruz
					 traverse->headOfStudentsInfo->name="";											//nodelar�n kald�r�lmas�yla asl�nda ayn� �slem oluyor suan yap�lan
					 traverse->headOfStudentsInfo->surname="";
					
					 if(traverse->headOfStudentsInfo->prev){										//s�ld�kten sonra head �m�z� �lg�l� yer�ne al�yoruz
						traverse->headOfStudentsInfo = traverse->headOfStudentsInfo->prev;
					 }
					 return;
				}
				else
				{
					traverse->headOfStudentsInfo = traverse->headOfStudentsInfo->prev;				//eslesme olmazsa ayn� ma�llerde head �lerlet�yoruz
					return;
				}
			}
		}
		
			traverse = traverse->next;																//soyadlar� �lerlet�yoruz arama �c�n
	}
}
void list::deleteSurnameNode(string srnm)
{
	surnameMap *traverse;
	traverse = head;
	while (traverse != NULL){

		if (strcmp(srnm.c_str(), traverse->surname.c_str()) == 0)								//sadece surname nodonu s�lmek �c�n surname kars�last�rmas� yeterl�
		{
			if (traverse->headOfStudentsInfo != NULL){
				while (traverse->headOfStudentsInfo != NULL){									//�cer�s�nde ogrenc� kayd� varsa onlar� s�l�yoruz
					deleteStudent(traverse->headOfStudentsInfo->email, traverse->headOfStudentsInfo->surname);
					traverse->headOfStudentsInfo=traverse->headOfStudentsInfo->prev;
				}
				traverse->surname = "";															//nodeumuzu siliyoruz
				return;
			}
			else
			{
				surnameMap *a;																//ogrenc� kayd� yoksa o nodu s�l�yoruz
				a = traverse;
				traverse = traverse->next;
				delete a;
				return;
			}
		}
		traverse = traverse->next;
	}
}
void list::updateList(string nm,string srnm,string email)
{
	surnameMap *traverse;
	traverse = head;
	while (traverse != NULL){
		if (strcmp(srnm.c_str(), traverse->surname.c_str()) == 0)					//surname kars�last�rmas�
		{
			while (traverse->headOfStudentsInfo != NULL)
			{
				if (strcmp(traverse->headOfStudentsInfo->email.c_str(), email.c_str()) == 0)	//ema�l kars�last�rmas�
				{
					string nm1, srnm1, email1;
					cout << "PLEASE ENTER NEW NAME:";											//yen� g�rd�ler al�n�yor
					cin >> nm1;
					cout << "PLEASE ENTER NEW SURNAME:";
					cin >> srnm1;
					cout << "PLEASE ENTER NEW EMAIL:";
					cin >> email1;
					traverse->headOfStudentsInfo->email = nm1;									//yen� g�rd�ler atan�yor
					traverse->headOfStudentsInfo->name = srnm1;
					traverse->headOfStudentsInfo->surname =email1;
					return;
				}
				else
				{
					traverse->headOfStudentsInfo = traverse->headOfStudentsInfo->prev;
				}
			}
		}

		traverse = traverse->next;
	}
}

void list::writeToFile()
{
	ofstream dosya;																											//kay�tlar� dosyaya z-den a-ya olacak sek�lde 
	dosya.open("emailList.txt", ios::trunc);																				//her yaz�sta s�f�rdan s�l�p yaz�yoruz
	if (dosya.is_open()){
		surnameMap *traverse;
		studentInfo *traverse2;
		traverse = head;
		dosya << "\t\t------ITU EMAIL CREATION PROGRAM FOR NEW STUDENTS------" << endl;
		dosya << "\t\t\t------ORDERED DESCENDING Z TO A------" << endl;
		do{
			dosya << traverse->surname << endl;
			dosya << "__________________" << endl;
			traverse2 = traverse->headOfStudentsInfo;
			while (traverse2) {
				dosya << " -> " << traverse2->email << " -> " << traverse2->name << " -> " << traverse2->surname << endl;
				traverse2 = traverse2->prev;
			}

			dosya << "____________________________________________________________" << endl;
			traverse = traverse->next;
		} while (traverse->next != head->next);
	}
	else{
		cout << "!--ERROR--THE FILE CANNOT BE OPENED--!";
	}
	dosya.close();
}
void list:: controlCircular(){						
	surnameMap *traverse;
	traverse = head;
	while (traverse ->next!= NULL){
		traverse = traverse->next;
	}
	traverse->next = head;
}
