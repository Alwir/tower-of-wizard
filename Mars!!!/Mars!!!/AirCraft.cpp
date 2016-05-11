#include <iostream>
#include "AirCraft.h"


AirCraft* AirCraft::self=nullptr;

AirCraft::AirCraft(unsigned int newCoorX, unsigned int newCoorY):Unit(newCoorX, newCoorY,UnitsType::AIRCRAFT){};


AirCraft::~AirCraft(){
	self=nullptr;
}

AirCraft* AirCraft::Instance(unsigned int newCoorX, unsigned int newCoorY) {
	if (self==nullptr){
		self=new AirCraft(newCoorX,newCoorY);
	}
	return self;
}

Unit* AirCraft::Collision(unsigned int newCoorX, unsigned int newCoorY) {
	size_t size=Game::GetUnit()->size();
	for (unsigned int i=0;i<size;i++){
		if (Game::GetUnit()->at(i)==this){
			continue;
		}
		if (Game::GetUnit()->at(i)->GetCoorX()==newCoorX &&
			Game::GetUnit()->at(i)->GetCoorY()==newCoorY &&
			(typeid(*(Game::GetUnit()->at(i)))==typeid(PartOfBuilding)||
			Game::GetUnit()->at(i)->GetName()==UnitsType::HELICOPTER)) {

			return Game::GetUnit()->at(i);
		}
	}
	return nullptr;
}

bool AirCraft::Step(){
	unsigned int tempCoorX=this->GetCoorX();
	unsigned int tempCoorY=this->GetCoorY();

	tempCoorX++;
	if (tempCoorX>=WIDTHOFFIELD){
		tempCoorY++;
		if (tempCoorX>=WIDTHOFFIELD && tempCoorY>HEIGHTOFFIELD){
			Game::Wins();
			return false;
		}
		tempCoorX=0;
	}
	this->SetCoordinate(tempCoorX,tempCoorY);
	Unit* collisionUnit=Collision(tempCoorX,tempCoorY);

	if (collisionUnit!=nullptr) {
		Game::Lose();
		return false;
	}
	return true;
}

