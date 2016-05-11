
#include <iostream>
#include "Game.h"

vector <Unit*> Game::allUnit;
bool Game::pause=true;
bool Game::gameOver=false;
bool Game::win=false;
InterFace* Game::interFace=nullptr;

unsigned int Game::bombs=0;
unsigned int Game::level=1;
unsigned int Game::rockets=5;
unsigned int Game::score=0;

unsigned int Game::targetCount=0;
unsigned int Game::bombCount=0;
unsigned int Game::rocketCount=0;

unsigned int Game::speedBomb=SPEEDOFBOMB;
unsigned int Game::speedAirCraft=SPEEDOFAIRCRAFT;

Game::Game(HINSTANCE& hInstance, int nCmdShow, size_t height, size_t width){
	Game::interFace=new InterFace(hInstance, nCmdShow,height, width);
	Game::NewGame();
}

Game::~Game() {
}

void Game::NewGame(){
	Game::Clear();

	Game::GetLevel()=1;
	Game::GetScore()=0;

	unsigned int bombs=Init();

	UINT level=Game::GetLevel()*2;
	if (level>20){
		level=20;
	}

	Game::GetBombs()=5+bombs+(int)((bombs*(100-level))/100.0);
	Game::GetRockets()=5;

	Game::gameOver=false;
	Game::win=false;

	Game::GetSpeedBomb()=SPEEDOFBOMB;
	Game::GetSpeedAirCraft()=SPEEDOFAIRCRAFT;

	interFace->SetStatistics(Game::bombs,Game::level,Game::score,Game::rockets);
}

void Game::Clear(){
	int size=Game::allUnit.size();
	for (int i=0;i<size;i++){
		delete allUnit[i];
	}
	Game::allUnit.clear();
}

void Game::DropBomb(){
	if (Game::GetBombs()>0){
		Unit* airCraft=Game::GetUnit()->at(0);
		Bombs* newBomb=new Bombs(airCraft->GetCoorX(),airCraft->GetCoorY());
		if (Game::GetBombCount()>0){
			newBomb->Marvel();
		}
		Game::GetUnit()->push_back(newBomb);
		Game::GetBombs()--;
	}
}

void Game::FireRocket(){
	if (Game::GetRockets()>0){
		Unit* airCraft=Game::GetUnit()->at(0);
		Rocket* newRocket=new Rocket(airCraft->GetCoorX(),airCraft->GetCoorY());
		if (Game::GetRocketCount()>0){
			Game::GetRocketCount()--;
			newRocket->Marvel();
		}
		Game::GetUnit()->push_back(newRocket);
		Game::GetRockets()--;
	}
}

void Game::SetMarvel() {
	unsigned int size=Game::GetUnit()->size();
	for (unsigned int i=0;i<size;i++){
		if (typeid(*(Game::GetUnit()->at(i)))!=typeid(PartOfBuilding)){
			continue;
		}
		PartOfBuilding* tempPart=(PartOfBuilding*)Game::GetUnit()->at(i);

		//Set magic
		if (tempPart->GetName()==UnitsType::ROOF || tempPart->GetName()==UnitsType::FIRE) {
			if (tempPart->isMagic()){
				if (rand()%100<70){
					tempPart->Magic();
				}
				continue;
			}
			if (rand()%100<10){
				tempPart->Magic();
				if (rand()%100<70){
					return;
				}
			}
		}
	}
}

void Game::EnableMarvel(PartOfBuilding* unit){

	unsigned int textID=NAME_ADDBOMB;
	unsigned int ran=rand()%100;

	if (ran<20){
		Game::GetBombs()+=10;
		textID=NAME_ADDBOMB;
	}
	else if(ran<40) {
		Game::GetRockets()+=3;
		textID=NAME_ADDROCKET;
	}
	else if (ran<60){
		Game::GetBombCount()+=10;
		textID=NAME_STRONGBOMB;
	}
	else if(ran<80) {
		Game::GetRocketCount()++;
		textID=NAME_STRONGROCKET;
	}
	else {
		Game::GetTargetCount()+=30;
		textID=NAME_TARGGETER;
	}

	Game::GetInterFace()->SetFlyingText(GetLocalText(textID),unit->GetCoorX()*16+XSTARTOFFIELD+8,unit->GetCoorY()*16+YSTARTOFFIELD);
	unit->Magic();
}


void Game::AllStep(UINT timerID){
	unsigned int countBuilding=0;
	unsigned int countBombs=0;
	vector <Unit*>* tempUnits=Game::GetUnit();

	// the Step () can change  the allUnit size because 
	//PartOfBuilding or the Bomb can be destroyed
	for (unsigned int i=0;i<Game::GetUnit()->size();i++){
		UnitsType tempUnitType=tempUnits->at(i)->GetName();

		if (typeid(*(tempUnits->at(i)))==typeid(PartOfBuilding)){
			countBuilding++;
		}

		if ((tempUnitType==UnitsType::BOMB || tempUnitType==UnitsType::ROCKET)){
			countBombs++;
			if (timerID==Timers::TIMERBOMB){
				tempUnits->at(i)->Step();
			}
		}
		if (timerID==Timers::TIMERHELICOPTER && tempUnitType==UnitsType::HELICOPTER){
			tempUnits->at(i)->Step();
		}
		if (timerID==Timers::TIMERAIRCRAFT && tempUnitType==UnitsType::AIRCRAFT){
			tempUnits->at(i)->Step();
			break;
		}
	}
//TODO include rocket for end of game
	if (Game::GetBombs()==0 && countBuilding>0 && countBombs==0){
		Game::Lose();
	}
}

