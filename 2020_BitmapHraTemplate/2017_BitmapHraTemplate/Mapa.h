#pragma once
#include "bitmapa.h"
#include "Pozice.h"
#include <vector>

using namespace std;

class Mapa
{
	CBitmapa m_Btm;
public:
	//struct Dlazdice
	//{
		char Cesta_Soubor[255];
		char Cesta_level[255];
		int Sirka_obr;
		int Vyska_obr;
		char Jmeno_Dlazdice[255];
		int Sirka_Dlazdice;
		int Vyska_Dlazdice;
		int Pocet_Dlazdic;
		float Pocet_Radku;
		float Pocet_Sloupcu;
	//};
		struct Dlazdice
		{
			int radek;
			int sloupec;
		};

		int mapa[24][32];

	vector <Dlazdice> UlozDlazdice;

	vector <Pozice> DlazdiceKolize;
	vector <Pozice> Smrt;			//souradnice kde nastane smrt
	vector <Pozice> Body;			//souradnice minci (bodu)
	vector <Pozice> KrabZel;		//souradnice, kde je krabice na trave
	vector <Pozice> KrabDlaz;		//souradnice, kde je krabice na dlazdici
	vector <Pozice> DvereTrava;		//souradnice, kde je vchod na trave
	vector <Pozice> DvereDlazdice;	//souradnice, kde je vchod na dlazdici

public:
	void LoadData(HDC dc, char* x);
	void Display(HDC dc);		//, int pozX, int pozY, char* x

	void NactiKolizi();
	int indx = 0;
	//vector <Pozice> VratKoliziDL();

	Mapa(void);
	~Mapa(void);
};

