#include <iostream>
#include "Rocket.h"

Rocket::Rocket(unsigned int newCoorX, unsigned int newCoorY):Unit(newCoorX, newCoorY,UnitsType::ROCKET), marvelValue(false){
	MakeSound(ROCKETNOISE);
}

Rocket::~Rocket(){}


Unit* Rocket::Collision(unsigned int newCoorX, unsigned int newCoorY) {
	size_t size=Game::GetUnit()->size();
	for (unsigned int i=0;i<size;i++){
		if (Game::GetUnit()->at(i)==this){
			continue;
		}

		if (Game::GetUnit()->at(i)->GetCoorX()==newCoorX &&
			Game::GetUnit()->at(i)->GetCoorY()==newCoorY &&
			(typeid(*(Game::GetUnit()->at(i)))==typeid(PartOfBuilding)||
			Game::GetUnit()->at(i)->GetName()==UnitsType::HELICOPTER)) {

			if (Game::GetUnit()->at(i)->GetName()==UnitsType::HELICOPTER){
				Game::GetInterFace()->SetFlyingText(GetLocalText(NAME_TARGGETER),Game::GetUnit()->at(i)->GetCoorX()*16+XSTARTOFFIELD+8,Game::GetUnit()->at(i)->GetCoorY()*16+YSTARTOFFIELD);
				Game::GetScore()+=SCOREFORHELICOPTER*Game::GetLevel();
				Game::GetTargetCount()+=TIMEFORHELICOPTER;
			}
			else {
				Game::GetScore()+=Game::GetLevel();
			}

			MakeSound(EXPLOSIONNOISE);

			return Game::GetUnit()->at(i);
		}
	}
	return nullptr;
}


bool Rocket::Step(){
	unsigned int tempCoorX=this->GetCoorX();
	unsigned int tempCoorY=this->GetCoorY();

	tempCoorX++;
	if (tempCoorX>WIDTHOFFIELD){
		this->Destroy();
		return false;
	}

	if (this->marvelValue==true) {
		bool temp=true;
		for (unsigned int i=tempCoorX-2;i<tempCoorX+2;i++){
			for (unsigned int q=tempCoorY-2;q<tempCoorY+2;q++){
				Unit* collisionUnit=Collision(i,q);
				if (collisionUnit!=nullptr) {
					collisionUnit->Destroy();
					temp=false;
				}
			}
		}
		if (temp==false){
			this->Destroy();
			return false;
		}
	}
	else {
		Unit* collisionUnit=Collision(tempCoorX,tempCoorY);

		if (collisionUnit!=nullptr) {
			collisionUnit->Destroy();
			this->Destroy();
			return false;
		}
	}
	this->SetCoordinate(tempCoorX,tempCoorY);
	return true;
}

void Rocket::Marvel(){
	this->marvelValue=!this->marvelValue;
}