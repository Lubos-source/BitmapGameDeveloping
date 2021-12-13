#include "StdAfx.h"
#include "Scene.h"
#include <string>

CScene::CScene(void)
{
	//dalsiLVL = 2;	//pouze vyvojarske preskakovani mezi lvly pro kontrolu zmen -> urychleni kontroly
}

CScene::~CScene(void)
{
}

void CScene::NacteniMapy(HDC hdc,char* mapa) {
	
	CCfgFile cfgfile;	
	Pozice StartNepr;
	

	if (cfgfile.LoadFile(mapa) >= 0) {			/*//!!!POZOR V .CFG NESMÍ BÝT VELKÁ PÍSMENA - NEROZEZNÁ A PAK NEJEDE TØÍDA CCfgfile!!!//*/

		cfgfile.GetStrValue(0, "cesta_soubor", m.Cesta_Soubor);		//POZOR CESTA V SOUBORU BEZ MEZERY ! jinak nenajde cestu k souboru (uklada se do stringu i mezera)
		cfgfile.GetStrValue(0, "cesta_level", m.Cesta_level);
		m.Sirka_obr = cfgfile.GetIntValue(0, "sirka_obr");
		m.Vyska_obr = cfgfile.GetIntValue(0, "vyska_obr"); 
		//cfgfile.GetStrValue(0, "jmeno_dlazdice", m.Jmeno_Dlazdice);
		m.Sirka_Dlazdice = cfgfile.GetIntValue(0, "sirka_dlazdice");
		m.Vyska_Dlazdice = cfgfile.GetIntValue(0, "vyska_dlazdice");
		
		Spawn.x = cfgfile.GetIntValue(0, "spawnx");
		Spawn.y = cfgfile.GetIntValue(0, "spawny");
		m_Drak.ZmenPozici(Spawn);			
		
		StartNepr.x = cfgfile.GetIntValue(0,"neprstartx");
		StartNepr.y = cfgfile.GetIntValue(0, "neprstarty");
		nepritel.ZmenPozici(StartNepr);

		m.Pocet_Radku = (int)((float)m.Vyska_obr / m.Vyska_Dlazdice);
		m.Pocet_Sloupcu = (int)((float)m.Sirka_obr / m.Sirka_Dlazdice);
		m.Pocet_Dlazdic = (int)(m.Pocet_Radku * m.Pocet_Sloupcu);
	
		cfgfile.GetMapLoad(m.Cesta_level, m.mapa);
		
	}
	m.LoadData(hdc, m.Cesta_Soubor);
}

void CScene::SetDalsilvl(int lvl)
{
	dalsiLVL = lvl;
}

int CScene::GetDalsiLVL()
{
	return dalsiLVL;
}

void CScene::AktualniLVL()
{
	aktualni = dalsiLVL;
}

int CScene::GetAktualniLVL()
{
	return aktualni;
}


