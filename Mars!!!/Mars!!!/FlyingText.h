#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "Constants.h"
#include <tchar.h>

class FlyingText
{
public:
	FlyingText(TCHAR* newLabel, UINT newX, UINT newY);
	~FlyingText();

	UINT GetX() const;
	UINT GetY() const;
	TCHAR* GetLabel();

	void SetX(UINT newX);
	void SetY(UINT newY);
	void SetLabel(TCHAR* newLabel);

	void Fly();

	bool isDead() const;

private:
	UINT coorX;
	UINT coorY;
	UINT anchorX;
	UINT anchorY;
	TCHAR label[MAX_LOADSTRING];

	bool direction;

	bool dead;
};

