#include "Application.h"

Application::Application(HINSTANCE& newhInstance, size_t newHeight, size_t newWidth):
						hInstance(newhInstance),height(newHeight),width(newWidth){
	_tcsnccpy(this->speed,_T(">\0"),2);
}

Application::~Application(){
}

void Application::AddFlyingText(TCHAR* newLabel, UINT newX, UINT newY){
	this->flyingText.push_back(new FlyingText(newLabel,newX,newY));
}

void Application::SetBombs(unsigned int bombs){
	_itow(bombs,this->bombs,10);
}
void Application::SetLevel(unsigned int level){
	_itow(level,this->level,10);
}
void Application::SetRockets(unsigned int rocket){
	_itow(rocket,this->rockets,10);
}
void Application::SetScore(unsigned int score){
	_itow(score,this->score,10);
}
void Application::SetSpeed(unsigned int speed){
	_tcsnccpy(this->speed,_T(">\0"),2);

	if (speed<50){
		_tcsnccpy(this->speed,_T(">>>>>>\0"),7);
	}
	else if(speed<100) {
		_tcsnccpy(this->speed,_T(">>>>>\0"),6);
	}
	else if(speed<150) {
		_tcsnccpy(this->speed,_T(">>>>\0"),5);
	}
	else if(speed<200) {
		_tcsnccpy(this->speed,_T(">>>\0"),4);
	}
	else if(speed<250) {
		_tcsnccpy(this->speed,_T(">>\0"),3);
	}
}
