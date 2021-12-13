#include "StdAfx.h"
#include "Drak.h"



#define SIRKA_HRACE 32
#define VYSKA_HRACE 32


int CDrak::GetDir()
{
	return m_Direction;
}

int CDrak::GetMinSmer()
{
	return MinSmer;
}

void CDrak::Rychlost_Reset()
{
	m_Rychlost.x = 0;
	m_Rychlost.y = 0;
}


Pozice CDrak::GetPozice()
{
	Pozice pom;
	pom.x = m_Pozice.x;
	pom.y = m_Pozice.y;

	return pom;
}

Pozice CDrak::GetBudouci()
{
	return BudouciPoz;
}

void CDrak::SetBudouci(Pozice bud)
{
	Pozice pom;
	pom.x = m_Pozice.x + m_Rychlost.x + bud.x;
	pom.y = m_Pozice.y + m_Rychlost.y + bud.y;

	BudouciPoz = pom;
}

void CDrak::ZmenPozici(Pozice NovaPozice)
{
	m_Pozice.x = NovaPozice.x;
	m_Pozice.y = NovaPozice.y;

	//m_Pozice = NovaPozice;
}

Pozice CDrak::GetRychlost()
{
	Pozice pom;
	pom = m_Rychlost;

	return pom;
}

int CDrak::GetSirka()
{
	SirkaHrace = SIRKA_HRACE;
	return SirkaHrace;
}

int CDrak::GetVyska()
{
	VyskaHrace = VYSKA_HRACE;
	return VyskaHrace;
}

float CDrak::GetVelikost()
{
	return velikost;
}

void CDrak::SetZem(Pozice zem)
{
	Zem.y = zem.y;
	Zem.x = zem.x;
}

int CDrak::GetZivoty()
{
	return Zivoty;
}

void CDrak::SetZivoty(int cislo)
{
	Zivoty = Zivoty + cislo;
}

void CDrak::ZivotyReset()
{
	Zivoty = 3;
	PlaySound("soundeffects\\reset.wav", NULL, SND_ASYNC);
}

CDrak::CDrak(void)
{
	SirkaHrace = SIRKA_HRACE;
	VyskaHrace = VYSKA_HRACE;
	m_Direction=-1;
	m_AnimRow=0;
	m_Pozice.x = 300;
	m_Pozice.y = 400;//-VYSKA_HRACE;
	velikost = 1;

	m_Rychlost.x = 0;
	m_Rychlost.y = 0;
	Je_NaPodlaze = false;

	m_AnimPhase=0;
	m_TimeFrameInterval=120;
	m_MaxAnimPhase=2;
	m_LastTime=GetTickCount();
	VelOkna.x = 1024;
	VelOkna.y = 768;
	Zem.y = VelOkna.y;

	Zivoty = 3;
}

CDrak::~CDrak(void)
{
}



void CDrak::LoadData(HDC dc) {
	m_Btm.LoadBitmap("HLpostavaUpravena.bmp",dc);			//drak.bmp
	m_Btm.SetAnim(SIRKA_HRACE,VYSKA_HRACE);						//m_Btm.SetAnim(192,192);
}

void CDrak::Display(HDC dc) {
	m_Btm.DisplayTransparentAnimScale(dc, m_Pozice.x, m_Pozice.y,m_AnimPhase,m_AnimRow,velikost);

	/// ZOBRAZENI ZIVOTU ///
	char zivoty[30];
	itoa(GetZivoty(), zivoty, 10);

	TextOut(dc, 0, 40, TEXT("ZIVOTY:"), (7));
	TextOut(dc, 52, 40, TEXT(zivoty), strlen(zivoty));
}

void CDrak::Move() {
		
	if ((GetTickCount()-m_LastTime)>m_TimeFrameInterval) { // zmenime animacni fazi jenom pokud uplyne vetsi cas od posledni zmenu nez je nastaveny
		m_AnimPhase++;
		m_LastTime=GetTickCount();
		if (m_AnimPhase>m_MaxAnimPhase) m_AnimPhase=0; // pokud jsme na konci animacnich fazi, tak se vratme na zacatek
		// posuneme se podle smeru, ktery byl nastaven (kazdy snimek, lze pridat timeframeinterval pro zmenu jenom za urceny cas)
		if (m_Direction == DRAK_RIGHT) 
		{
			//MinSmer = DRAK_RIGHT;
			m_Rychlost.x += 5.0f;
			
			//m_Pozice.x = m_Pozice.x + m_Rychlost.x; if (m_Pozice.x < 0)m_Pozice.x = 0; if ((m_Pozice.x + SIRKA_HRACE*velikost) > VelOkna.x) m_Pozice.x = (VelOkna.x - SIRKA_HRACE*velikost); }
		}
		if (m_Direction == DRAK_LEFT)
		{
			//MinSmer = DRAK_LEFT;
			m_Rychlost.x += -5.0f;
			
			//m_Pozice.x = m_Pozice.x - m_Rychlost.x; if (m_Pozice.x < 0)m_Pozice.x = 0; if ((m_Pozice.x + SIRKA_HRACE*velikost) > VelOkna.x) m_Pozice.x = (VelOkna.x - SIRKA_HRACE*velikost); }
		}
		if (m_Direction == DRAK_NONE) { /*MinSmer = DRAK_NONE;*/ m_Rychlost.x = 0; m_Rychlost.y = 0; }
		//if (m_Direction == DRAK_DOWN) m_Y += 10;
		if (m_Direction == DRAK_DOWN)  {
			//MinSmer = DRAK_DOWN;
			m_Rychlost.y += 5.0f;
		}
		if (m_Direction == DRAK_UP) {
			//MinSmer = DRAK_UP;
			m_Rychlost.y += -5.0f;				
		}				
		
		 m_Rychlost.x *= 0.9;	//"klouzani se" aby sebou necuknul na miste
		 m_Rychlost.y *= 0.9;

		 if (m_Rychlost.x > 15.0f)
			 m_Rychlost.x = 15.0f;
		 if (m_Rychlost.x < -15.0f)
			 m_Rychlost.x = -15.0f;
		 if (m_Rychlost.y > 15.0f)
			 m_Rychlost.y = 15.0f;
		 if (m_Rychlost.y < -15.0f)
			 m_Rychlost.y = -15.0f;

		BudouciPoz.x = m_Pozice.x + m_Rychlost.x;
		BudouciPoz.y = m_Pozice.y + m_Rychlost.y;
		
		m_Pozice = BudouciPoz;
		m_Pozice = GetBudouci();

		// KONTROLA Pozice Hrace a OKNA
		if (m_Pozice.y < 0)m_Pozice.y = 0;	//nahoru
		if (m_Pozice.x < 0)m_Pozice.x = 0;	//doleva
		if ((m_Pozice.x + SIRKA_HRACE * velikost) > VelOkna.x) m_Pozice.x = VelOkna.x - SIRKA_HRACE * velikost;	//doprava
		if ((m_Pozice.y + VYSKA_HRACE * velikost) > VelOkna.y) { m_Pozice.y = VelOkna.y - VYSKA_HRACE * velikost; }	//dolu
	}
		
}