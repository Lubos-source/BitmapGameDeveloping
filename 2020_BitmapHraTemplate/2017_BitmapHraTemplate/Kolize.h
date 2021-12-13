#pragma once
//#include "Drak.h"
//#include "Mapa.h"
#include "Pozice.h"
#include <vector>
using namespace std;

class Kolize
{
	Pozice BudouciPoz;
	//CDrak hrac;
//	Mapa Kol;
	vector <Pozice> D;
public:
	bool Colision(Pozice hrac, float velikost, vector <Pozice> KolizeMapy);
	int ColPenize(Pozice hrac, float velikost, vector <Pozice> KolizeMapy);
	bool ColisSeZem(Pozice hrac, float velikost, vector <Pozice> KolizeMapy);
	int Bedna(Pozice mec, float velikost, vector<Pozice> KolizeMapy);
	//int KolizeJE(Pozice Budouci, Pozice AktPozice, Pozice Rychlost, vector <Pozice> mapaKol);
	//Pozice KontrolaKolize(Pozice Budouci, Pozice AktPozice, Pozice Rychlost, vector <Pozice> mapaKol);
};

