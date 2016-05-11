#include "PartOfBuilding.h"


PartOfBuilding::PartOfBuilding(unsigned int newCoorX, unsigned int newCoorY, UnitsType name):Unit(newCoorX, newCoorY,name), magic(false) {}


PartOfBuilding::~PartOfBuilding()
{
}

bool PartOfBuilding::Step(){
	return true;
}

Unit* PartOfBuilding::Collision(unsigned int newCoorX, unsigned int newCoorY){
	return nullptr;
}

void PartOfBuilding::SetType(BuildingType type){
	this->typeOfImage=type;
}
BuildingType PartOfBuilding::GetType() const {
	return this->typeOfImage;
}

bool PartOfBuilding::isMagic() const {
	return this->magic;
}

void PartOfBuilding::Magic() {
	this->magic=!this->magic;
}