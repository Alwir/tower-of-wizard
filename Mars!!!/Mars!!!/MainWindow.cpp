#define _CRT_SECURE_NO_WARNINGS
#include <windowsx.h>
#include <iostream>

#include "MainWindow.h"
#include "Game.h"


MainWindow::MainWindow(HINSTANCE& newhInstance, int newnCmdShow, 
						size_t newHeight, size_t newWidth):
						nCmdShow(newnCmdShow),
						Application(newhInstance,newHeight,newWidth) {

	LoadString(hInstance, NAME_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, NAME_WINDOWS, szWindowClass, MAX_LOADSTRING);

	UINT strNumber=103;

	if (GetUserDefaultUILanguage()!=LANG_RUSSIAN+1024) {
		strNumber+=100;
	}
	
	for (UINT i=0; i<LABELCOUNT;i++){
		LoadString(hInstance, strNumber+i, labText[i], MAX_LOADSTRING);
	}

	this->imageBackground = (HBITMAP)LoadImage(newhInstance, MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_COPYFROMRESOURCE);
	this->imageBombs = (HBITMAP)LoadImage(newhInstance, MAKEINTRESOURCE(IDB_BITMAP3), IMAGE_BITMAP, 0, 0, LR_COPYFROMRESOURCE);
	this->imageAirCraft = (HBITMAP)LoadImage(newhInstance, MAKEINTRESOURCE(IDB_BITMAP2), IMAGE_BITMAP, 0, 0, LR_COPYFROMRESOURCE);
	this->imageBuilding = (HBITMAP)LoadImage(newhInstance, MAKEINTRESOURCE(IDB_BITMAP4), IMAGE_BITMAP, 0, 0, LR_COPYFROMRESOURCE);
	this->imageRoof = (HBITMAP)LoadImage(newhInstance, MAKEINTRESOURCE(IDB_BITMAP5), IMAGE_BITMAP, 0, 0, LR_COPYFROMRESOURCE);
	this->imageFire = (HBITMAP)LoadImage(newhInstance, MAKEINTRESOURCE(IDB_BITMAP6), IMAGE_BITMAP, 0, 0, LR_COPYFROMRESOURCE);
	this->imageRoad = (HBITMAP)LoadImage(newhInstance, MAKEINTRESOURCE(IDB_BITMAP7), IMAGE_BITMAP, 0, 0, LR_COPYFROMRESOURCE);
	this->imageBuilding1 = (HBITMAP)LoadImage(newhInstance, MAKEINTRESOURCE(IDB_BITMAP8), IMAGE_BITMAP, 0, 0, LR_COPYFROMRESOURCE);
	this->imageBuilding2 = (HBITMAP)LoadImage(newhInstance, MAKEINTRESOURCE(IDB_BITMAP9), IMAGE_BITMAP, 0, 0, LR_COPYFROMRESOURCE);	
	this->imageRocket = (HBITMAP)LoadImage(newhInstance, MAKEINTRESOURCE(IDB_BITMAP10), IMAGE_BITMAP, 0, 0, LR_COPYFROMRESOURCE);
	this->imageHelicopter = (HBITMAP)LoadImage(newhInstance, MAKEINTRESOURCE(IDB_BITMAP11), IMAGE_BITMAP, 0, 0, LR_COPYFROMRESOURCE);
	this->imageRoad1 = (HBITMAP)LoadImage(newhInstance, MAKEINTRESOURCE(IDB_BITMAP12), IMAGE_BITMAP, 0, 0, LR_COPYFROMRESOURCE);
	this->imageMenu = (HBITMAP)LoadImage(newhInstance, MAKEINTRESOURCE(IDB_BITMAP13), IMAGE_BITMAP, 0, 0, LR_COPYFROMRESOURCE);
	this->imageMagic1 = (HBITMAP)LoadImage(newhInstance, MAKEINTRESOURCE(IDB_BITMAP14), IMAGE_BITMAP, 0, 0, LR_COPYFROMRESOURCE);
	this->imageMagic2 = (HBITMAP)LoadImage(newhInstance, MAKEINTRESOURCE(IDB_BITMAP15), IMAGE_BITMAP, 0, 0, LR_COPYFROMRESOURCE);
	this->imageMagic3 = (HBITMAP)LoadImage(newhInstance, MAKEINTRESOURCE(IDB_BITMAP16), IMAGE_BITMAP, 0, 0, LR_COPYFROMRESOURCE);
}

