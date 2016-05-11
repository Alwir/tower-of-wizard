#pragma once
#include "Unit.h"
class PartOfBuilding : public Unit
{
public:
	PartOfBuilding(unsigned int newCoorX, unsigned int newCoorY, UnitsType=UnitsType::BUILDING);
	~PartOfBuilding();

	virtual bool Step();

	void SetType(BuildingType type);
	BuildingType GetType() const;

	bool isMagic() const;
	void Magic();

protected:
	virtual Unit* Collision(unsigned int newCoorX, unsigned int newCoorY);

private:
	BuildingType typeOfImage;
	bool magic;
};

