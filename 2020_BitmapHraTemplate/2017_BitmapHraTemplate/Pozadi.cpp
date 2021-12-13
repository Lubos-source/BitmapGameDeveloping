#include "stdafx.h"
#include "Pozadi.h"

void Pozadi::LoadData(HDC dc)
{
	m_Btm.LoadBitmap("pozadi.bmp", dc);
	
	//m_Btm.SetAnim(1024, 768);						//m_Btm.SetAnim(192,192);
}

void Pozadi::Display(HDC dc)
{
	m_Btm.Display(dc, 0, 0);
}

Pozadi::Pozadi(void)
{
}

Pozadi::~Pozadi(void)
{
}
