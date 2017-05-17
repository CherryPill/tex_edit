#include <windows.h>
#include <fstream>
#include <tchar.h>
#include <string>
#include "mainPrefs.h"
#include "appconst.h"
MAINPREFS settings;

unsigned int overrideValArray[mainPrefsMax];
std::string overrideTxtArray[mainPrefsMax] = 
{
	"bConfirmExit=",
	"\nbShowCompleteFilePathInTitle=",
	"\nbFirstLaunch=",
	"\nbSplashScreen=",
	"\nbToolbarActive=",
	"\nbToolbarText=",
	"\nbDetectLinks=",
	"\nbStartFullScr=",
	"\nbRememberLastSizeByUser=",
	"\niUsrLastWidth=",
	"\niUsrLastHeight=",
	"\niUsrLastXPos=",
	"\niUsrLastYPos=",
	"\nbOverrideSettings="
};

bool binary::chkIfConfigExists(void)
{
	bool fileGood = true;
	std::ifstream configFile(szConfigPath);
	if (!configFile)
	{
		MessageBox
		(
			NULL,
			_T("Configuration file is missing\nIt will be recreated"),
			_T("Error"),
			MB_ICONERROR | MB_OK
			);
	fileGood = false;
	}
	return fileGood;
}
void binary::loadMainPrefs(void)
{
	//load from binary into struct
	std::ifstream configFile;
	configFile.std::ifstream::open(szConfigPath, std::ios::binary
		| std::ios::in);
	configFile.std::ifstream::read((char*)&settings, sizeof(MAINPREFS));
	configFile.std::ifstream::close();
}
void binary::saveMainPrefs(void)
{
	//save to binary from struct
	std::ofstream configFile;
	configFile.std::ofstream::open(szConfigPath,std::ios::binary|std::ios::out);
	configFile.std::ofstream::write((char*)&settings,sizeof(MAINPREFS));
	configFile.std::ofstream::close();
}
void binary::setDefaultPrefs(void)
{
	settings.bConfirmExit = true;
	settings.bShowCompleteFilePathInTitle = true; //default 1
	settings.bFirstLaunch = true;
	settings.bSplashScreen = true;
	settings.bStartFullScr = false;
	//headers
	settings.bToolbarActive = true; //default 1
	settings.bToolbarText = true;
	
	//settings.iLang = 1; //default 1 - eng
	//_tcscpy(settings.szFontFamily,_T("Arial"));
	//settings.iFontSize = 11; //default 11
	//settings.iZoom = 100; //default 100
	//settings.bLastSizeByUser = false; //true if changed, false otherwise default 0
	settings.bRememberLastSizeByUser = false; //default false
	settings.iUsrLastWidth = wpInitWidth; //default 700
	settings.iUsrLastHeight = wpInitHeight; //default 400
	settings.iUsrLastXPos = wpInitPosX; //default center
	settings.iUsrLastYPos = wpInitPosY; //default center
	settings.bDetectLinks = false; //default false
	settings.bOverrideSettings = false;
	//cutoff app in
}


void binary::updatePrefs(void)
{
	//update preferences when the program is running

}
void manualOverride::loadMainPrefs(void)
{


}
void manualOverride::saveMainPrefs(void)
{
	populateValArray(); //filing array with the current values in the mainprefs struct
	std::ofstream txtOverride(szConfigManualPath,std::ios::out);
	for (register auto x = 0;x<mainPrefsMax;x++)
	{
		txtOverride<<overrideTxtArray[x]<<overrideValArray[x];//setting=value pair
	}
}
void manualOverride::setDefaultPrefs(void)
{
	

}
bool manualOverride::chkIfConfigExists(void)
{
	
	return 0;
}
void manualOverride::updatePrefs(void)
{


}
void manualOverride::parseTxtPrefs(void)
{


}
void manualOverride::populateValArray(void)
{
	overrideValArray[0] = settings.bConfirmExit;
	overrideValArray[1] = settings.bShowCompleteFilePathInTitle;
	overrideValArray[2] = settings.bFirstLaunch;
	overrideValArray[3] = settings.bSplashScreen;
	overrideValArray[4] = settings.bToolbarActive;
	overrideValArray[5] = settings.bToolbarText;
	overrideValArray[6] = settings.bDetectLinks;
	overrideValArray[7] = settings.bStartFullScr;
	overrideValArray[8] = settings.bRememberLastSizeByUser;
	overrideValArray[9] = settings.iUsrLastWidth;
	overrideValArray[10] = settings.iUsrLastHeight;
	overrideValArray[11] = settings.iUsrLastXPos;
	overrideValArray[12] = settings.iUsrLastYPos;
	overrideValArray[13] = settings.bOverrideSettings;
}