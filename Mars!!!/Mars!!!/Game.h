#pragma once

#include <vector>
using std::vector;

#include "resource.h"
#include "AirCraft.h"
#include "PartOfBuilding.h"
#include "Bombs.h"
#include "Rocket.h"
#include "Helicopter.h"
#include "InterFace.h"

class Game
{
public:
	Game(HINSTANCE& hInstance, int nCmdShow, size_t height, size_t width);
	~Game();

	static unsigned int Init();

	static vector<Unit*>* GetUnit();
	static void DeleteUnit(Unit* unit);

	static unsigned int& GetBombs();
	static unsigned int& GetLevel();
	static unsigned int& GetRockets();
	static unsigned int& GetScore();

	static unsigned int& GetSpeedBomb();
	static unsigned int& GetSpeedAirCraft();

	static void Pause();
	static bool isPause();

	static void GameOver();
	static bool isGameOver();

	static void Win();
	static bool isWin();

	static void NewGame();

	static InterFace* GetInterFace();
	/**
		Delete all object from allUnit
	*/
	static void Clear();

	static void DropBomb();
	static void FireRocket();

	static void Lose();
	static void Wins();

	static void AllStep(UINT timerID);

	static unsigned int& GetTargetCount();
	static unsigned int& GetBombCount();
	static unsigned int& GetRocketCount();

	static void SetMarvel();
	static void EnableMarvel(PartOfBuilding* unit);

private:

	static bool pause;
	static bool gameOver;
	static bool win;

	static vector <Unit*> allUnit;

	static InterFace* interFace;

	static unsigned int bombs;
	static unsigned int level;
	static unsigned int rockets;
	static unsigned int score;

	static unsigned int speedBomb;
	static unsigned int speedAirCraft;

	static unsigned int targetCount;
	static unsigned int bombCount;
	static unsigned int rocketCount;

	static bool CheckForRoof(vector <unsigned int>& endOfBuilding, unsigned int index);
};