void Game::Lose(){
	Game::GameOver();
	Game::Pause();
}

void Game::Wins(){

	Game::GetLevel()++;
	Game::GetScore()+=GetBombs()*3;

	Game::Win();
	Game::Pause();

	Game::Clear();
	unsigned int bombs=Init();
//TODO dependense from level
	UINT level=Game::GetLevel()*5;

	if (level>90){
		level=90;
	}

	Game::GetBombs()=5+bombs+(int)((bombs*(100-level))/100.0);
	Game::GetRockets()+=5;

	Game::GetSpeedBomb()=SPEEDOFBOMB;
	Game::GetSpeedAirCraft()=SPEEDOFAIRCRAFT;

	interFace->SetStatistics(Game::bombs,Game::level,Game::score,Game::rockets);
}

unsigned int& Game::GetBombs(){
	return Game::bombs;
}
unsigned int& Game::GetLevel(){
	return Game::level;
}
unsigned int& Game::GetRockets(){
	return Game::rockets;
}
unsigned int& Game::GetScore(){
	return Game::score;
}

unsigned int& Game::GetSpeedBomb(){
	return Game::speedBomb;
}
unsigned int& Game::GetSpeedAirCraft(){
	return Game::speedAirCraft;
}

unsigned int& Game::GetTargetCount(){
	return Game::targetCount;
}
unsigned int& Game::GetBombCount(){
	return Game::bombCount;
}
unsigned int& Game::GetRocketCount(){
	return Game::rocketCount;
}


void Game::Pause(){
	Game::pause=!Game::pause;
}

bool Game::isPause(){
	return Game::pause;
}

void Game::GameOver(){
	Game::gameOver=!Game::gameOver;
}

bool Game::isGameOver(){
	return Game::gameOver;
}

void Game::Win(){
	Game::win=!Game::win;
}

bool Game::isWin(){
	return Game::win;
}

/**
	Statics function returns allUnit
*/
vector<Unit*>* Game::GetUnit() {
	return &Game::allUnit;
}

void Game::DeleteUnit(Unit* unit){
	int size=Game::allUnit.size();
	for (int i=0;i<size;i++){
		if (allUnit[i]==unit){
			delete allUnit[i];
			allUnit.erase(allUnit.begin()+i);
			return;
		}
	}
}

InterFace* Game::GetInterFace(){
	return Game::interFace;
}

unsigned int Game::Init() {
	Game::GetUnit()->push_back(AirCraft::Instance(0,0));

	vector <unsigned int> endOfBuilding;

	unsigned int countOfParts=0;
	UINT level=Game::GetLevel()*2;
	if (level>20){
		level=20;
	}
	//Game::GetUnit()->push_back(new PartOfBuilding(10,29,UnitsType::ROOF));
	//Game::GetUnit()->push_back(new PartOfBuilding(10,28,UnitsType::ROOF));
	//Game::GetUnit()->push_back(new PartOfBuilding(10,27,UnitsType::ROOF));
	for (UINT i=0;i<WIDTHOFFIELD;i++) {
		for (UINT q=HEIGHTOFFIELD-1;q>HEIGHTOFFIELD-7-level;q--) {
			if ((UINT)(rand()%100)<(CHANSEOFROOF-level) && CheckForRoof(endOfBuilding, i)){
				PartOfBuilding* building=new PartOfBuilding(i,q,UnitsType::ROOF);
				building->SetType(BuildingType::ROOF1);
				Game::GetUnit()->push_back(building);
				endOfBuilding.push_back(i);
				countOfParts++;
			}
			else if (CheckForRoof(endOfBuilding, i)) {
				if (q==HEIGHTOFFIELD-6-level) {
					PartOfBuilding* building=new PartOfBuilding(i,q,UnitsType::ROOF);
					building->SetType(BuildingType::ROOF1);
					Game::GetUnit()->push_back(building);
					endOfBuilding.push_back(i);
					countOfParts++;
				}
				else {
					PartOfBuilding* building=new PartOfBuilding(i,q);
					
					building->SetType(BuildingType::BUILDING1);
					if (rand()%100<50){
						building->SetType(BuildingType::BUILDING2);
					}
					else if (rand()%100<50){
						building->SetType(BuildingType::BUILDING3);
					}

					Game::GetUnit()->push_back(building);
					countOfParts++;
				}
			}
		}
	}
//TODO
	Game::SetMarvel();
	return countOfParts;
}

bool Game::CheckForRoof(vector <unsigned int>& endOfBuilding, unsigned int index){
	int size=endOfBuilding.size();
	for (int z=0;z<size;z++){
		if (index==endOfBuilding[z]){
			return false;
		}
	}
	return true;
}