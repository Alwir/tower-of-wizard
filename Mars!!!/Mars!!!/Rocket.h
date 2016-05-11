#pragma once
#include "Unit.h"
#include "Game.h"

class Rocket :	public Unit
{
public:
	Rocket(unsigned int newCoorX, unsigned int newCoorY);
	~Rocket();

	virtual bool Step();
	void Marvel();

protected:
	virtual Unit* Collision(unsigned int newCoorX, unsigned int newCoorY);

private:
	bool marvelValue;
};

