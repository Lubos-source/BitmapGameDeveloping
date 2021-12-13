#pragma once
#include <sstream>

class Score
{
private:
	int score = 0;

public:
	Score(void);
	void ZvysSkore();
	int GetScore();
	void Display(HDC dc);
	void ResetScore();
	////////////////////////DODELAT ZATIM NEFUNKCNI ----> ZJISTIT JAK ZOBRAZIT DO nejakeho LABELU ???
};

