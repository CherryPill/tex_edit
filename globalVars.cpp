#include <Windows.h>
#include <CommCtrl.h>
#include <tchar.h>
#include <cstdlib>
#include <cstring>
#include "globalVars.h"

TCHAR *currentVersion = _T("0.5");
TCHAR *appInfo = _T("texEdit is built with C++ and WinAPI");
int currRecentAddStart = 0; //changed when recent config file is loaded
bool fileLoaded = false;
bool fileSaved = false;
bool fileChanged = false;
HINSTANCE ghInstance = NULL;	
HMENU menuBar = NULL;
HMENU menuEntry = NULL;
HMENU subMenuFiles = NULL;
HMENU subMenuRecent = NULL;
HMENU subMenuTime = NULL;
HMENU subMenuDate = NULL;
HWND richEditControl = NULL;
HWND statusBar = NULL;
HWND toolBar = NULL;
DWORD toolbarStyle = BTNS_AUTOSIZE;
HIMAGELIST toolbarImages = NULL;
HIMAGELIST comboImages = NULL;
HWND combo = NULL;





HWND settingsDialog = NULL;
HWND hwnd = NULL; //main window app handle


HWND chkBox_WinPosDimsRemember = NULL;
HWND chkBox_ToggleLastSession = NULL;
HWND chkBox_ToggleSplashScreen = NULL;

HWND chkBox_ToggleInitialZoom = NULL;
HWND chkBox_ExitConfirm = NULL;
HWND chkBox_ToggleFullPath = NULL;
HWND chkBox_ToggleToolbar = NULL;
HWND chkBox_ToggleRecentDuplicates = NULL;
HWND chkBox_ToggleRecentOnlyShort = NULL;
HWND chkBox_ToggleToolbarText = NULL;
HWND chkBox_TogglebDetectLinks = NULL;
HWND chkBox_ToggleStatusBar = NULL;
HWND chkBox_ToggleStatusLineNum = NULL;
HWND chkBox_ToggleStatusTextLen = NULL;
HWND chkBox_ToggleStatusZoom = NULL;

HWND dialogOKButton = NULL;
HWND dialogCancelButton = NULL;


bool justifyLeftEnabled = false;
bool justifyRightEnabled = false;
bool justifyCenterEnabled = false;
bool styleBoldEnabled = false;
bool styleItalicEnabled = false;
bool styleUnderlinedEnabled = false;

bool bRecentFilesExist = false;
WORD tempStyle = 0;

HWND findDlg = NULL;

HWND radioButtonLangUSA = NULL;
HWND radioButtonLangRU = NULL;
HWND radioButtonLangJP = NULL;

HWND placeHolderUSA = NULL;
HWND placeHolderRU = NULL;
HWND placeHolderJP = NULL;

HICON staticImageUSA_active = NULL;
HICON staticImageUSA_inactive = NULL;

HICON staticImageRU_active = NULL;
HICON staticImageRU_inactive = NULL;

HICON staticImageJP_active = NULL;
HICON staticImageJP_inactive = NULL;

HICON staticImageSave = NULL;
HICON staticImageCancel = NULL;

TCHAR fontFamily[32];
TCHAR currentlyOpenedFile[257];
UINT uFindReplaceMsg = RegisterWindowMessage(FINDMSGSTRING);

WNDPROC lpEditWndProc;
WNDPROC lpSplashWndProc;
HWND toolTip = NULL;
HWND splashScreen = NULL;
int OPENMODE; //1 text, 2 - .rtf
TCHAR *SplashWndClass = _T("Splash Window");
//file status
TCHAR *titleBarStatus[] = {
					_T("Untitled.txt - TexEdit"), 
	
					_T("Untitled.rtf - TexEdit")
};
TCHAR *titleBarStatus_RU[]
{
					_T("Безымянный.txt - TexEdit"), 
	
					_T("Безымянный.rtf - TexEdit")
};
TCHAR *titleBarStatus_JP[]
{
					_T("無名.txt - TexEdit"),

					_T("無名.rtf - TexEdit")

};
PARAFORMAT formatStruct;
MENUITEMINFO menuState;
MENUITEMINFO contextMenuState;
TCHAR *OSList[7] = {

	_T("Windows Xp"),
	_T("Windows Vista"),
	_T("Windows 7"),
	_T("Windows 8"),
	_T("Windows 8.1"),
	_T("Windows 10"),
	_T("Windows X")
};
unsigned int uiVecIndex_recents = 0;
unsigned int uiMenuIndex_recents = 0;

unsigned int uiRemainingEntries_recents = 0;


HCURSOR plainCursor = LoadCursor(NULL,IDC_ARROW);
HCURSOR busyCursor = LoadCursor(NULL,IDC_WAIT);

UINT64 richEditCurrOffset = 0;

HWND dialogTabControl = NULL;

WPARAM currentZoomNumerator = 0;