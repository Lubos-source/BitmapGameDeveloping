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

class CDrak
{
	CBitmapa m_Btm; // bitmapa s animacemi (dlazdicemi)
	int m_Direction; // smer, kterym se drak pohybuje
	int m_AnimPhase; // cislo animacni faze - index faze(dlazdice) v bitmape 
	int m_AnimRow; // cislo radku v bitmape pro animacni fazi
	int m_MaxAnimPhase; // maximalni index animacni faze (dlazdice) v bitmape  
	DWORD m_TimeFrameInterval; // interval v ms kdy se bude menit animacni faze
	DWORD m_LastTime; // posledni cas, kdy se menila animacni faze

	//int m_X; // pozice draka na obrazovce
	//int m_Y;
	Pozice VelOkna;
	Pozice Zem;
	Pozice m_Pozice;
	Pozice BudouciPoz;
	Pozice m_Rychlost;
	
	
	const float gravitace = 1;
	float Vyska_Skoku = 30;
	int SirkaHrace;
	int VyskaHrace;
	float velikost = 1;
	int MinSmer = DRAK_NONE;
	bool Je_NaPodlaze;

	int Zivoty = 3;

public:
	void LoadData(HDC dc);
	void Display(HDC dc);
	void Move();
	void SetDirNone() { m_Direction = DRAK_NONE; m_AnimRow = 0; m_AnimPhase = 1; };
	void SetDirRight() { MinSmer = m_Direction = DRAK_RIGHT; m_AnimRow = 3; };
	void SetDirLeft() { MinSmer = m_Direction = DRAK_LEFT; m_AnimRow = 2; };
	void SetDirUp() { MinSmer = m_Direction = DRAK_UP; m_AnimRow = 4; };
	void SetDirDown() { MinSmer = m_Direction = DRAK_DOWN; m_AnimRow = 1; };
	int GetDir();
	int GetMinSmer();

	void Rychlost_Reset();

	Pozice GetPozice();
	Pozice GetBudouci();
	void SetBudouci(Pozice bud);

	void ZmenPozici(Pozice NovaPozice);
	
	Pozice GetRychlost();

	int GetSirka();
	int GetVyska();
	float GetVelikost();
	void SetZem(Pozice zem);

	int GetZivoty();
	void SetZivoty(int cislo);
	void ZivotyReset();

	CDrak(void);
	~CDrak(void);

};
