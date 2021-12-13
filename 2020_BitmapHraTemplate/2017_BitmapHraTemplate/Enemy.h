#pragma once
#include "bitmapa.h"
#include "Pozice.h"

#include <vector>

using namespace std;

#define _LEFT 2
#define _RIGHT 1
#define _UP 3
#define _DOWN 0
#define _NONE -1

class Enemy
{
	CBitmapa m_Btm; // bitmapa s animacemi (dlazdicemi)
	int m_Direction; // smer, kterym se drak pohybuje
	int m_AnimPhase; // cislo animacni faze - index faze(dlazdice) v bitmape 
	int m_AnimRow; // cislo radku v bitmape pro animacni fazi
	int m_MaxAnimPhase; // maximalni index animacni faze (dlazdice) v bitmape  
	DWORD m_TimeFrameInterval; // interval v ms kdy se bude menit animacni faze
	DWORD m_LastTime; // posledni cas, kdy se menila animacni faze

	Pozice m_Pozice;
	Pozice m_Rychlost;
	float velikost = 1;

public:

	void LoadData(HDC dc);
	void Display(HDC dc);
	void Move();
	void SetDirNone() { m_Direction = _NONE; m_AnimRow = 0; m_AnimPhase = 1; };
	void SetDirRight() { m_Direction = _RIGHT; m_AnimRow = 3; };
	void SetDirLeft() { m_Direction = _LEFT; m_AnimRow = 2; };
	void SetDirUp() { m_Direction = _UP; m_AnimRow = 4; };
	void SetDirDown() { m_Direction = _DOWN; m_AnimRow = 1; };

	Pozice GetPozice();
	void ZmenPozici(Pozice NovaPozice);
	void ZmenSmer();

	Enemy(void);
	~Enemy(void);
};

