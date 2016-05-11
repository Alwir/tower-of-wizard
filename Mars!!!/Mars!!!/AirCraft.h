#pragma once
#include "Unit.h"
#include "Game.h"

class AirCraft : public Unit {

public:
	~AirCraft();

	virtual bool Step();
	static AirCraft* Instance(unsigned int newCoorX, unsigned int newCoorY);

protected:
	static AirCraft* self;

	AirCraft(unsigned int newCoorX, unsigned int newCoorY);

	virtual Unit* Collision(unsigned int newCoorX, unsigned int newCoorY);	
	
};

