#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <vector>

#include "Simulationsobjekt.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "PKW.h"

using namespace std;

//Funktionsdeklarationen (keine Definitionen!):
void vAufgabe_1();
void vAufgabe_1a();
void vAufgabe_2();
void vAufgabe_3();
void vTestBisAufgabe7332();
void vAufgabe_4();
void vAufgabe_5();


//globale Uhr
double dGlobaleZeit = 0.0;

//Rundungstoleranz bei double-Vergleichen: Wähle hinreichend kleines Epsilon
double dToleranz = 0.001;

int main()
{

	vAufgabe_5();
	
	return 0;
}
void vAufgabe_4()
{
	auto weg = make_unique<Weg>("WEG1", 356.9);

	Weg::vKopf();
	cout << *weg << std::endl;

}

void vAufgabe_5()
{
	auto weg = std::make_unique<Weg>("WEG1", 30);
	weg->vAnnahme(std::make_unique<Fahrrad>("RAD1", 15));
	weg->vAnnahme(std::make_unique<Fahrrad>("RAD2", 25), 2.0);
	weg->vAnnahme(std::make_unique<PKW>("PKW1", 100, 5, 60));

	Weg::vKopf();
	while (dGlobaleZeit < 4.0) {
		dGlobaleZeit += 0.5;

		weg->vSimulieren();

		std::cout << *weg << std::endl;
	}
}


