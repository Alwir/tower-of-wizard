#include <iostream>
#include "Helicopter.h"

Helicopter::Helicopter(unsigned int newCoorX, unsigned int newCoorY):Unit(newCoorX, newCoorY,UnitsType::HELICOPTER),timeLife(TIMEOFLIFEHELICOPTER){}

Helicopter::~Helicopter(){}

Unit* Helicopter::Collision(unsigned int newCoorX, unsigned int newCoorY) {
	size_t size=Game::GetUnit()->size();
	for (unsigned int i=0;i<size;i++){
		if (Game::GetUnit()->at(i)==this){
			continue;
		}

		if (Game::GetUnit()->at(i)->GetCoorX()==newCoorX &&
			Game::GetUnit()->at(i)->GetCoorY()==newCoorY &&
			(typeid(*(Game::GetUnit()->at(i)))==typeid(PartOfBuilding)||
			Game::GetUnit()->at(i)->GetName()==UnitsType::ROCKET ||
			Game::GetUnit()->at(i)->GetName()==UnitsType::AIRCRAFT)) {

			if (Game::GetUnit()->at(i)->GetName()==UnitsType::ROCKET){
				Game::GetScore()+=SCOREFORHELICOPTER*Game::GetLevel();
				Game::GetTargetCount()+=TIMEFORHELICOPTER;
			}
			else if (Game::GetUnit()->at(i)->GetName()==UnitsType::AIRCRAFT){
				Game::Lose();
			}
			return Game::GetUnit()->at(i);
		}
	}
	return nullptr;
}

bool Helicopter::Step(){
	unsigned int tempCoorX=this->GetCoorX();
	unsigned int tempCoorY=this->GetCoorY();

//TODO random time of life of helicopter
	this->timeLife--;
	if (timeLife<0){
		this->Destroy();
		return false;
	}

	UINT ran=rand()%100;
	if (ran<25) {
		tempCoorY++;
		if (tempCoorY>HEIGHTOFFIELD){
			tempCoorY=HEIGHTOFFIELD-1;
		}
	}
	else if (ran<50) {
		tempCoorY--;
	}
	if (ran<75) {
		tempCoorX++;
		if (tempCoorX>WIDTHOFFIELD){
			tempCoorX=WIDTHOFFIELD-1;
		}
	}
	else  {
		tempCoorX--;
		if (tempCoorX<0){
			tempCoorX+=2;
		}
	}

	Unit* collisionUnit=Collision(tempCoorX,tempCoorY);

	if (collisionUnit!=nullptr) {
		collisionUnit->Destroy();
		this->Destroy();
		return false;
	}
	this->SetCoordinate(tempCoorX,tempCoorY);
	return true;
}