void CScene::Init(HDC hdc) {


/* // UKAZKA NACTENI Z CFG
	CCfgFile cfgfile; //dekoder konfiguracniho souboru sceny

	if (cfgfile.LoadFile("scena1.cfg")>=0) { //nacteme konfiguracni soubor sceny
		// konfiguracni soubor muze byt rozdelen na sekce (oddeleny slozenymi zavorkami {})
		// obsahuje vzdy klicove slovo a hodnotu (string nebo cislo) oddelene symbolem rovna se =

		//**** toto je priklad jak nacitat data z konfiguracniho souboru
		int pocet_objektu = cfgfile.GetIntValue(0,"pocet_objektu"); // nacte ze sekce 0 (prvni sekce v souboru) hodnotu klicoveho slova pocet_objektu
		char nazev_objektu[255];
		cfgfile.GetStrValue(0,"nazev_objektu",nazev_objektu); //nacte string ze sekce 0 pod klicem nazev objektu
	}
	*/
	if (GetDalsiLVL() == 0)
	{
		NacteniMapy(hdc, "mapa1.cfg");
		m.NactiKolizi();
		AktualniLVL();
		SetDalsilvl(-1);
	}
	else if (GetDalsiLVL() == 1)
	{
		NacteniMapy(hdc, "mapa2.cfg");	
		m.NactiKolizi();
		AktualniLVL();
		SetDalsilvl(-1);				// (-1) ukonci inicializaci v TIMER cyklu
	}
	else if (GetDalsiLVL() == 2)
	{
		NacteniMapy(hdc, "mapaCIL.cfg");
		m.NactiKolizi();
		AktualniLVL();
		SetDalsilvl(-1);
	}
	else if (GetDalsiLVL() == 3)
	{
		NacteniMapy(hdc, "KONEC.cfg");
		m.NactiKolizi();
		AktualniLVL();
		//m_pozadi.LoadData(hdc);
		SetDalsilvl(-1);
	}
	else if (GetDalsiLVL() == 4)
	{
		NacteniMapy(hdc, "KONEC.cfg");
		m.NactiKolizi();
		AktualniLVL();
		//m_pozadi.LoadData(hdc);
		SetDalsilvl(-1);
	}
	
	//m_pozadi.LoadData(hdc);
	m_Drak.LoadData(hdc); //nahrajeme data k objektu Drak
	strela.LoadData(hdc);
	nepritel.LoadData(hdc);
}


void CScene::Render(HDC hdc) {
	
	//m_pozadi.Display(hdc);
	
	m.Display(hdc);
	m_Drak.Display(hdc); // zobrazime draka
	strela.Display(hdc);
	score.Display(hdc);
	nepritel.Display(hdc);
	
	//KONTROLA KOLIZE obdelnik okolo hrace
	
	//Rectangle(hdc, m_Drak.GetPozice().x, m_Drak.GetPozice().y, m_Drak.GetPozice().x + m_Drak.GetSirka() * m_Drak.GetVelikost(), m_Drak.GetPozice().y + m_Drak.GetVyska() * m_Drak.GetVelikost());

	//for (int i = 0; i < m.DlazdiceKolize.size(); i++)	//KONTROLA KDE JE KOLIZE vykresli obdelnik
	//{
	//	Pozice Dlaz = m.DlazdiceKolize[i];
	//	Rectangle(hdc, Dlaz.x, Dlaz.y, Dlaz.x+32*1 , Dlaz.y+32*1 );
	//}
	
}

bool isKeyDown(int key)
{
	return (GetAsyncKeyState(key) & (1 << 16));
}

void CScene::UserInput(WPARAM wParam) {
	// zpracujeme uzivateluv vstup z klavesnice
		if (wParam==VK_RIGHT) m_Drak.SetDirRight();
		if (wParam==VK_LEFT) m_Drak.SetDirLeft();
		if (wParam == VK_UP) m_Drak.SetDirUp();
		if (wParam == VK_DOWN) m_Drak.SetDirDown();
		else if (wParam == -255) { m_Drak.SetDirNone(); strela.SetStisk(false); }
		
		if (wParam == VK_SPACE && isKeyDown(VK_SPACE)) strela.Strel(m_Drak.GetPozice(), m_Drak.GetRychlost(), m_Drak.GetMinSmer());
		else if (isKeyDown(VK_SPACE) == false) { strela.StrelaSetPryc(); }
}

