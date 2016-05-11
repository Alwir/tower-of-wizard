#pragma once
#include "Unit.h"
#include "Game.h"

class Bombs : public Unit
{
public:
	Bombs(unsigned int newCoorX, unsigned int newCoorY);
	~Bombs();
	virtual bool Step();
	void Marvel();

protected:
	virtual Unit* Collision(unsigned int newCoorX, unsigned int newCoorY);

private:
	HSTREAM sound;
	bool marvelValue;
};

