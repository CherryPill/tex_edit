#include <windows.h>
#include <CommCtrl.h>
#include <Richedit.h>
#include <tchar.h>
#ifndef GLOBALVARS
#define GLOBALVARS

extern int currRecentAddStart; //starting position in the recent docs list for adding a new path
extern TCHAR *currentVersion;
extern TCHAR *appInfo;
extern HINSTANCE ghInstance;
extern HMENU menuBar;
extern HMENU menuEntry;
extern HMENU subMenuFiles;
extern HMENU subMenuRecent;
extern HMENU subMenuTime;
extern HMENU subMenuDate;
extern HWND richEditControl;
extern HWND statusBar;
extern HWND toolBar;
extern HWND settingsDialog;
extern HIMAGELIST toolbarImages;
extern HIMAGELIST comboImages;
extern HWND combo;
extern DWORD toolbarStyle;



extern TCHAR currentlyOpenedFile[257];


extern HWND radioButtonLangUSA;
extern HWND radioButtonLangRU;
extern HWND radioButtonLangRU;

extern HICON staticImageUSA_active;
extern HICON staticImageUSA_inactive;

extern HICON staticImageRU_active;
extern HICON staticImageRU_inactive;

extern HICON staticImageJP_active;
extern HICON staticImageJP_inactive;

extern HWND placeHolderUSA;
extern HWND placeHolderRU;
extern HWND placeHolderJP;

extern HWND hwnd;
extern bool fileLoaded;
extern bool fileSaved;
extern bool fileChanged;
//settings dialog box controls

//static HWND chkBox_WinPosDimsRemember;
extern HWND splashScreen;
extern HWND chkBox_WinPosDimsRemember;
extern HWND chkBox_ToggleLastSession;
extern HWND chkBox_ToggleSplashScreen;

extern HWND chkBox_ToggleInitialZoom;
extern HWND chkBox_ExitConfirm;

extern HWND chkBox_ToggleFullPath;
extern HWND chkBox_ToggleToolbar;
extern HWND chkBox_ToggleStatusBar;
extern HWND chkBox_ToggleStatusLineNum;
extern HWND chkBox_ToggleStatusTextLen;
extern HWND chkBox_ToggleStatusZoom;
extern HWND chkBox_ToggleRecentDuplicates;
extern HWND chkBox_ToggleRecentOnlyShort;
extern HWND chkBox_ToggleToolbarText;

extern HWND chkBox_TogglebDetectLinks;

extern HWND dialogOKButton;
extern HWND dialogCancelButton;

extern HWND dialogTabControl;

extern bool justifyLeftEnabled;
extern bool justifyRightEnabled;
extern bool justifyCenterEnabled;
extern bool styleBoldEnabled;
extern bool styleItalicEnabled;
extern bool styleUnderlinedEnabled;
extern bool bRecentFilesExist;
extern WORD tempStyle;
extern HWND findDlg;



//essential formatting

extern TCHAR fontFamily[32];
extern UINT uFindReplaceMsg;

extern WNDPROC lpEditWndProc;
extern WNDPROC lpSplashWndProc;

extern int OPENMODE; //1 text, 2 - .rtf


extern HWND toolTip;
extern TCHAR *SplashWndClass;

extern TCHAR *titleBarStatus[];
extern TCHAR *titleBarStatus_RU[];
extern TCHAR *titleBarStatus_JP[];


extern PARAFORMAT formatStruct;
extern MENUITEMINFO menuState;
extern MENUITEMINFO contextMenuState;
extern TCHAR *OSList[7];



extern unsigned int uiVecIndex_recents;
extern unsigned int uiMenuIndex_recents;

extern unsigned int uiRemainingEntries_recents;

extern HCURSOR plainCursor;
extern HCURSOR busyCursor;

extern UINT64 richEditCurrOffset;

extern WPARAM currentZoomNumerator;
extern HICON staticImageSave;
extern HICON staticImageCancel;

#endif