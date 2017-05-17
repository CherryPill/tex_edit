#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <winternl.h>
#include "appconst.h"
#ifndef MAINPREFS_H
#define MAINPREFS_H



namespace binary
{
	void loadMainPrefs(void);
	void saveMainPrefs(void);
	void setDefaultPrefs(void);
	bool chkIfConfigExists(void);
	void updatePrefs(void);
}
namespace manualOverride
{
	void loadMainPrefs(void);
	void saveMainPrefs(void);
	void setDefaultPrefs(void);
	bool chkIfConfigExists(void);
	void updatePrefs(void);
	void parseTxtPrefs(void);
	void populateValArray(void);
}



struct MAINPREFS
{
	bool bConfirmExit;
	bool bShowCompleteFilePathInTitle; //default true
	//bool detectURLS;
	bool bFirstLaunch; //not actually a setting that user can toggle used in-app
	bool bSplashScreen;
	bool bToolbarActive; //default 1
	bool bToolbarText;
	bool bDetectLinks;
	bool bStartFullScr;
	//bool bShowLoadedFileInTitle; //default true
	//int iLang; //default 1 - eng
	//TCHAR szFontFamily[257]; //default Arial
	//int iFontSize; //default 11
	//int iZoom; //default 100
	//bool bLastSizeByUser; //true if changed, false otherwise default 0
	bool bRememberLastSizeByUser; //default 1
	int iUsrLastWidth; //default 500
	int iUsrLastHeight; //default 400
	int iUsrLastXPos; //default center
	int iUsrLastYPos; //default center
	bool bOverrideSettings;
	//in-app setting, usr can only clear at runtime
};


extern MAINPREFS settings;
extern std::string overrideTxtArray[mainPrefsMax];
extern unsigned int overrideValArray[mainPrefsMax];

#endif