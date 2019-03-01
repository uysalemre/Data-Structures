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
char sayac[10] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '10' };	//10 taneye kadar ayný isimde kiþi eklemek için oluþturuldu.
int i = 0;																//ayný kiþi eklenebilmesi için sayaç olusturuldu.

void list::createList()
{
	kayit = NULL;														//headlerýmýzý null yaparak lýsteler ýcýn ýlk ýslemý yapmýs oluyoruz
	head = NULL;
}

void list::insertAll(char secim[])
{
	//dosyadan verilerimizi okuduk//
	ifstream file;
	file.open(secim);
	if (file.is_open()) 
	{
		studentInfo *traverse = kayit, *tail = NULL;			//oncelikle verilerimizi double linked list olan studentInfoya attýk
		while (!file.eof())													//*** Bu durumda elýmýzde hazýr name ve surnamelerýn oldugu double lýnked lýstýmýz olur.
		{																	//*** DOUBLE LINKED LISTI CIRCULAR I OLUSTURURKEN PARCALAYARAK ILGILI NODELARIN ALTINA YERLESTIRECEGIZ VE DAHA HIZLI BIR SEKILDE YAPI OLUSTURULACAK
			studentInfo *dosyadan;											//*** Bu herhangýbýr problem olusturmaz yine iþlem akýþýmýz (circular a double baglama seklýnde) odevde istendiði gibi olacaktýr.
			dosyadan = new studentInfo;										//*** Sadece veri bütünlüðünün korunmasý ve dosya iþlemini hemen bitirme amacýyla yapýlmýstýr.
			dosyadan->prev = NULL;								//next ve prev ýmýzý null yaptýk
			dosyadan->next = NULL;

			getline(file, dosyadan->name, '\t');				//getline ile once tab a kadar daha sonra bosluga kadar okuyup ýnputumuza attýk
			getline(file, dosyadan->surname);
			if (dosyadan->surname.compare("") == 0)			//bos kayýtla karsýlasma ýhtýmalýne karsý 
				break;


			if (!kayit)									//record her zaman listenin basýný tutacak --eger record yoksa
			{				
				kayit = dosyadan;							//record yaný lýstenýn basý dýrek ýnputa esýt olacak
			}
			else if (strcmp(dosyadan->surname.c_str(), kayit->surname.c_str()) < 0)	//eger gelen dosyadan->surname i normal recordunkinden alfebetik olarak onceyse	
			{
				dosyadan->next = kayit;						//basa ekleme yapýlýr						
				kayit = dosyadan;							//record yine basý gosterir	
			}
			else											
			{
				traverse = kayit;							//record u traverse e esýtledýk lýste ustunde dolasmak ýcýn
				while (traverse && strcmp(dosyadan->surname.c_str(), traverse->surname.c_str()) >= 0) {	//eger alfabetýk olarak dosyadan sonra gelýyorsa
					tail = traverse;																	//burada traverse ile listede dosyadan u eklememiz gereken noktaya kadar geldýk
					traverse = traverse->next;															
				}
				if (traverse) {								//eger traverse varsa dosyadanu istediðimiz noktada araya sokmus olduk
					dosyadan->next = traverse;
					dosyadan->prev = tail;
					tail->next = dosyadan;
					traverse->prev = dosyadan;
				}
				else {
					tail->next = dosyadan;						//eger traverse yoksa da ýnputu sondan eklemýs olduk
					dosyadan->prev = tail;
				}
			}
		}
	}
	else {
		cerr << "!--ERROR--FILE CANNOT BE OPENED--!";		//dosya acýlamazsa hata mesajý yazdýrýldý
		getchar();
		return;
	}
	file.close();											//dosya kapatýldý

	//------------------------DOSYA OKUMA ILE ISIMIZ BITTI SURNAME MAP E YER ALIP CIRCULAR LISTIMIZE BAGLI DOUBLE LINKED LISTLERI EKLEYECEGIZ --------------------------//
	
	studentInfo *gezici;
	gezici = kayit;										//recordlar uzerýnde gezmek ýcýn olusturdugumuz poýnter
	while (gezici != NULL) 
	{
		if (gezici->next != NULL) {
			surnameMap *temp = new surnameMap;				//surnameMap e ekleme yapabýlmek ýcýn bos node olusturuldu.
			studentInfo *tempStudentInfo0 = new studentInfo;// studentInfoya ekleme yapabýlmek ýcýn bos node olusturuldu.

			if (head == NULL) {								//eger head NULL sa 
				head = temp;								
				head->surname = gezici->surname;
				head->next = NULL;
				head->headOfStudentsInfo = tempStudentInfo0;	//SurnameMap i studentInfoya baglayacak node a yer aldýk
				head->headOfStudentsInfo->name = gezici->name;				//gezýcýnýn name ve surname ýný atadýk
				head->headOfStudentsInfo->surname = gezici->surname;
				head->headOfStudentsInfo->email = gezici->surname + "@itu.edu.tr";	
				head->headOfStudentsInfo->next = NULL;						
				head->headOfStudentsInfo->prev = NULL;
				gezici = gezici->next;							//gezýcýyý 1 artýrýp donguden cýktýk
				continue;
			}

			if (gezici->surname != gezici->prev->surname) {		//bulundugumuz surname 1 oncekýne esýt degýlse
				temp->surname = gezici->surname;				//surnamemýzý surnameMap ýn býr sonraký nodu na atýyoruz
				temp->next = head;
				temp->headOfStudentsInfo = tempStudentInfo0;
				temp->headOfStudentsInfo->name = gezici->name;				//StudentInfo baglantýsý ýcýn node a yer aldýk ve býlgýlerý attýk
				temp->headOfStudentsInfo->surname = gezici->surname;
				temp->headOfStudentsInfo->email = gezici->surname + "@itu.edu.tr";
				temp->headOfStudentsInfo->next = NULL;
				temp->headOfStudentsInfo->prev = NULL;
				head = temp;											//listeye bastan ekleme yaptýgýmýz ýcýn head ý sureklý basta tutmamýz gerektýgý ýcýn head=temp oldu
			}
			else if (gezici->surname == gezici->prev->surname) {		//eger esýtlýk saglanýrsa 1 oncekýyle surnamemapde bulunulan nodun studentInfosuna ekleme yapýlýr.
				studentInfo *tempStudentInfo = new studentInfo;
				head->headOfStudentsInfo->next = tempStudentInfo;
				head->headOfStudentsInfo->next->name = gezici->name;
				head->headOfStudentsInfo->next->surname = gezici->surname;
				//headofstudentInfonun altýna gelecek emaýller buradan basladýgý ýcýn kontrollerý burada yapýyoruz//
				if (head->headOfStudentsInfo->name == head->headOfStudentsInfo->next->name)
				{
					head->headOfStudentsInfo->next->email = gezici->surname+gezici->name+ "@itu.edu.tr";
					if (head->headOfStudentsInfo->name == head->headOfStudentsInfo->prev->name)	//ayni isimli mail gelirse sayý eklenecek kýsým
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
		gezici = gezici->next;											//geziciyi artýrýyoruz ki dongu tum kayýtlar ýcýn donsun
	}
	controlCircular();														//last node's next pointing the head now 
}

void list::printList() {												//multilisti ekrana yazdýrmak için belirlediðim bir formatta fonksiyon
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
	//kayýtlarý karsýlastýrýp ekleme yapýyoruz bu sekýlde sort ýslemý ýcýn ayrý býr fonksýyona gerek kalmýyor
	if (strcmp(newnode->surname.c_str(), head->surname.c_str()) > 0){		//bastan ekleme
		newnode->next = head;
		head = newnode;
		newnode->headOfStudentsInfo = nw;
		head->headOfStudentsInfo->name = nw->name;
		head->headOfStudentsInfo->surname = nw->surname;
		head->headOfStudentsInfo->email = nw->email;
		return;
	}
	while (traverse && strcmp(traverse->surname.c_str(), newnode->surname.c_str()) >= 0){	//elimizdeki kayýt alfebetýk olarak buyuk oldukca
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
		tail = traverse;														//kaydý eklýycegýmýz yerý buluyoruz 
		traverse = traverse->next;
	}
	if (traverse){																//kaydý araya sokuyoruz
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
	else																		//araya gelmeyecekse sona eklýyoruz
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
		if (strcmp(srnm.c_str(), traverse->surname.c_str())==0)						//surname karsýlastýrmasý
		{	
			while (traverse->headOfStudentsInfo!=NULL)
			{
				if (strcmp(traverse->headOfStudentsInfo->email.c_str(), mail.c_str()) == 0)		//silecegýmýz yerý bulup  mailler tek oldugu ýcýn maýle gore sýlýyoruz
				{
					
					 traverse->headOfStudentsInfo->email="";										//bu sekýlde atama yaptýgýmýzda ekstra node ýslemý yapmadan sýlmýs oluyoruz
					 traverse->headOfStudentsInfo->name="";											//nodelarýn kaldýrýlmasýyla aslýnda ayný ýslem oluyor suan yapýlan
					 traverse->headOfStudentsInfo->surname="";
					
					 if(traverse->headOfStudentsInfo->prev){										//sýldýkten sonra head ýmýzý ýlgýlý yerýne alýyoruz
						traverse->headOfStudentsInfo = traverse->headOfStudentsInfo->prev;
					 }
					 return;
				}
				else
				{
					traverse->headOfStudentsInfo = traverse->headOfStudentsInfo->prev;				//eslesme olmazsa ayný maýllerde head ýlerletýyoruz
					return;
				}
			}
		}
		
			traverse = traverse->next;																//soyadlarý ýlerletýyoruz arama ýcýn
	}
}
void list::deleteSurnameNode(string srnm)
{
	surnameMap *traverse;
	traverse = head;
	while (traverse != NULL){

		if (strcmp(srnm.c_str(), traverse->surname.c_str()) == 0)								//sadece surname nodonu sýlmek ýcýn surname karsýlastýrmasý yeterlý
		{
			if (traverse->headOfStudentsInfo != NULL){
				while (traverse->headOfStudentsInfo != NULL){									//ýcerýsýnde ogrencý kaydý varsa onlarý sýlýyoruz
					deleteStudent(traverse->headOfStudentsInfo->email, traverse->headOfStudentsInfo->surname);
					traverse->headOfStudentsInfo=traverse->headOfStudentsInfo->prev;
				}
				traverse->surname = "";															//nodeumuzu siliyoruz
				return;
			}
			else
			{
				surnameMap *a;																//ogrencý kaydý yoksa o nodu sýlýyoruz
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
		if (strcmp(srnm.c_str(), traverse->surname.c_str()) == 0)					//surname karsýlastýrmasý
		{
			while (traverse->headOfStudentsInfo != NULL)
			{
				if (strcmp(traverse->headOfStudentsInfo->email.c_str(), email.c_str()) == 0)	//emaýl karsýlastýrmasý
				{
					string nm1, srnm1, email1;
					cout << "PLEASE ENTER NEW NAME:";											//yený gýrdýler alýnýyor
					cin >> nm1;
					cout << "PLEASE ENTER NEW SURNAME:";
					cin >> srnm1;
					cout << "PLEASE ENTER NEW EMAIL:";
					cin >> email1;
					traverse->headOfStudentsInfo->email = nm1;									//yený gýrdýler atanýyor
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
	ofstream dosya;																											//kayýtlarý dosyaya z-den a-ya olacak sekýlde 
	dosya.open("emailList.txt", ios::trunc);																				//her yazýsta sýfýrdan sýlýp yazýyoruz
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