//Funktionsdefinitionen:
/*
void vAufgabe_1()
{
	//statische Elemente
	Fahrzeug StatischesFahrzeug1;
	Fahrzeug StatischesFahrzeug2("StatischesFahrzeug2");

	//dynamische Elemente
	Fahrzeug* DynamischesFahrzeug1 = new Fahrzeug;
	Fahrzeug* DynamischesFahrzeug2 = new Fahrzeug("DynamischesFahrzeug1");

	delete DynamischesFahrzeug1;
	delete DynamischesFahrzeug2;

	//zwei unique_ptr erstellen
	unique_ptr<Fahrzeug> ersterSmartUniquePtr = make_unique<Fahrzeug>("ersterSmartUniquePtr", 30.873);
	unique_ptr<Fahrzeug> zweiterSmartUniquePtr = make_unique<Fahrzeug>("zweiterSmartUniquePtr", 100.2);

	//zwei shared_ptr erstellen
	shared_ptr<Fahrzeug> ersterSmartSharedPtr = make_shared<Fahrzeug>("ersterSmartSharedPtr", 420);
	shared_ptr<Fahrzeug> zweiterSmartSharedPtr = make_shared<Fahrzeug>("zweiterSmartSharedPtr");

	//ein shared_ptr in einem weiteren shared_ptr speichern und Anzahl Referenzen ausgeben:
	cout << ersterSmartSharedPtr.use_count() << endl;
	shared_ptr<Fahrzeug> speichereKopieSharedPtr = ersterSmartSharedPtr;
	cout << ersterSmartSharedPtr.use_count() << endl;
	cout << speichereKopieSharedPtr.use_count() << endl;

	//ein shared_ptr in einem weiteren unique_ptr speichern und Anzahl Referenzen ausgeben:
	//cout << ersterSmartSharedPtr.use_count() << endl;

	//++++++++++++++++++Fehler - unique_ptr hat eindeutigen Besitz:+++++++++++++++++++++++++++++++
	//unique_ptr<Fahrzeug> speichereKopieSharedPtr = ersterSmartSharedPtr; 
	//cout << ersterSmartSharedPtr.use_count() << endl;
	//cout << speichereKopieSharedPtr.use_count() << endl;


	//erstelle Vector, in dem unique_ptr, die auf Objekte der Klasse Fahrzeug zeigen, gespeichert werden
	vector<unique_ptr<Fahrzeug>> uniqueFahrzeugVector(3);

	//fahrzeugVector[0] = ersterSmartUniquePtr;	//Fehler: unique_ptr nicht kopierbar

	uniqueFahrzeugVector[0] = move(ersterSmartUniquePtr);					//Besitzwechsel mit move-Funktion; ersterSmartUniquePtr wird nullptr
	uniqueFahrzeugVector[1] = move(zweiterSmartUniquePtr);					//Besitzwechsel mit move-Funktion; zweiterSmartUniquePtr wird nullptr
	//uniqueFahrzeugVector[2] = ersterSmartSharedPtr;							//Fehler: shared_ptr nicht als unique<ptr> speicherbar
	//uniqueFahrzeugVector[3] = make_unique<Fahrzeug>(*ersterSmartSharedPtr);	//Fehler: shared_ptr nicht als unique<ptr> speicherbar

	//Hier wird 2 mal der Destruktor aufgerufen - mit dem Löschen der unique-Pointer in der Liste werden automatisch auch die Objekte gelöscht
	uniqueFahrzeugVector.clear();


	//erstelle Vector, in dem shared_ptr, die auf Objekte der Klasse Fahrzeug zeigen, gespeichert werden
	vector<shared_ptr<Fahrzeug>> sharedFahrzeugVector(5);
	unique_ptr<Fahrzeug> dritterSmartUniquePtr = make_unique<Fahrzeug>("dritterSmartUniquePtr", 30.873);

	//Auch einstige unique-ptr können in der shared-ptr vector gespeichert werden, wird also automatisch gecastet
	sharedFahrzeugVector[0] = move(dritterSmartUniquePtr);

	//Füge shared-Fahrzeug ohne move hinzu:
	shared_ptr<Fahrzeug> dritterSmartSharedPtr = make_shared<Fahrzeug>("dritterSmartSharedPtr");
	sharedFahrzeugVector[1] = dritterSmartSharedPtr;
	cout << dritterSmartSharedPtr.use_count() << endl;//ausgabe: 2, da dritterSmartSharedPtr und sharedFahrzeugVector[1] auf das selbe Objekt zeigen

	//Füge unique-Fahrzeug mit move hinzu:
	shared_ptr<Fahrzeug> vierterSmartSharedPtr = make_shared<Fahrzeug>("vierterSmartSharedPtr");
	sharedFahrzeugVector[2] = move(vierterSmartSharedPtr);
	cout << vierterSmartSharedPtr.use_count() << endl;		//Ausgabe: 0, da zweiterSmartSharedPtr durch move nicht mehr zugreifbar
	cout << sharedFahrzeugVector[2].use_count() << endl;	//Ausgabe: 1, da


	cout << "Ende der Funktion vAufgabe_1" << endl;
}//Hier wird der Destruktor für die zwei statischen Objekte und für jene, auf die die restlichen Smartpointer zeigen, aufgerufen

void vAufgabe_1a()
{
	string sFahrzeug1Name;
	string sFahrzeug2Name;
	string sFahrzeug3Name;

	double dFahrzeug1Geschwindigkeit = 0;
	double dFahrzeug2Geschwindigkeit = 0;
	double dFahrzeug3Geschwindigkeit = 0;

	//Lese Fahrzeugnamen und -Geschwindigkeiten ein:
	cout << "Hallo! Geben Sie im folgenden die geforderten Daten ein:" << endl;
	cout << "Name von Fahrzeug 1:" << endl;
	cin >> sFahrzeug1Name;
	cout << "Geschwindigkeit von Fahrzeug 1:" << endl;
	cin >> dFahrzeug1Geschwindigkeit;

	cout << "Name von Fahrzeug 2:" << endl;
	cin >> sFahrzeug2Name;
	cout << "Geschwindigkeit von Fahrzeug 2:" << endl;
	cin >> dFahrzeug2Geschwindigkeit;

	cout << "Name von Fahrzeug 3:" << endl;
	cin >> sFahrzeug3Name;
	cout << "Geschwindigkeit von Fahrzeug 3:" << endl;
	cin >> dFahrzeug3Geschwindigkeit;

	//speichere 3 Fahrzeuge in vector
	vector<unique_ptr<Fahrzeug>> fahrzeugVector(3);

	fahrzeugVector[0] = make_unique<Fahrzeug>(sFahrzeug1Name, dFahrzeug1Geschwindigkeit);
	fahrzeugVector[1] = make_unique<Fahrzeug>(sFahrzeug2Name, dFahrzeug2Geschwindigkeit);
	fahrzeugVector[2] = make_unique<Fahrzeug>(sFahrzeug3Name, dFahrzeug3Geschwindigkeit);

	//Simulationsschleife
	double dMaxSimulationsZeit = 10.0;
	double step = (1.0 / 4);
	for (dGlobaleZeit = 0.0; dGlobaleZeit <= (dMaxSimulationsZeit + dToleranz); dGlobaleZeit = dGlobaleZeit + step)
	{
		cout << "GlobaleZeit: " << dGlobaleZeit << " Stunden " << endl;
		Fahrzeug::vKopf();
		for (vector<unique_ptr<Fahrzeug>>::iterator it = fahrzeugVector.begin(); it != fahrzeugVector.end(); it++)
		{
			cout << endl;
			(*it)->vSimulieren();
			(*it)->vAusgeben(cout);
		}
		cout << "\n" << endl;
	}

	fahrzeugVector.clear();
}

void vAufgabe_2()
{
	int iAnzahl = 0;
	vector<unique_ptr<Fahrzeug>> fahrzeugvector;
	cout << "Geben Sie die Anzahl der zu erzeugenden PKW ein: " << endl;
	cin >> iAnzahl;

	for (int i = 0; i < iAnzahl; i++)
	{
		fahrzeugvector.push_back(move(make_unique<PKW>("PKW" + to_string(i + 1), 200.0, 8.0)));
	}

	cout << "Geben Sie die Anzahl der zu erzeugenden Fahrraeder ein: " << endl;
	cin >> iAnzahl;

	for (int i = 0; i < iAnzahl; i++)
	{
		fahrzeugvector.push_back(move(make_unique<Fahrrad>("Fahrrad" + to_string(i + 1), 20.0)));
	}

	//	vector<unique_ptr<Fahrzeug>> fahrzeugVector(7);

	   //fahrzeugVector[0] = make_unique<Fahrrad>("Fahrrad1", 12.00);
	   //fahrzeugVector[1] = make_unique<Fahrrad>("Fahrrad2", 26.54);
	   //fahrzeugVector[2] = make_unique<Fahrrad>("Fahrrad3", 30.00);
	   //fahrzeugVector[3] = make_unique<PKW>("PKW1", 100.00, 100.0);
	   //fahrzeugVector[4] = make_unique<PKW>("PKW2", 50.00, 5.0, 100);
	   //fahrzeugVector[5] = make_unique<PKW>("Aventador", 200.00, 13.25);
	   //fahrzeugVector[6] = make_unique<PKW>("PKW4", 111.11, 3.0);

	   //Simulationsschleife
	double dMaxSimulationsZeit = 4.0;
	double step = (0.4);
	bool bGetankt = false;
	for (dGlobaleZeit = 0.0; dGlobaleZeit <= (dMaxSimulationsZeit + dToleranz); dGlobaleZeit = dGlobaleZeit + step)
	{
		cout << "GlobaleZeit: " << dGlobaleZeit << " Stunden " << endl;
		Fahrzeug::vKopf();
		if ((dGlobaleZeit >= 3.0 - dToleranz) && (bGetankt == false))
		{
			for (vector<unique_ptr<Fahrzeug>>::iterator it = fahrzeugvector.begin(); it != fahrzeugvector.end(); it++)
			{
				(*it)->dTanken();//default-Wert: volltanken
			}
			bGetankt = true;
		}
		for (vector<unique_ptr<Fahrzeug>>::iterator it = fahrzeugvector.begin(); it != fahrzeugvector.end(); it++)
		{
			cout << endl;
			(*it)->vSimulieren();
			(*it)->vAusgeben(cout);
		}
		cout << "\n" << endl;
	}

	fahrzeugvector.clear();
}

void vAufgabe_3()
{
*/

	/********************Prüfe Überladung <<-Operator*************************************/
