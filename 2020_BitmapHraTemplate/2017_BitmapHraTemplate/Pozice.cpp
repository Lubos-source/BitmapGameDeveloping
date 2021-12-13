#include "stdafx.h"
#include "Pozice.h"

Pozice::Pozice(void)
{
	x = 0;
	y = 0;
}

Pozice::~Pozice(void)
{
}


Pozice Pozice::DruhaSourad(int sirka, int vyska, float velikost)
{		
	Pozice pom;

	pom.x = (x + sirka) * velikost;
	pom.y = (y + vyska) * velikost;

	return pom;
}

Pozice Pozice::operator*(float cislo)
{
	Pozice pom;
	
	pom.x = x * cislo;
	pom.y = y * cislo;
	return pom;
}

const Pozice Pozice::operator+(const Pozice poz2)
{
	Pozice vysledek;
	vysledek.x = x + poz2.x;
	vysledek.y = y + poz2.y;

	return vysledek;
}

const Pozice Pozice::operator-(const Pozice poz2)
{
	Pozice vysledek;
	vysledek.x = x - poz2.x;
	vysledek.y = y - poz2.y;

	return vysledek;
}

