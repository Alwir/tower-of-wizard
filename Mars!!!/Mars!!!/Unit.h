#pragma once
#include "Constants.h"
//#include "Game.h"

class Unit
{
public:
	Unit(unsigned int newCoorX=0, unsigned int newCoorY=0, UnitsType=UnitsType::BUILDING);
	virtual ~Unit();

	unsigned int GetCoorX() const;
	unsigned int GetCoorY() const;
	UnitsType GetName() const;

	virtual bool Step()=0;
	void Destroy(bool makeFire=true);
	

protected:
	void SetCoordinate(unsigned int newCoorX, unsigned int newCoorY);

	virtual Unit* Collision(unsigned int newCoorX, unsigned int newCoorY)=0;

private:
	unsigned int coorX;
	unsigned int coorY;

	UnitsType type;
};
