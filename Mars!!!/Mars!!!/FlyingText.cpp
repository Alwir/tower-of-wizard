#include "FlyingText.h"


FlyingText::FlyingText(TCHAR* newLabel, UINT newX, UINT newY):coorX(newX),coorY(newY),anchorX(newX),anchorY(newY),dead(false){
	
	//Warning	1	warning C4800: 'int' : forcing value to bool 'true' or 'false' (performance warning)
	//this->direction=rand()%2;
	this->direction=(rand()%2)?true:false;

	_tcsnccpy(this->label,newLabel,wcslen(newLabel)+1);
	delete [] newLabel;
}

FlyingText::~FlyingText(){}

UINT FlyingText::GetX() const {
	return this->coorX;
}
UINT FlyingText::GetY() const {
	return this->coorY;
}
TCHAR* FlyingText::GetLabel() {
	return this->label;
}

void FlyingText::SetX(UINT newX){
	this->coorX=newX;
}
void FlyingText::SetY(UINT newY){
	this->coorY=newY;
}
void FlyingText::SetLabel(TCHAR* newLabel){
UINT a=_tclen(newLabel);
	_tcsnccpy(this->label,newLabel,wcslen(newLabel)+1);
}

void FlyingText::Fly(){
	if (this->coorY<this->anchorY-FLYINGTEXTLIVE){
		dead=true;
	}
	this->coorY--;

	if (direction) {
		this->coorX++;
		if (this->coorX>this->anchorX+10){
			this->direction=false;
		}
	}
	else {
		this->coorX--;
		if (this->coorX<this->anchorX-10){
			this->direction=true;
		}
	}
}

bool FlyingText::isDead() const {
	return this->dead;
}