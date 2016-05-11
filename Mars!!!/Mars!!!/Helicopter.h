#pragma once
#include "Unit.h"
#include "Game.h"

class Helicopter : public Unit
{
public:
	Helicopter(unsigned int newCoorX, unsigned int newCoorY);
	~Helicopter();
	virtual bool Step();

protected:
	virtual Unit* Collision(unsigned int newCoorX, unsigned int newCoorY);

private:
	int timeLife;
};

