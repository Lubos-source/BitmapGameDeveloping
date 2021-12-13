#include "stdafx.h"
#include "Enemy.h"

#define SIRKA_E 32
#define VYSKA_E 32
#define VelOknax 1024
#define VelOknay 768

void Enemy::LoadData(HDC dc)
{
	m_Btm.LoadBitmap("Enemy.bmp", dc);			//drak.bmp
	m_Btm.SetAnim(SIRKA_E, VYSKA_E);						
}

void Enemy::Display(HDC dc)
{
	m_Btm.DisplayTransparentAnimScale(dc, m_Pozice.x, m_Pozice.y, m_AnimPhase, m_AnimRow, velikost);
}

void Enemy::Move()
{
	if ((GetTickCount() - m_LastTime) > m_TimeFrameInterval) { 
		m_AnimPhase++;
		m_LastTime = GetTickCount();
		if (m_AnimPhase > m_MaxAnimPhase) m_AnimPhase = 0; 
		if (m_Direction == _RIGHT)
		{			
			m_Rychlost.x = 5.0f;
			m_Rychlost.y = 0;			
		}
		if (m_Direction == _LEFT)
		{			
			m_Rychlost.x = -5.0f;
			m_Rychlost.y = 0;			
		}
		if (m_Direction == _NONE) {  m_Rychlost.x = 0; m_Rychlost.y = 0; }
		
		if (m_Direction == _DOWN) {
			
			m_Rychlost.y = 5.0f;
			m_Rychlost.x = 0;
		}
		if (m_Direction == _UP) {
	
			m_Rychlost.y = -5.0f;
			m_Rychlost.x = 0;
		}


		m_Pozice = m_Pozice + m_Rychlost;

		if (m_Pozice.y < 0)
		{
			m_Pozice.y = 0;
			ZmenSmer();
		}
		if (m_Pozice.x < 0) 
		{
			m_Pozice.x = 0;
			ZmenSmer();
		}
		if ((m_Pozice.x + 32 * velikost) > VelOknax)
		{
			m_Pozice.x = VelOknax - 32 * velikost;
			ZmenSmer();
		}
		if ((m_Pozice.y + 32 * velikost) > VelOknay) 
		{ 
			m_Pozice.y = VelOknay - 32 * velikost; 
			ZmenSmer();
		}

	}

}

Pozice Enemy::GetPozice()
{
		Pozice pom;
		pom.x = m_Pozice.x;
		pom.y = m_Pozice.y;

		return pom;
}

void Enemy::ZmenPozici(Pozice NovaPozice)
{
	m_Pozice.x = NovaPozice.x;
	m_Pozice.y = NovaPozice.y;
}

void Enemy::ZmenSmer()
{
	if (m_Direction == _LEFT) SetDirRight();
	else if (m_Direction == _RIGHT) SetDirLeft();
	//else if (m_Direction == _UP) SetDirDown();
	//else if (m_Direction == _DOWN) SetDirLeft();

	//void SetDirRight() { m_Direction = _RIGHT; m_AnimRow = 3; };
	//void SetDirLeft() { m_Direction = _LEFT; m_AnimRow = 2; };
	//void SetDirUp() { m_Direction = _UP; m_AnimRow = 4; };
	//void SetDirDown() { m_Direction = _DOWN; m_AnimRow = 1; };
	
}

Enemy::Enemy(void)
{
	SetDirLeft();
	//m_Direction = _DOWN;
	//m_AnimRow = 0;
	m_Pozice.x = 00;					//1) 400 2) 3) 
	m_Pozice.y = 00;//-VYSKA_HRACE;	//1) 200 2) 3) 
	velikost = 1;

	m_Rychlost.x = 0;
	m_Rychlost.y = 0;

	m_AnimPhase = 0;
	m_TimeFrameInterval = 120;
	m_MaxAnimPhase = 2;
	m_LastTime = GetTickCount();
}

Enemy::~Enemy(void)
{

}
