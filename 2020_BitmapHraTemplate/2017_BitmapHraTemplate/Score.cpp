#include "stdafx.h"
#include "Score.h"

Score::Score(void)
{
	score = 0;
}

void Score::ZvysSkore()
{
	score = score + 1;
}

int Score::GetScore()
{
	return score;
}

void Score::Display(HDC dc)
{
	char skore[30];
	itoa(GetScore(), skore, 10);
	
	TextOut(dc, 0, 20, TEXT("SCORE:"), (6));
	TextOut(dc, 50, 20, TEXT(skore), strlen(skore));
	//TextOut(dc, 0, 20,  TEXT("SCORE: %u",skore), (6+ strlen(skore)));	//nevim jak to dát do jednoho text outu ??
}

void Score::ResetScore()
{
	score = 0;
}
