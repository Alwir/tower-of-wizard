#include <Windows.h>
#include "bass.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	BASS_Init( -1,44100, BASS_DEVICE_MONO | BASS_DEVICE_DMIX,0,NULL);

	Game game(hInstance,nCmdShow,1000,800);

	game.GetInterFace()->Run();
	
	return 0;
}