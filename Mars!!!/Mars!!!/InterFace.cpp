#include "InterFace.h"
#include "Game.h"

InterFace::InterFace(HINSTANCE& hInstance, int nCmdShow, 
					size_t height, size_t width):
					application(new MainWindow(hInstance, nCmdShow,height, width)),
					hInstance(&hInstance){};

InterFace::~InterFace(){}

void InterFace::Run(){
	this->application->Create();

	while (true) {
		this->application->Run();
		int key=application->GetKey();
		if (key!=0){
			switch (key){
				//case VK_UP:
				//	application->SetLevel(1);
				//	break;
				case VK_DOWN:
					Game::Wins();
					InvalidateRect(application->hwnd,NULL,1);
					break;
/////////////////////////////////////////
				case VK_LEFT:
					if (Game::GetSpeedAirCraft()>=MINSPEEDAIRCRAFT) {
						Game::GetSpeedAirCraft()=MINSPEEDAIRCRAFT;
						break;
					}
					Game::GetSpeedAirCraft()+=10;
//					SetTimer(application->hwnd,Timers::TIMERAIRCRAFT,Game::GetSpeedAirCraft(),NULL);
					break;
				case VK_RIGHT:
					if (Game::GetSpeedAirCraft()<=MAXSPEEDAIRCRAFT) {
						Game::GetSpeedAirCraft()=MAXSPEEDAIRCRAFT;
						break;
					}
					Game::GetSpeedAirCraft()-=10;
					
					break;
/////////////////////////////////////////
				case '2':
					if (!Game::isPause() || Game::isGameOver()){
						break;
					}
				case VK_ESCAPE:
					if (Game::isWin()){
						Game::Win();
					}
					Game::Pause();
					InvalidateRect(application->hwnd,NULL,1);
					break;
/////////////////////////////////////////
				case '3':		//exit
					if (!Game::isPause() && (!Game::isGameOver() || !Game::isWin())){
						break;
					}
				case VK_FINAL:
					return;
/////////////////////////////////////////
				case '1':			//TODO new game
					if (!Game::isPause() || Game::isWin()){
						break;
					}
				case 0x07:
					Game::NewGame();
					Game::Pause();
					break;
/////////////////////////////////////////
				case VK_SPACE: {
					if (Game::isPause()){
						break;
					}
					Game::DropBomb();
					break;
				}
				case VK_CONTROL: {
					if (Game::isPause()){
						break;
					}
					Game::FireRocket();
					break;
				}
			}
			application->SetKey(0);
		}
	}
}

void InterFace::SetStatistics(unsigned int bombs,unsigned int level,unsigned int score,unsigned int rockets){
	this->application->SetBombs(bombs);
	this->application->SetLevel(level);
	this->application->SetScore(score);
	this->application->SetRockets(rockets);
}

void InterFace::SetFlyingText(TCHAR* newLabel, UINT newX, UINT newY){
	application->AddFlyingText(newLabel, newX, newY);
}