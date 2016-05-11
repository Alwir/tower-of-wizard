
#include <iostream>
#include "Bombs.h"

Bombs::Bombs(unsigned int newCoorX, unsigned int newCoorY):Unit(newCoorX, newCoorY,UnitsType::BOMB), marvelValue(false){
	this->sound=MakeSound(BOMBNOISE);
}

Bombs::~Bombs(){
	MakeSound(EXPLOSIONNOISE);
	BASS_StreamFree(this->sound);
}

Unit* Bombs::Collision(unsigned int newCoorX, unsigned int newCoorY) {
	size_t size=Game::GetUnit()->size();
	for (unsigned int i=0;i<size;i++){
		if (Game::GetUnit()->at(i)==this){
			continue;
		}

		if (Game::GetUnit()->at(i)->GetCoorX()==newCoorX &&
			Game::GetUnit()->at(i)->GetCoorY()==newCoorY &&
			typeid(*(Game::GetUnit()->at(i)))==typeid(PartOfBuilding)) {

			PartOfBuilding* tempPart=(PartOfBuilding*)Game::GetUnit()->at(i);

			//add marvel
			if (tempPart->isMagic()){
				Game::EnableMarvel(tempPart);
			}

			if (tempPart->GetName()==UnitsType::FIRE){
				tempPart->Destroy();
				return nullptr;
			}
			if (this->marvelValue==true){
				this->marvelValue=false;
				tempPart->Destroy(false);
				return nullptr;
			}

			Game::GetScore()+=Game::GetLevel();

			return tempPart;
		}
	}
	return nullptr;
}

bool Bombs::Step(){
	unsigned int tempCoorX=this->GetCoorX();
	unsigned int tempCoorY=this->GetCoorY();

	tempCoorY++;
	if (tempCoorY>HEIGHTOFFIELD){
		this->Destroy();
		return false;
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

void Bombs::Marvel(){
	this->marvelValue=!this->marvelValue;
}