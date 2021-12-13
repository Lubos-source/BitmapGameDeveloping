#pragma once
#include "bitmapa.h"
class Pozadi
{
	CBitmapa m_Btm;

public:
	void LoadData(HDC dc);
	void Display(HDC dc);
	Pozadi(void);
	~Pozadi(void);
};