MainWindow::~MainWindow(){
}

int MainWindow::Create() {
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = &MainWindow::WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = this->hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = this->szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex)) {
		return 1;
    }

	HWND hWnd = CreateWindow(
        this->szWindowClass,
        this->szTitle,
		WS_OVERLAPPED | WS_CAPTION,
        CW_USEDEFAULT, CW_USEDEFAULT,
		this->height,this->width,
        NULL,
        NULL,
        hInstance,
        this
    );

	if (!hWnd) {
       return 2;
    }

	this->hwnd=hWnd;

	SetWindowLong(hWnd,GWL_USERDATA,(long int)this);

	ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

	return 0;
}

 int MainWindow::Run(){
 	MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);

        DispatchMessage(&msg);
		break;
    }
	return (int) msg.wParam;
 }


int MainWindow::GetKey(){
	return this->key;
}

void MainWindow::SetKey(int newKey){
	this->key=newKey;
}

long int MainWindow::Message(HWND hWnd,unsigned int message,WPARAM wParam,LPARAM lParam){
    PAINTSTRUCT ps;
    HDC hdc;
    switch (message)
    {
	case WM_CREATE:
		SetTimer(hWnd,Timers::TIMERBOMB,Game::GetSpeedBomb(),NULL); //timer for bomb
		SetTimer(hWnd,Timers::TIMERAIRCRAFT,Game::GetSpeedAirCraft(),NULL); //timer for aircraft
		SetTimer(hWnd,Timers::TIMERHELICOPTER,SPEEDOFHELICOPTER,NULL); //timer for helicopter
		SetTimer(hWnd,Timers::TIMERSECONDS,1000,NULL); //timer for seconds
		SetTimer(hWnd,Timers::TIMERMARVEL,30000,NULL); //timer for marvel
		break;
	case WM_TIMER: {
			if (Game::isPause() || Game::isWin() || Game::isGameOver()){
				break;
			}
			if (wParam==Timers::TIMERSECONDS) {
				if (Game::GetTargetCount()>0){
					Game::GetTargetCount()--;
				}
				if (Game::GetBombCount()>0){
					Game::GetBombCount()--;
				}
				break;
			}
			if (wParam==Timers::TIMERMARVEL) {
				if (rand()%100<70 && Game::GetUnit()->at(0)->GetCoorX()<WIDTHOFFIELD-10){
					Game::GetUnit()->push_back(new Helicopter(WIDTHOFFIELD-3+(1-rand()%3), Game::GetUnit()->at(0)->GetCoorY()+(1-rand()%3)));
				}
				Game::SetMarvel();
				break;
			}

			InvalidateRect(hwnd,NULL,1);
			if (wParam==Timers::TIMERAIRCRAFT){
				SetTimer(hWnd,Timers::TIMERAIRCRAFT,Game::GetSpeedAirCraft(),NULL);
			}

			Game::AllStep(wParam);

			SetBombs(Game::GetBombs());
			SetLevel(Game::GetLevel());
			SetRockets(Game::GetRockets());
			SetScore(Game::GetScore());
			SetSpeed(Game::GetSpeedAirCraft());
			break;
		}
	case WM_KEYDOWN:
		this->SetKey(wParam);
		break;
	case WM_LBUTTONDOWN:{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam);
			if (xPos>400 && yPos>340 && xPos<625 && yPos<365 && Game::isWin()!=true && Game::isPause()==true){
				this->SetKey(0x07);
			}
			if (xPos>400 && yPos>395 && xPos<640 && yPos<420 && Game::isGameOver()!=true && Game::isPause()==true){
				this->SetKey(VK_ESCAPE);
			}
			if (xPos>400 && yPos>450 && xPos<530 && yPos<475 && Game::isPause()==true){
				this->SetKey(VK_FINAL);
			}
			break;
		}
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

		this->Show(hdc);
		DeleteDC(hdc);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
		this->SetKey(VK_FINAL);
        break;
	case WM_ERASEBKGND:
		return 1;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}

