#pragma once
#include <Windows.h>
#include "MainWindow.h"

class InterFace
{
public:
	InterFace(HINSTANCE& hInstance, int nCmdShow, size_t height, size_t width);
	~InterFace();

	void Run();

	void SetStatistics(unsigned int bombs,unsigned int level,unsigned int score,unsigned int rockets);

	void SetFlyingText(TCHAR* newLabel, UINT newX, UINT newY);

private:
	HINSTANCE* hInstance;
	Application* application;
};

