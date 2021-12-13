#include "stdafx.h"
#include "Kolize.h"

#define SIRKA_HRACE 32
#define VYSKA_HRACE 32

bool Kolize::Colision(Pozice hrac,float velikost, vector<Pozice> KolizeMapy)
{
	D = KolizeMapy;

	for (int i = 0; i < D.size(); i++)
	{
		if (
			hrac.x + SIRKA_HRACE * velikost >= KolizeMapy[i].x &&	//1 podminka
			KolizeMapy[i].x + 28 >= hrac.x &&						//2 p.
			hrac.y + VYSKA_HRACE * velikost >= KolizeMapy[i].y &&	//3 p.
			KolizeMapy[i].y + 28 >= hrac.y							//4 p.
			)
			return true;
	}
	return false;
}

int Kolize::ColPenize(Pozice hrac, float velikost, vector<Pozice> KolizeMapy)
{
		D = KolizeMapy;

		for (int i = 0; i < D.size(); i++)
		{
			if (
				hrac.x + SIRKA_HRACE * velikost >= KolizeMapy[i].x &&	//1 podminka
				KolizeMapy[i].x + 10 >= hrac.x &&						//2 p.
				hrac.y + VYSKA_HRACE * velikost >= KolizeMapy[i].y &&	//3 p.
				KolizeMapy[i].y + 10 >= hrac.y							//4 p.
				)
				return i;
		}
		return (-2);	
}

bool Kolize::ColisSeZem(Pozice hrac, float velikost, vector<Pozice> KolizeMapy)
{
	D = KolizeMapy;

	for (int i = 0; i < D.size(); i++)
	{
		if (				
			hrac.y+VYSKA_HRACE*velikost>KolizeMapy[i].y && 
			hrac.x + SIRKA_HRACE * velikost >= KolizeMapy[i].x
			)
			return true;
	}
	return false;
}

int Kolize::Bedna(Pozice mec, float velikost, vector<Pozice> KolizeMapy)
{
	D = KolizeMapy;

	for (int i = 0; i < KolizeMapy.size(); i++)
	{
		if (
			mec.x +16 * velikost >= KolizeMapy[i].x &&	//1 podminka	//16
			KolizeMapy[i].x+32 >= mec.x &&						//2 p.
			mec.y + 21 * velikost >= KolizeMapy[i].y &&	//3 p.			//21
			KolizeMapy[i].y+32 >= mec.y							//4 p.
			)
			return i;
	}
	return (-2);
}

//SPATNE POUZITE KOLIZE (ale ruzne zpusoby), bohuzel nedodelane--> NEFUNKCNI
/*
int Kolize::KolizeJE(Pozice Budouci, Pozice AktPozice, Pozice Rychlost, vector<Pozice> mapaKol)
{

	Pozice BudouciPoz = Budouci;
	Pozice aktualni = AktPozice;
	Pozice Rychl = Rychlost;
	D = mapaKol;

	for (int i = 0; i < D.size(); i++)
	{
		Pozice Dlaz = D[i];
		if (Rychl.x < 0)	//Jde do leva
		{

			if ((BudouciPoz.x <= (Dlaz.x + 32) && aktualni.y == Dlaz.y) || (BudouciPoz.x <= (Dlaz.x + 32) && (aktualni.y + (VYSKA_HRACE - 0.1f)) == Dlaz.y))
			{
				return(1);
			}
		}
		if (Rychl.x > 0)    //do prava 
		{
			if (((BudouciPoz.x + (SIRKA_HRACE)) >= Dlaz.x && aktualni.y == Dlaz.y) || ((BudouciPoz.x + (SIRKA_HRACE)) >= Dlaz.x && (aktualni.y + (VYSKA_HRACE - 0.1f)) == Dlaz.y))
			{
				return(2);
			}
		}
		if (Rychl.y < 0)	//Jde nahoru
		{

			if ((BudouciPoz.x == Dlaz.x && BudouciPoz.y <= Dlaz.y + 32) || ((BudouciPoz.x == Dlaz.x && (aktualni.y + (VYSKA_HRACE - 0.1f)) <= Dlaz.y + 32)))
			{
				return(3);
			}
		}
		if (Rychl.y > 0)    //dolu 
		{
			if ((BudouciPoz.x == Dlaz.x && (BudouciPoz.y + VYSKA_HRACE) >= Dlaz.y) || ((BudouciPoz.x == Dlaz.x && (aktualni.y + (VYSKA_HRACE - 0.1f))) >= Dlaz.y))
			{
				return(4);
			}
		}

	}
	
}
*/

/*
Pozice Kolize::KontrolaKolize(Pozice Budouci,Pozice AktPozice, Pozice Rychlost, vector <Pozice> mapaKol)
{

	Pozice BudouciPoz = Budouci;
	Pozice aktualni = AktPozice;
	Pozice Rychl = Rychlost;
	
	
	D = mapaKol;
	for (int i = 0; i < D.size(); i++)
	{
		Pozice Dlaz = D[i];

		if (Rychl.x < 0)	//Jde do leva
		{
		
				if ((BudouciPoz.x != (Dlaz.x+32) && aktualni.y != Dlaz.y) || (BudouciPoz.x != (Dlaz.x+32) && (aktualni.y + (VYSKA_HRACE - 0.1f)) != Dlaz.y))
				{
					BudouciPoz.x = BudouciPoz.x + 1;
					BudouciPoz.y = 0;

					return (BudouciPoz);
					//hrac.Rychlost_Reset();
				}
		
		}
		else if (Rychl.x > 0)    //do prava 
		{
			if (((BudouciPoz.x+(SIRKA_HRACE)) != Dlaz.x && aktualni.y != Dlaz.y) || ((BudouciPoz.x+(SIRKA_HRACE)) != Dlaz.x && (aktualni.y + (VYSKA_HRACE-0.1f)) != Dlaz.y))
			{
				BudouciPoz.x = BudouciPoz.x;
				BudouciPoz.y = 0;

				return (BudouciPoz);
				//hrac.Rychlost_Reset();
			}
		}

		if (Rychl.y < 0)	//Jde nahoru
		{

			if ((BudouciPoz.x != Dlaz.x && BudouciPoz.y != Dlaz.y+32) || ((BudouciPoz.x != Dlaz.x && (aktualni.y + (VYSKA_HRACE - 0.1f)) != Dlaz.y+32)))
			{
				BudouciPoz.y = BudouciPoz.y + 1;
				BudouciPoz.x = 0;

				return (BudouciPoz);
				//hrac.Rychlost_Reset();
			}

		}
		else if (Rychl.y > 0)    //dolu 
		{
			if ((BudouciPoz.x != Dlaz.x && (BudouciPoz.y+VYSKA_HRACE) != Dlaz.y) || ((BudouciPoz.x != Dlaz.x && (aktualni.y + (VYSKA_HRACE - 0.1f))) != Dlaz.y))
			{
				BudouciPoz.y = BudouciPoz.y;
				BudouciPoz.x = 0;

				return (BudouciPoz);
				//hrac.Rychlost_Reset();
			}
		}
	

	
	}
	if (Rychl.x == 0 && Rychl.y == 0) {
		BudouciPoz.x = 0;
		BudouciPoz.y = 0;
	}

	return(BudouciPoz);
}
*/