/*
	Fahrrad aFahrrad1("Fahrrad1", 30.00);
	PKW aPKW1("PKW1", 100.00, 5.0);

	cout << aPKW1 << endl;
	cout << aFahrrad1 << endl;

	vector<unique_ptr<Fahrzeug>> fahrzeugVector1(2);
	fahrzeugVector1[0] = make_unique<Fahrrad>("Fahrrad2", 12.00);
	fahrzeugVector1[1] = make_unique<PKW>("PKW2", 26.54, 5.0);

	cout << *(fahrzeugVector1[0]) << endl;
	cout << *(fahrzeugVector1[1]) << endl;

	fahrzeugVector1.clear();

	*/
	/***************************Teste die Überladung des <-Operators******************************/
/*
	vector<unique_ptr<Fahrzeug>> fahrzeugVector2(7);
	fahrzeugVector2[0] = make_unique<Fahrrad>("Fahrrad1", 12.00);
	fahrzeugVector2[1] = make_unique<Fahrrad>("Fahrrad2", 26.54);
	fahrzeugVector2[2] = make_unique<Fahrrad>("Fahrrad3", 30.00);
	fahrzeugVector2[3] = make_unique<PKW>("PKW1", 100.00, 100.0);
	fahrzeugVector2[4] = make_unique<PKW>("PKW2", 50.00, 5.0, 100);
	fahrzeugVector2[5] = make_unique<PKW>("Aventador", 200.00, 13.25);
	fahrzeugVector2[6] = make_unique<PKW>("PKW4", 111.11, 3.0);

	double dMaxSimulationsZeit = 4.0;
	double step = (1.0 / 4);
	for (dGlobaleZeit = 0.0; dGlobaleZeit <= (dMaxSimulationsZeit + dToleranz); dGlobaleZeit = dGlobaleZeit + step)
	{
		cout << "GlobaleZeit: " << dGlobaleZeit << " Stunden " << endl;
		Fahrzeug::vKopf();
		if (dGlobaleZeit >= 3.0 && dGlobaleZeit <= 3.1)
		{
			bool bWahrheit = fahrzeugVector2[4] < fahrzeugVector2[6];
			if (bWahrheit == true)
			{
				cout << "\n" << "<-Operator Ueberladung funktioniert :)" << endl;
			}
			else
			{
				cout << "\n" << "<-Operator Ueberladung funktioniert (noch) nicht :(" << endl;
			}
		}
		for (vector<unique_ptr<Fahrzeug>>::iterator it = fahrzeugVector2.begin(); it != fahrzeugVector2.end(); it++)
		{
			cout << endl;
			(*it)->vSimulieren();
			(*it)->vAusgeben(cout);
		}
		cout << "\n" << endl;
	}

	//fahrzeugVector2.clear();


	/********************Teste = Operatorüberladung*************************************/
