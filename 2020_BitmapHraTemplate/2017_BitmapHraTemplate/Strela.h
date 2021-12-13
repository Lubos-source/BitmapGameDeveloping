#pragma once
#include "bitmapa.h"
#include "Pozice.h"
#include <vector>
using namespace std;

#define DRAK_LEFT 2
#define DRAK_RIGHT 1
#define DRAK_UP 3
#define DRAK_DOWN 0
#define DRAK_NONE -1


class Strela
{
protected:
	CBitmapa m_Btm;
	int m_AnimPhase; // cislo animacni faze - index faze(dlazdice) v bitmape 
	int m_AnimRow; // cislo radku v bitmape pro animacni fazi
	int m_MaxAnimPhase; // maximalni index animacni faze (dlazdice) v bitmape  
	DWORD m_TimeFrameInterval; // interval v ms kdy se bude menit animacni faze
	DWORD m_LastTime; // posledni cas, kdy se menila animacni faze

	Pozice m_Rychlost;
	Pozice m_Pozice;
	float velikost = 1;
	int Smer = DRAK_NONE;
	bool Stisk = false;
	vector <Pozice> strely;

public:
	Strela(void);
	~Strela(void);
	void Move();
	void Strel(Pozice Odkud, Pozice Rychlost,int MinSmer);
	void StrelaSetPryc();

	Pozice GetPozice();
	float GetVelikost();

	void SetStisk(bool AN);
	void LoadData(HDC dc);
	void Display(HDC dc);

};

