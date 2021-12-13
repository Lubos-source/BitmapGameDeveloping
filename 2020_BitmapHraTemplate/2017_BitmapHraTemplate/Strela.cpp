#include "stdafx.h"
#include "Strela.h"

Strela::Strela(void)
{
	m_AnimRow = 0;
	m_Pozice.x = -300;
	m_Pozice.y = -400;//-VYSKA_HRACE;
	velikost = 1;

	m_Rychlost.x = 0;
	m_Rychlost.y = 0;

	m_AnimPhase = 0;
	m_TimeFrameInterval = 120;
	m_MaxAnimPhase = 7;
	m_LastTime = GetTickCount();
}

Strela::~Strela(void)
{

}

void Strela::Move()
{
	//if ((GetTickCount() - m_LastTime) > m_TimeFrameInterval) { // zmenime animacni fazi jenom pokud uplyne vetsi cas od posledni zmenu nez je nastaveny
		m_AnimPhase++;
		m_LastTime = GetTickCount();
		if (m_AnimPhase > m_MaxAnimPhase) m_AnimPhase = 0; // pokud jsme na konci animacnich fazi, tak se vratme na zacatek
		// posuneme se podle smeru, ktery byl nastaven (kazdy snimek, lze pridat timeframeinterval pro zmenu jenom za urceny cas)
		if (Smer == DRAK_NONE )
		{
			StrelaSetPryc();
			//Stisk = false;
			strely.clear();
		}		
		if (Smer==DRAK_RIGHT )
		{
			m_Rychlost.x = 5.0f;
			m_Pozice.x = m_Pozice.x+20 + m_Rychlost.x;
			m_Pozice.y = m_Pozice.y+8;
	
		}
		if (Smer == DRAK_LEFT )
		{
			m_Rychlost.x = -5.0f;
			m_Pozice.x = m_Pozice.x-5 + m_Rychlost.x;
			m_Pozice.y = m_Pozice.y+8;
			
		}
		
		if (Smer == DRAK_DOWN ) {
			m_Rychlost.y = 5.0f;
			m_Pozice.y = m_Pozice.y + 25 + m_Rychlost.y;
			m_Pozice.x = m_Pozice.x+7;
			
		}
		if (Smer == DRAK_UP ) {

			m_Rychlost.y = -5.0f;
			m_Pozice.y = m_Pozice.y-15 + m_Rychlost.y;
			m_Pozice.x = m_Pozice.x+7;
			
		}
		
	//}
		m_Pozice = m_Pozice;
		strely.push_back(m_Pozice);

}
void Strela::Strel(Pozice Odkud, Pozice Rychlost,int MinSmer)
{
	Stisk = true;
	Smer = MinSmer;
	m_Pozice = Odkud;
	m_Rychlost = Rychlost;
	Move();
}
void Strela::StrelaSetPryc()
{
	m_Pozice.x = -200;
	m_Pozice.y = -200;
}
Pozice Strela::GetPozice()
{

	return m_Pozice;
}
float Strela::GetVelikost()
{
	return velikost;
}
void Strela::SetStisk(bool AN)
{
	Stisk = AN;
}
void Strela::LoadData(HDC dc)
{
	m_Btm.LoadBitmap("ZBRAN.bmp", dc);			//drak.bmp
	m_Btm.SetAnim(16,21);						//m_Btm.SetAnim(192,192);
}

void Strela::Display(HDC dc)
{
	m_Btm.DisplayTransparentAnimScale(dc, m_Pozice.x, m_Pozice.y, m_AnimPhase, m_AnimRow, velikost);
}
