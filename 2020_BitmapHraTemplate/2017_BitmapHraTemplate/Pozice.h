#pragma once
class Pozice
{
public:
	float x, y;

public:
	Pozice(void);
	~Pozice(void);


	Pozice DruhaSourad(int sirka, int vyska, float velikost);

	Pozice operator*(float cislo);
	const Pozice operator+(const Pozice poz2);
	const Pozice operator-(const Pozice poz2);
		

};

