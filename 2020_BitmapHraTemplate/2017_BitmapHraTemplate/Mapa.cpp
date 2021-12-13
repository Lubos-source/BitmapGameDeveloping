#include "stdafx.h"
#include "Mapa.h"

void Mapa::LoadData(HDC dc, char* x)
{
	m_Btm.LoadBitmap(x, dc);			//drak.bmp	//"mapaTEST.bmp"
}

void Mapa::Display(HDC dc)	//, int pozX, int pozY, char* x
{				 //(Platno, pozX, pozY, sirka, vyska, SIRKADL, VYSKADL, PRUHLDNA_barva(0-levy horni roh));	
	int dl;

	for (int i = 0; i < 24; i++)
	{
		for (int z = 0; z< 32; z++) 
		{
			dl = mapa[i][z];
			
			switch (dl)
			{
			case -1 :
				break;
			case 0:
				break;		
			default:
				m_Btm.Zobraz_Dlazdici(dc, z * 32, i * 32, Sirka_Dlazdice, Vyska_Dlazdice, UlozDlazdice[dl].sloupec, UlozDlazdice[dl].radek, 0);
				break;
			}
			
		}
	}
	
}

void Mapa::NactiKolizi()
{
	int dl; Pozice pom;
	DlazdiceKolize.clear();
	DvereTrava.clear(); DvereDlazdice.clear(); Body.clear(); Smrt.clear(); KrabDlaz.clear(); KrabZel.clear();

	for (int i = 0; i < 24; i++)
	{
		for (int z = 0; z < 32; z++)
		{
			dl = mapa[i][z];

			switch (dl)
			{
			case -1:
				break;
			case 0:
				break;
			case 66:
				break;
			case 10:
				break;
			case 12:
				break;
			case 20:
				break;
			case 21:
				break;
			case 22:
				break;
			case 26:
				break;
			case 52:
				break;
			case 53:
				break;
			case 56:
				break;
			case 57:
				break;
			case 61:
				break;
			case 71:
				break;
			case 73:
				break;
			case 74:
				break;
			case 75:
				break;
			case 81:
				break;
			case 63:	//vylez
				break;
			case 50:	//dvere do zeme trava
				pom.x = z * 32;
				pom.y = i * 32;
				DvereTrava.push_back(pom);
				break;
			case 51:	//dvere do zeme dlazdice
				pom.x = z * 32;
				pom.y = i * 32;
				DvereDlazdice.push_back(pom);
				break;
			case 59:	//krabice trava				
				pom.x = z * 32;
				pom.y = i * 32;
				KrabZel.push_back(pom);	
				DlazdiceKolize.push_back(pom);
				indx = DlazdiceKolize.size();
				break;
			case 58:	//krabice dlazdice
				pom.x = z * 32;
				pom.y = i * 32;
				KrabDlaz.push_back(pom);	
				DlazdiceKolize.push_back(pom);
				break;
			case 13:	//mince (body)
				pom.x = z * 32;
				pom.y = i * 32;
				Body.push_back(pom);
				break;
			case 11:	//rybnicek (smrt)
				pom.x = z * 32;
				pom.y = i * 32;
				Smrt.push_back(pom);
				break;
			default:				
				pom.x = z * 32;
				pom.y = i * 32;
				DlazdiceKolize.push_back(pom);
				break;
			}

		}
	}

}
/*
vector<Pozice> Mapa::VratKoliziDL()
{
	vector <Pozice> pom;
	for (int i = 0; i < DlazdiceKolize.size(); i++)
	{
		
		pom.push_back(DlazdiceKolize[i]);
	}

	return pom;
}
*/

Mapa::Mapa(void)
{
	
	for(int i=0;i<9;i++)	
	{		
		//temp.radek = i;
		for (int j = 0; j < 10; j++) 
		{
			Dlazdice temp;
			temp.radek = i;
			temp.sloupec = j;
			UlozDlazdice.push_back(temp);	//Ulozim si dlazdici [cislo dlazdice] --> ulozi se kolikaty je to radek a sloupec.
		}
		
	}
	
	
		
}

Mapa::~Mapa(void)
{
	UlozDlazdice.clear();
}