LRESULT CALLBACK MainWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
  MainWindow* application=nullptr;

  if(message==WM_NCCREATE)
    application=(MainWindow*)lParam;
  else
    application=(MainWindow*)GetWindowLong(hWnd,GWL_USERDATA);

  return application->Message(hWnd,message,wParam,lParam);
}

/**
	Shows interface for windows desctop
*/
void MainWindow::Show(HDC& hdc){

	HDC hdcMem=CreateCompatibleDC(hdc);
	HDC hdcBuf=CreateCompatibleDC(hdc);
	HBITMAP tempBitmap=(HBITMAP) CopyImage(this->imageBackground,IMAGE_BITMAP,1000,800,LR_COPYFROMRESOURCE);
	HBITMAP hBitmapBuff = (HBITMAP) SelectObject(hdcBuf,tempBitmap);

	SelectObject(hdcMem, this->imageRoad);
	BitBlt(hdcBuf, 0, YSTARTOFFIELD+HEIGHTOFFIELD*16-3, 1000, 31, hdcMem, 0, 0, SRCCOPY);

	UINT yProvCoordForTargetSystem=1000;
	int size=Game::GetUnit()->size();

	for (int i=0;i<size;i++){
		Unit* tempUnits=Game::GetUnit()->at(i);

		HBITMAP* tempImage=nullptr;
		switch(tempUnits->GetName()){
			case UnitsType::AIRCRAFT:
				tempImage=&this->imageAirCraft;
				break;
			case UnitsType::BOMB:
				tempImage=&this->imageBombs;
				break;
			case UnitsType::ROCKET:
				tempImage=&this->imageRocket;
				break;
			case UnitsType::BUILDING:
		//TODO dynamic cast
				tempImage=&this->imageBuilding1;
				if (((PartOfBuilding*)tempUnits)->GetType()==BuildingType::BUILDING2) {
					tempImage=&this->imageBuilding1;
				}
				else if (((PartOfBuilding*)tempUnits)->GetType()==BuildingType::BUILDING3){
					tempImage=&this->imageBuilding2;
				}
				else {
					tempImage=&this->imageBuilding;
				}
				break;
			case UnitsType::ROOF:
				tempImage=&this->imageRoof;
				break;
			case UnitsType::FIRE:
				tempImage=&this->imageFire;
				break;
			case UnitsType::HELICOPTER:
				tempImage=&this->imageHelicopter;
				break;
		}
		//for visual set at road
		UINT yDelta=0;
		if (Game::GetUnit()->at(0)->GetCoorY()==HEIGHTOFFIELD && i==0){
			yDelta+=10;
		}
		/////////////////////

		SelectObject(hdcMem, *tempImage);
		TransparentBlit(hdcBuf,tempUnits->GetCoorX()*16+XSTARTOFFIELD, 
						tempUnits->GetCoorY()*16+YSTARTOFFIELD+yDelta,16,16, hdcMem, 0, 0,RGB(255,255,255));

		//magic image
		//TODO dynamic cast
		if ((tempUnits->GetName()==UnitsType::ROOF || tempUnits->GetName()==UnitsType::FIRE) && ((PartOfBuilding*)tempUnits)->isMagic()) {
			UINT ran=rand()%100;
			tempImage=&this->imageMagic1;
			if (ran<33){
				tempImage=&this->imageMagic2;
			}
			else if (ran<66){
				tempImage=&this->imageMagic3;
			}
			SelectObject(hdcMem, *tempImage);
			TransparentBlit(hdcBuf,tempUnits->GetCoorX()*16+XSTARTOFFIELD, 
						tempUnits->GetCoorY()*16+YSTARTOFFIELD,16,16, hdcMem, 0, 0,RGB(255,255,255));
		}
		///////////////////////////////////////
		//for targetting
		if (Game::GetTargetCount()>0) {
			if (typeid(*(tempUnits))==typeid(PartOfBuilding) && tempUnits->GetCoorX()==Game::GetUnit()->at(0)->GetCoorX()){
				if (yProvCoordForTargetSystem>tempUnits->GetCoorY()*16+YSTARTOFFIELD) {
					yProvCoordForTargetSystem=tempUnits->GetCoorY()*16+YSTARTOFFIELD;
				}
			}
		}
		//////////////////////////
	}

	SelectObject(hdcMem, this->imageRoad1);
	TransparentBlit(hdcBuf,0, YSTARTOFFIELD+HEIGHTOFFIELD*16-12, 1000, 20, hdcMem, 0, 0,RGB(255,255,255));

	//Target system
	if (yProvCoordForTargetSystem<1000){
		UINT xCoor=Game::GetUnit()->at(0)->GetCoorX()*16+XSTARTOFFIELD+8;
		UINT yCoor=Game::GetUnit()->at(0)->GetCoorY()*16+XSTARTOFFIELD+16;
	
		SelectObject(hdcBuf, GetStockObject(DC_PEN));
		SetDCPenColor(hdcBuf,RGB(255,0,0));

		MoveToEx(hdcBuf,xCoor,yCoor,NULL);
		LineTo(hdcBuf,xCoor,yProvCoordForTargetSystem);
	}
	//////////////////////////////
	//Labels
	SetBkMode(hdcBuf, TRANSPARENT);
	//Bomb marvel 
	if (Game::GetBombCount()>0) {
		SetTextColor(hdcBuf,RGB(255,0,0));
		TCHAR timer[MAX_LOADSTRING];
		_itow(Game::GetBombCount(),timer,10);

		TextOut(hdcBuf, 80, 5, timer, wcslen(timer));
	}
	TextOut(hdcBuf, 5, 5, labText[0], wcslen(labText[0]));
	TextOut(hdcBuf, 25, 25, this->bombs, wcslen(this->bombs));
	SetTextColor(hdcBuf,RGB(0,0,0));

	//Rocket marvel 
	if (Game::GetRocketCount()>0) {
		SetTextColor(hdcBuf,RGB(255,0,0));
		TCHAR timer[MAX_LOADSTRING];
		_itow(Game::GetRocketCount(),timer,10);

		TextOut(hdcBuf, 80, 50, timer, wcslen(timer));
	}
	TextOut(hdcBuf, 5, 50, labText[17], wcslen(labText[17]));
	TextOut(hdcBuf, 25, 75, this->rockets, wcslen(this->rockets));
	SetTextColor(hdcBuf,RGB(0,0,0));

	TextOut(hdcBuf, 400, 5, labText[1], wcslen(labText[1]));
	TextOut(hdcBuf, 420, 25, this->level, wcslen(this->level));

	TextOut(hdcBuf, 800, 5, labText[2], wcslen(labText[2]));
	TextOut(hdcBuf, 820, 25, this->score, wcslen(this->score));

	TextOut(hdcBuf, 400, 50, labText[16], wcslen(labText[16]));
	TextOut(hdcBuf, 420, 75, this->speed, wcslen(this->speed));
	//Target marvel label
	if (Game::GetTargetCount()>0) {
		TCHAR timer[MAX_LOADSTRING];
		_itow(Game::GetTargetCount(),timer,10);

		TextOut(hdcBuf, 800, 50, labText[18], wcslen(labText[18]));
		TextOut(hdcBuf, 820, 75, timer, wcslen(timer));
	}
	///////////////
	/////Flying text
	for (UINT i=0;i<flyingText.size();i++){
		FlyingText* tempText=flyingText.at(i);

		if (tempText->isDead()){
			delete tempText;
			flyingText.erase(flyingText.begin()+i);
			continue;
		}

		HFONT hFont=CreateFont(10,0,0,0,FW_BOLD,0,0,0,0,0,0,2,0,L"SYSTEM_FIXED_FONT");
		SetTextColor(hdcBuf,RGB(0,255,0));
		SelectObject(hdcBuf,hFont);
	
		TextOut(hdcBuf, tempText->GetX(), tempText->GetY(), tempText->GetLabel(), wcslen(tempText->GetLabel()));
		tempText->Fly();
	}
	///////////////////////////
	//Menu
	if (Game::isPause() || Game::isGameOver() || Game::isWin()){

		SelectObject(hdcMem, this->imageMenu);
		TransparentBlit(hdcBuf,250, 150, 500, 500, hdcMem, 0, 0,RGB(255,255,255));

		HFONT hFont=CreateFont(15,0,0,0,FW_BOLD,0,TRUE,0,0,0,0,2,0,L"SYSTEM_FIXED_FONT");
		SelectObject(hdcBuf,hFont);
//		SetTextColor(hdcBuf,RGB(255,255,255));

		TextOut(hdcBuf,558,189,VERSION,wcslen(VERSION));

		hFont=CreateFont(60,0,0,0,FW_BOLD,0,0,0,0,0,0,2,0,L"SYSTEM_FIXED_FONT");
		SetTextColor(hdcBuf,RGB(0,0,255));

		LPCWSTR text=labText[3];

		if (Game::isGameOver()){
			SetTextColor(hdcBuf,RGB(255,0,0));
			text=labText[4];
		}
		else if(Game::isWin()){
			SetTextColor(hdcBuf,RGB(0,255,0));
			text=labText[5];
		}
		SelectObject(hdcBuf,hFont);
		TextOut(hdcBuf,400,240,text,wcslen(text));

		hFont=CreateFont(40,0,0,0,FW_BOLD,0,0,0,0,0,0,2,0,L"SYSTEM_FIXED_FONT");
		SelectObject(hdcBuf,hFont);
		SetTextColor(hdcBuf,RGB(0,0,255));

		if (Game::isWin()!=true){
			TextOut(hdcBuf,400,340,labText[6],wcslen(labText[6]));
		}
		if (Game::isGameOver()!=true){
			TextOut(hdcBuf,400,395,labText[7],wcslen(labText[7]));
		}

		TextOut(hdcBuf,400,450,labText[8],wcslen(labText[8]));

		hFont=CreateFont(20,0,0,0,FW_BOLD,0,0,0,0,0,0,2,0,L"SYSTEM_FIXED_FONT");
		SelectObject(hdcBuf,hFont);
		SetTextColor(hdcBuf,RGB(0,0,0));

		UINT xText=280;
		UINT yText=510;

		TextOut(hdcBuf,xText,yText,labText[10],wcslen(labText[10]));
		TextOut(hdcBuf,xText,yText+30,labText[11],wcslen(labText[11]));
		TextOut(hdcBuf,xText,yText+60,labText[12],wcslen(labText[12]));
		TextOut(hdcBuf,xText,yText+90,labText[13],wcslen(labText[13]));
		xText=520;
		TextOut(hdcBuf,xText,yText,labText[9],wcslen(labText[9]));
		TextOut(hdcBuf,xText,yText+30,labText[19],wcslen(labText[19]));
		TextOut(hdcBuf,xText,yText+60,labText[14],wcslen(labText[14]));
		TextOut(hdcBuf,xText,yText+90,labText[15],wcslen(labText[15]));
	}
	////////////////////////////////

	SetBkMode(hdcBuf, OPAQUE);
	BitBlt(hdc, 0, 0, 1000, 800, hdcBuf, 0, 0, SRCCOPY);
	SelectObject(hdcBuf, hBitmapBuff);
	DeleteObject(hBitmapBuff);
	DeleteObject(tempBitmap);
	DeleteDC(hdcMem);
	DeleteDC(hdcBuf);
}

