#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Application.h"

class MainWindow : public Application
{

public:
	MainWindow(HINSTANCE& hInstance, int nCmdShow, size_t height=DEFAULTHEIGHT, size_t width=DEFAULTWIDTH);
	~MainWindow();

	virtual int Create();
	virtual int GetKey();
	virtual void SetKey(int newKey);
	virtual int Run();

private:
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	long int Message(HWND _window,unsigned int _message,WPARAM _wParam,LPARAM _lParam);

	int nCmdShow;

	TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
	TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

	TCHAR labText[LABELCOUNT][MAX_LOADSTRING];

	HBITMAP imageBackground;

	HBITMAP imageBombs;
	HBITMAP imageAirCraft;
	HBITMAP imageBuilding;
	HBITMAP imageBuilding1;
	HBITMAP imageBuilding2;
	HBITMAP imageRoof;
	HBITMAP imageFire;
	HBITMAP imageRoad;
	HBITMAP imageRoad1;
	HBITMAP imageRocket;
	HBITMAP imageHelicopter;
	HBITMAP imageMenu;

	HBITMAP imageMagic1;
	HBITMAP imageMagic2;
	HBITMAP imageMagic3;

	void MainWindow::TransparentBlit(HDC& hdc, int destX, int destY, int destWidth, int destHeight, 
					 HDC hdc2, int srcX, int srcY, UINT tranparency);


protected:
	virtual void Show(HDC& hdc);
};

