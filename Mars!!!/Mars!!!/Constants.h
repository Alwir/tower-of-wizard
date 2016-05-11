#pragma once
#include "bass.h"

#define VERSION L"v0.9"

#define WIDTHOFFIELD 50
#define HEIGHTOFFIELD 30

#define XSTARTOFFIELD 100
#define YSTARTOFFIELD 100

#define MAX_LOADSTRING 100
#define DEFAULTHEIGHT 500
#define DEFAULTWIDTH 100

#define CHANSEOFROOF 25

#define SPEEDOFBOMB 70
#define SPEEDOFAIRCRAFT 200
#define MAXSPEEDAIRCRAFT 30
#define MINSPEEDAIRCRAFT 300

#define LABELCOUNT 20

#define TIMEOFLIFEHELICOPTER 50
#define SPEEDOFHELICOPTER 500
#define SCOREFORHELICOPTER 500
#define TIMEFORHELICOPTER 60

#define BOMBNOISE IDR_WAVE1
#define EXPLOSIONNOISE IDR_WAVE2
#define ROCKETNOISE IDR_WAVE3

#define FLYINGTEXTLIVE 100

enum UnitsType {
	AIRCRAFT,
	BOMB,
	BUILDING,
	ROOF,
	FIRE,
	ROCKET,
	HELICOPTER
};

enum BuildingType {
	BUILDING1,
	BUILDING2,
	BUILDING3,
	ROOF1
};

enum Timers {
	TIMERAIRCRAFT,
	TIMERBOMB,
	TIMERHELICOPTER,
	TIMERSECONDS,
	TIMERMARVEL
};

static HSTREAM MakeSound(unsigned int name){
	HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(name), L"WAVE");
	if (hRes!=NULL) {
		DWORD dwSize = SizeofResource (NULL, hRes);
		HGLOBAL hLoad = LoadResource(NULL, hRes);

		HSTREAM sound=BASS_StreamCreateFile(TRUE, LockResource(hLoad), 0, dwSize, BASS_STREAM_AUTOFREE);
		BASS_ChannelPlay(sound,TRUE);
		return sound;
	}
	return NULL;
}

static TCHAR* GetLocalText(UINT resNumber){
	if (GetUserDefaultUILanguage()!=LANG_RUSSIAN+1024) {
		resNumber+=100;
	}
	TCHAR* tempText=new TCHAR[MAX_LOADSTRING];
	LoadString(NULL, resNumber, tempText, MAX_LOADSTRING);

	return tempText;
}