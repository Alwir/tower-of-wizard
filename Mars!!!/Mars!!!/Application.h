#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <tchar.h>
#include <vector>

using std::vector;

#include "resource.h"
#include "Constants.h"
#include "FlyingText.h"

class Application
{
public:
	Application(HINSTANCE& hInstance, size_t newHeight, size_t newWidth);
	virtual ~Application();

	virtual int Create()=0;

	virtual int Run()=0;

	virtual int GetKey()=0;
	virtual void SetKey(int newKey)=0;

	void SetBombs(unsigned int bombs);
	void SetLevel(unsigned int level);
	void SetRockets(unsigned int rockets);
	void SetScore(unsigned int score);
	void SetSpeed(unsigned int speed);

	void AddFlyingText(TCHAR* newLabel, UINT newX, UINT newY);
		
	HWND hwnd;

protected:
	virtual void Show(HDC& hdc)=0;

	int key;

	size_t height;
	size_t width;

	HINSTANCE& hInstance;
	
	TCHAR bombs[MAX_LOADSTRING];
	TCHAR level[MAX_LOADSTRING];
	TCHAR rockets[MAX_LOADSTRING];
	TCHAR score[MAX_LOADSTRING];
	TCHAR speed[MAX_LOADSTRING];

	vector <FlyingText*> flyingText;
};

