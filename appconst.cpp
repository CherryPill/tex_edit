#include <windows.h>
#include <tchar.h>
#include <string>
#include "appconst.h"
#include "translations.h"
HICON mainAppIcon = NULL;
HICON appSetsIcon = NULL;
TCHAR *szAppName = _T("TexEdit");
TCHAR *szConfigPath = _T("config.dat");
TCHAR *szRecentFilesPath = _T("D:\\recs.txt");
TCHAR *szConfigManualPath = _T("configManual.txt");
TCHAR *rtfExt = _T(".rtf");
TCHAR *txtExt = _T(".txt");
TCHAR *szAppClass = szAppName;
TCHAR *settingsDialogCaption = _T("TexEdit - Settings");
//TCHAR *settingsDialogCaption = settingsTextWindowTitle_JP; test
//initial window size (default)
WPARAM splashScreenWidth = 350;
WPARAM splashScreenHeight = 350;
WPARAM wpInitWidth{ 700 }; 
WPARAM wpInitHeight{ 500 };
WPARAM screenWidth = GetSystemMetrics(SM_CXSCREEN);
WPARAM screenHeight = GetSystemMetrics(SM_CYSCREEN);
//default centering using default coords for height and width
WPARAM wpInitPosX = screenWidth / 2 - (wpInitWidth / 2);
WPARAM wpInitPosY = screenHeight / 2 - (wpInitWidth / 2);

WPARAM currentWidth = 0;
WPARAM currentHeight = 0;

WPARAM currentPosX = 0;
WPARAM currentPosY = 0;


WPARAM settingsDialogBoxWidth = 450;
WPARAM settingsDialogBoxHeight = 600;

int recentDocsListMax = 10; //inactive
int toolbarOffset = 0; //inactive

//1:1 ratio
WPARAM zoomRatio_e = 10; //initial, this value gets incremented and decremented
WPARAM zoomRatio_d = 10;