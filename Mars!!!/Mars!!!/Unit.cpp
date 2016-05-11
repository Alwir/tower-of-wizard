#include <iostream>

#include "Unit.h"
#include "Game.h"
#include "bass.h"

Unit::Unit(unsigned int newCoorX, unsigned int newCoorY, UnitsType newName):
			coorX(newCoorX),coorY(newCoorY),type(newName) {}


Unit::~Unit(){}

//TODO Complete me
void Unit::Destroy(bool makeFire){
	if (this->type==UnitsType::HELICOPTER || this->type==UnitsType::BOMB || this->type==UnitsType::FIRE || this->type==UnitsType::ROCKET || makeFire==false){
		Game::DeleteUnit(this);
		return;
	}
	this->type=UnitsType::FIRE;
}

unsigned int Unit::GetCoorX() const {
	return this->coorX;
}

unsigned int Unit::GetCoorY() const {
	return this->coorY;
}

UnitsType Unit::GetName() const {
	return this->type;
}

void Unit::SetCoordinate(unsigned int newCoorX, unsigned int newCoorY) {
	if (newCoorX>WIDTHOFFIELD){
		newCoorX=0;
	}
	if (newCoorY>HEIGHTOFFIELD){
		newCoorY=0;
	}
	this->coorX=newCoorX;
	this->coorY=newCoorY;
}