/*

	Fahrzeug vorletztesFahrzeug("vorletztesFahrzeug", 50.0);
	Fahrzeug letztesFahrzeug("letztesFahrzeug", 40.0);
	letztesFahrzeug = vorletztesFahrzeug;

	cout << letztesFahrzeug << endl;

	Fahrrad vorletztesFahrrad("vorletztesFahrrad", 30.0);
	Fahrrad letztesFahrrad("letztesFahrrad", 60.0);
	letztesFahrrad = vorletztesFahrrad;

	cout << letztesFahrrad << endl;

	PKW vorletzterPKW("vorletzterPKW", 100.0, 5.0);
	PKW letzterPKW("letzterPKW", 200.0, 10.0);
	letzterPKW = vorletzterPKW;

	cout << letzterPKW << endl;

	/*Die folgenden vier Zeilen verdeutlichen das byteweise Kopieren eines Objekts, copyFahrzeug und letztesFahrzeug hätten dieselbe ID*/

	//Fahrzeug copyFahrzeug1(letztesFahrzeug);
	//cout << copyFahrzeug1 << endl;

	////oder

	//Fahrzeug copyFahrzeug2 = letztesFahrzeug;
	//cout << copyFahrzeug2 << endl;

	/*********************************Bemerkung zu CopyConstruktor und =-Operator***************************************************/
	//Beim =-Operator wird KEIN Konstruktor aufgerufen. Die Zuweisung von Variablen wird im Rumpf der Operator-Überladung selbst implementiert.
	//Da die ID als const definiert wurde, wie in der Aufgabenstellung geraten, kann diese bei der manuellen Überladung nicht mehr geändert
	//werden. ABER: Das muss sie auch nicht, denn das Fahrzeugobjekt, in welches die Daten eines anderen Objektes kopiert werden sollen, 
	// wurde ja bereits vorher erstellt, hat daher eine ID und dise wird einfach beibehalten. Beim standardmäßigen CopyConstruktor würde eine NEUES Objekt erstellt
	//, indem byteweise kopiert würde, weshalb in diesem Fall zwei Objekte dieselbe ID hätten.
	//
	//Für die Klasse Fahrrad wird der =-Operator nicht mehr überladen, da diese Klasse keine zusätzlichen Attribute hat.
	//
	//Es ergibt Sinn, den Copyconstruktor zu verbieten, da dann nicht aus Versehen zwei Objekte mit gleicher ID erstellt werden können
/*
}*/

//void vTestBisAufgabe7332()
//{
//	//speichere 3 Fahrzeuge in vector
//	vector<unique_ptr<Fahrzeug>> fahrzeugVector(3);
//
//	fahrzeugVector[0] = make_unique<Fahrrad>("Fahrzeug1", 30.00);
//	fahrzeugVector[1] = make_unique<PKW>("Fahrzeug2", 100.00, 100.0);
//	fahrzeugVector[2] = make_unique<PKW>("Fahrzeug3", 50.00, 5.0);
//
//	//Simulationsschleife
//	double dMaxSimulationsZeit = 1.0;
//	double step = (1.0 / 4);
//	fahrzeugVector[0]->vKopf();
// 	for (dGlobaleZeit = 0.0; dGlobaleZeit <= (dMaxSimulationsZeit + dToleranz); dGlobaleZeit = dGlobaleZeit + step)
//	{
//		for (vector<unique_ptr<Fahrzeug>>::iterator it = fahrzeugVector.begin(); it != fahrzeugVector.end(); it++)
//		{
//			cout << endl;
//			(*it)->vSimulieren();
//			(*it)->vAusgeben();
//		}
//		cout << "\n" << endl;
//		fahrzeugVector[1]->dTanken(25);
//	}
//
//	fahrzeugVector.clear();
//}