void MainWindow::TransparentBlit(HDC& hdc, int destX, int destY, int destWidth, int destHeight, 
					 HDC hdc2, int srcX, int srcY, UINT tranparency)
{
	unsigned char* pImageBits;
	unsigned char* pBackBits;
	BITMAPINFO bmBitmapInfo = {0};
	HBITMAP hBitmap, hBitmap2, hOldBitmap, hOldBitmap2;
	HDC compHDC;
	HDC compHDC2;
	
	// Fill in our BitmapInfo structure (we want a 24 bit image)
	bmBitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmBitmapInfo.bmiHeader.biCompression = BI_RGB;
	bmBitmapInfo.bmiHeader.biHeight = destHeight;
	bmBitmapInfo.bmiHeader.biWidth = destWidth;	
	bmBitmapInfo.bmiHeader.biBitCount = 24;
	bmBitmapInfo.bmiHeader.biClrUsed = 0;
	bmBitmapInfo.bmiHeader.biPlanes = 1;

	// Create 2 DIB Sections.  One for the Front Buffer and one for the BackBuffer
	hBitmap  = CreateDIBSection(hdc,  &bmBitmapInfo, DIB_RGB_COLORS,(void **)&pImageBits, 0,0);	
	hBitmap2  = CreateDIBSection(hdc,  &bmBitmapInfo, DIB_RGB_COLORS,(void **)&pBackBits, 0,0);

	// Create a compatible DC for the front buffer and Select our Dib Section into it
	compHDC = CreateCompatibleDC(hdc);
	hOldBitmap = (HBITMAP)SelectObject(compHDC, hBitmap);
	
	// Create a compatible DC for the back buffer and Select our Dib Section into it
	compHDC2 = CreateCompatibleDC(hdc2);
	hOldBitmap2 = (HBITMAP)SelectObject(compHDC2, hBitmap2);

	// Blit the front buffer to our compatible DC that will hold the destination bits
	BitBlt(compHDC, 0, 0, destWidth, destHeight, hdc, destX, destY, SRCCOPY);

	// Blit the back buffer to our compatible DC that will hold the source bits
	BitBlt(compHDC2, 0, 0, destWidth, destHeight, hdc2, srcX, srcY, SRCCOPY);

	// Loop through the 24 bit image (Times 3 for R G and B)
	for(int i = 0; i < destHeight * destWidth * 3; i += 3)
	{
		// Check if the current pixel being examined isn't the transparent color
		// Remember, the image bits are stored (Blue, Green, Red), not (Red, Green, Blue)
		// We use the system macros to abstract the R G B data
		if((pBackBits[i]   != GetBValue(tranparency)) || 
		   (pBackBits[i+1] != GetGValue(tranparency)) || 
		   (pBackBits[i+2] != GetRValue(tranparency)))
		{
			// Assign the desired pixel to the foreground
			pImageBits[i]     = pBackBits[i];
			pImageBits[i + 1] = pBackBits[i + 1];
			pImageBits[i + 2] = pBackBits[i + 2];
		}
	}  

	
	// Blit the transparent image to the front buffer (Voila!)
	BitBlt(hdc, destX, destY, destWidth, destHeight, compHDC, 0, 0, SRCCOPY);

	// Cleanup the monochrome bitmaps
	SelectObject(compHDC, hOldBitmap);
	SelectObject(compHDC2, hOldBitmap2);	

	// Free GDI Resources
	DeleteObject(hBitmap);
	DeleteObject(hBitmap2);

	DeleteDC(compHDC);
	DeleteDC(compHDC2);
}
