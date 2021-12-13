#pragma once

#include "stdafx.h"
#include "drak.h"
#include "Pozadi.h"
#include "Mapa.h"
#include "Kolize.h"
#include "Score.h"
#include "Strela.h"
#include "Enemy.h"

#include "cfgfile.h"


class CScene
{
	//vytvorime nase hlavni objekty
	CDrak m_Drak;		// draka
	Pozadi m_pozadi;		//pozadi	
	Mapa m;
	Score score;
	Strela strela;
	int dalsiLVL = 0;
	int aktualni = 0;
		
	Enemy nepritel;

public:
	void Init(HDC hdc);
	void Render(HDC hdc);
	void UserInput(WPARAM wParam);
	void Move();
	void NacteniMapy(HDC hdc, char* mapa);
	
	void SetDalsilvl(int lvl);
	int GetDalsiLVL();
	void AktualniLVL();
	int GetAktualniLVL();

	Pozice Spawn;

	CScene(void);
	~CScene(void);

};