void CScene::Move() {
	vector <Pozice> PozHrace;
	PozHrace.push_back(m_Drak.GetPozice());

	/*
	Kolize kolize; Pozice pom;
	int kol;
	kol = kolize.KolizeJE(m_Drak.GetBudouci(), m_Drak.GetPozice(), m_Drak.GetRychlost(), m.DlazdiceKolize);
	switch (kol)
	{
	case 1:	//doleva
		pom.x = m_Drak.GetPozice().x + (16);
		pom.y = m_Drak.GetPozice().y;
		m_Drak.SetBudouci(pom);
		break;
	case 2:	//doprava
		pom.x = m_Drak.GetPozice().x + (-16);
		pom.y = m_Drak.GetPozice().y;
		m_Drak.SetBudouci(pom);
		break;
	case 3:	//nahoru
		pom.x = m_Drak.GetPozice().x;
		pom.y = m_Drak.GetPozice().y + (16);
		m_Drak.SetBudouci(pom);
		break;
	case 4:	//dolu
		pom.x = m_Drak.GetPozice().x;
		pom.y = m_Drak.GetPozice().y + (-16);
		m_Drak.SetBudouci(pom);
		break;
	default:
		break;
	}
	*/
	Kolize kol;
	
	m_Drak.Move(); // pohneme drakem
	
	Pozice PozPomocna;
	PozPomocna.x = m_Drak.GetPozice().x;
	PozPomocna.y = m_Drak.GetPozice().y -20;

	//// KOLIZE s okolim (zakazane bloky) ////
	if (kol.Colision(m_Drak.GetPozice(),m_Drak.GetVelikost(), m.DlazdiceKolize) == true)
	{
		m_Drak.ZmenPozici(PozHrace.back());
		
		/*	//ZKOUSKA NOVE VERZE : zatim nefunkcni
		int smer = m_Drak.GetDir();
		switch (smer)
		{
		case DRAK_DOWN:
			m_Drak.SetPodlaha(true);
			m_Drak.ZmenPozici(PozHrace.back());
			break;
		case DRAK_RIGHT:
			//m_Drak.ZmenPozici(m_Drak.GetBudouci());
			m_Drak.SetPodlaha(true);
			//m_Drak.ZmenPozici(PozPomocna);
			break;
		case DRAK_LEFT:
			m_Drak.SetPodlaha(true);
			//m_Drak.ZmenPozici(PozPomocna);
			break;
		case DRAK_UP:
			m_Drak.SetPodlaha(false);
			break;
		default:
			m_Drak.SetPodlaha(false);
			m_Drak.ZmenPozici(PozHrace.back());

			break;
		}
		*/

	}
	
	//// SMRT voda ////
	if (kol.Colision(m_Drak.GetPozice(), m_Drak.GetVelikost(), m.Smrt) == true)
	{
		m_Drak.SetZivoty(-1);
		Pozice smrt;
		PlaySound("soundeffects\\death.wav", NULL, SND_ASYNC);

		if (m_Drak.GetZivoty() > 0)
		{		
			
		}		
		else
		{
			SetDalsilvl(0);
			
			score.ResetScore();
			m_Drak.ZivotyReset();
		}
		m_Drak.ZmenPozici(Spawn);
		
	}
	
	//// BEDNA dlazdice ////
	if (kol.Bedna(strela.GetPozice(), strela.GetVelikost(), m.KrabDlaz) != (-2))
	{
		int index = kol.Bedna(strela.GetPozice(), strela.GetVelikost(), m.KrabDlaz);
		int pomx = m.KrabDlaz[index].y / 32;
		int pomy = m.KrabDlaz[index].x / 32;
		m.mapa[pomx][pomy] = 56;
		m.KrabDlaz.erase(m.KrabDlaz.begin() + index);
		PlaySound("soundeffects\\wood.wav", NULL, SND_ASYNC);
		m.NactiKolizi();
	}

	////BEDNA trava ////
	if (kol.Bedna(strela.GetPozice(), strela.GetVelikost(), m.KrabZel) != (-2))
	{
		int index = kol.Bedna(strela.GetPozice(), strela.GetVelikost(), m.KrabZel);
		Pozice ppp=m.KrabZel[index];
		int pomx = m.KrabZel[index].y / 32;
		int pomy = m.KrabZel[index].x / 32;
		m.mapa[pomx][pomy] = 57;		
		m.KrabZel.erase(m.KrabZel.begin() + index);
		PlaySound("soundeffects\\wood.wav", NULL, SND_ASYNC);
		m.NactiKolizi();						//neni nejvhodnejsi vzdy nacitat novou kolizi, ale nedokazal jsem se dostat k indexu kde 
												//je ulozena bedna v kolizi abych ji vymazal, tak znovu nacitam kolize-->tim ze se zmeni 
												//textura bedny na texturu bez kolize, kolize zmizi.
	}

	//// BODY (mince) ////
	if (kol.ColPenize(m_Drak.GetPozice(), m_Drak.GetVelikost(), m.Body) !=(-2))
	{		
		int index = kol.ColPenize(m_Drak.GetPozice(), m_Drak.GetVelikost(), m.Body);
		int pomx = m.Body[index].y/32;
		int pomy = m.Body[index].x / 32;
		m.mapa[pomx][pomy] = 66;	// Pokud sebere nahradi prazdnou dlazdici :)
		score.ZvysSkore();
		m.Body.erase(m.Body.begin() + index);
		PlaySound("soundeffects\\coin.wav", NULL, SND_ASYNC);
	}
	
	//// DVERE na trave ////
	if (kol.Colision(m_Drak.GetPozice(), m_Drak.GetVelikost(), m.DvereTrava) == true)
	{
		if (isKeyDown(VK_SPACE))		//pokud je zamcknuto tak VSTOUPI jinak ne !
		{
			
			strela.StrelaSetPryc();
			
			SetDalsilvl(GetAktualniLVL() + 1);
			m_Drak.ZmenPozici(Spawn);
		}
		
	}
	
	//// DVERE na dlazdici ////
	if (kol.Colision(m_Drak.GetPozice(), m_Drak.GetVelikost(), m.DvereDlazdice) == true)
	{
		if (isKeyDown(VK_SPACE))		//pokud je zamcknuto tak VSTOUPI jinak ne !
		{
			
			strela.StrelaSetPryc();
			m_Drak.ZmenPozici(Spawn);
			SetDalsilvl(GetAktualniLVL()+1);
		}

	}
	
	PozHrace.clear();	//uvolneni pameti (vymazani vektoru pozic hrace --> nepotrebujeme vzdy se ulozi nova pozice pri volani MOVE


	// ENEMY kolize + pohyb //
	vector <Pozice> PozNepr;
	PozNepr.push_back(nepritel.GetPozice());

	nepritel.Move();


	if (kol.Colision(nepritel.GetPozice(),1, m.DlazdiceKolize) == true)
	{
		nepritel.ZmenPozici(PozNepr.back());
		nepritel.ZmenSmer();
	}

	
	/// KOLIZE HRAC a NEPRITEL ///
	
	if (kol.Colision(m_Drak.GetPozice(), m_Drak.GetVelikost(), PozNepr) == true)
	{
		m_Drak.SetZivoty(-1);
		PlaySound("soundeffects\\zombie.wav", NULL, SND_ASYNC); 
		if (m_Drak.GetZivoty() > 0)
		{

		}
		else
		{
			SetDalsilvl(0);
			score.ResetScore();
			m_Drak.ZivotyReset();
			
		}
		m_Drak.ZmenPozici(Spawn);
	}

	PozNepr.clear();


						
				/*TO DO:

			***	*Dodelat nepritele---> skript nebo AI ?	
			***	*Dodelat zivoty a odecitani po kontaktu s nepritelem nebo jeho zbrani ? 
			???		(mozna udelat ze pred sebou ma dlazdici zbran ktere se nesmime dotknout abychom ho mohli zabit na blizko)
			***	*Dodelat skore po sebrani mince---> Nekde na obrazovce zobrazovat
			***	*Pridat hudbu a zvuky ---> Pokud pujde prehrat jen jeden zvuk jako u hada tak pouze zvuky po sebrani, DMG, rozbiti...
				*Dodelat KONEC HRY po dokonceni CIL lvl závìreèná obrazovka.
				*Dodelat ZACATEK HRY mozna i menu ?
						
				*/
						
						//prehravani zvuku: #include <windows.h>
						//PlaySound("D:\\life.wav", NULL, SND_ASYNC);
}

