#include <windows.h>
#include <tchar.h>
#include <string>
#include <atlstr.h>
#include "systemCheck.h"
#include "mainPrefs.h"
#include "globalVars.h"
#include "menuids.h"
#include "editcontrol.h"
#include "chkModule.h"
#include "recentFiles.h"
#include "timeDate.h"
#include "translations.h"
void createMainMenu(HWND mainWindow)
{

	UINT STYLE_FLAG;
	UINT MF_STYLE_POPUP;
	if (!chkIfFileLoaded())
	{
		STYLE_FLAG = MF_GRAYED;
	}
	else
	{
		STYLE_FLAG = MF_STRING;
	}
	if (currRecentAddStart==IDM_REC_CLEAR)
	{
		MF_STYLE_POPUP = MF_GRAYED | MF_POPUP;
	}
	else
	{
		MF_STYLE_POPUP = MF_STRING|MF_POPUP;
	}
	menuBar = NULL;
	menuEntry = NULL;
	menuBar = CreateMenu();
	menuEntry = CreateMenu();
	subMenuFiles = CreatePopupMenu();
	subMenuRecent = CreatePopupMenu();
	subMenuTime = CreatePopupMenu();
	subMenuDate = CreatePopupMenu();
	AppendMenu(menuBar, MF_POPUP, (UINT_PTR)menuEntry, _T("&File"));
	AppendMenu(menuEntry, MF_STRING, IDM_FILE_OPEN, _T("&Open...\tCtrl+O"));
	//AppendMenu(menuEntry, MF_STRING, IDM_FILE_NEW, _T("&New...\tCtrl+N"));
	AppendMenu(menuEntry, MF_STRING|MF_POPUP,(UINT_PTR)subMenuFiles, _T("&New...\tCtrl+N"));
	AppendMenu(subMenuFiles, MF_STRING, IDM_FILE_NEW_TXT, _T("&a new .txt document")); //initiate respective openmodes
	AppendMenu(subMenuFiles, MF_STRING, IDM_FILE_NEW_RTF, _T("&a new .rtf document"));


	AppendMenu(menuEntry, MF_STRING, IDM_FILE_SAVE, _T("&Save...\t Ctrl+S"));
	AppendMenu(menuEntry, MF_STRING, IDM_FILE_SAVE_AS, _T("&Save As..."));
	AppendMenu(menuEntry, MF_STRING, IDM_FILE_PRINT, _T("&Print\tCtrl+P"));

	AppendMenu(menuEntry, MF_STRING|MF_POPUP, (UINT_PTR)subMenuRecent, _T("Recently opened files"));
	
	AppendMenu(subMenuRecent, MF_STRING, IDM_REC_CLEAR, _T("Clear list"));
	AppendMenu(subMenuRecent,MF_SEPARATOR,NULL,NULL);
	if (bRecentFilesExist)
	{
		recentDocsList_fill_gui();
	}
	else
	{
		disableRecentMenuItem();
	}
	//if (currRecentAddStart != IDM_REC_CLEAR)
	//{
	//	recentDocsList_fill_gui();
	//}
	//recentDocsList_fill_gui(recentStartingLabelID);






	AppendMenu(menuEntry, MF_SEPARATOR, NULL, NULL);
	AppendMenu(menuEntry, MF_STRING, IDM_FILE_EXIT, _T("&Exit"));
	//cutoff pnt
	menuEntry = CreateMenu();
	AppendMenu(menuBar, MF_POPUP, (UINT_PTR)menuEntry, _T("&Edit"));
	AppendMenu(menuEntry, MF_STRING, IDM_EDIT_UNDO, _T("&Undo...\tCtrl+Z"));
	AppendMenu(menuEntry, MF_SEPARATOR, NULL, NULL);
	AppendMenu(menuEntry, MF_STRING, IDM_EDIT_COPY, _T("&Copy...\tCtrl+C"));
	AppendMenu(menuEntry, MF_STRING, IDM_EDIT_PASTE, _T("&Paste...\tCtrl+V"));
	AppendMenu(menuEntry, MF_STRING, IDM_EDIT_DELETE, _T("&Cut...\tCtrl+X"));
	AppendMenu(menuEntry, MF_SEPARATOR, NULL, NULL);
	AppendMenu(menuEntry, MF_STRING, IDM_EDIT_FIND, _T("&Find\tCtrl+F"));
	AppendMenu(menuEntry, MF_STRING, IDM_EDIT_REPLACE, _T("&Replace\tCtrl+H"));
	AppendMenu(menuEntry, MF_SEPARATOR, NULL, NULL);

	AppendMenu(menuEntry, MF_STRING, IDM_EDIT_PREFERENCES, _T("&Preferences...\tCtrl+J"));



	menuEntry = CreateMenu();

	AppendMenu(menuBar, MF_POPUP, (UINT_PTR)menuEntry, _T("&Format"));

	AppendMenu(menuEntry, MF_GRAYED, NULL, _T("Alignment"));
	AppendMenu(menuEntry, MF_SEPARATOR, NULL, NULL);

	AppendMenu(menuEntry, MF_STRING, IDM_JUSTIFY_RIGHT, _T("&Right"));
	AppendMenu(menuEntry, MF_STRING, IDM_JUSTIFY_CENTER, _T("&Center"));
	AppendMenu(menuEntry, MF_STRING, IDM_JUSTIFY_LEFT, _T("&Left"));
	AppendMenu(menuEntry, MF_SEPARATOR, NULL, NULL);
	AppendMenu(menuEntry, MF_GRAYED, NULL, _T("Style"));
	AppendMenu(menuEntry, MF_SEPARATOR, NULL, NULL);

	AppendMenu(menuEntry, MF_STRING, IDM_STYLE_BOLD, _T("&Bold"));
	AppendMenu(menuEntry, MF_STRING, IDM_STYLE_ITALIC, _T("&Italic"));
	AppendMenu(menuEntry, MF_STRING, IDM_STYLE_UNDERLINED, _T("&Underlined"));
	AppendMenu(menuEntry, MF_SEPARATOR, NULL, NULL);
	AppendMenu(menuEntry, MF_STRING, IDM_STYLE_COLOR, _T("&Color"));
	AppendMenu(menuEntry, MF_STRING, IDM_STYLE_FONT, _T("&Font"));
	AppendMenu(menuEntry, MF_SEPARATOR, NULL, NULL);

	//cutoff pnt
	menuEntry = CreateMenu();
	AppendMenu(menuBar, MF_POPUP, (UINT_PTR)menuEntry, _T("&Insert"));
	AppendMenu(menuEntry, MF_STRING, IDM_INS_PIC, _T("&Image..."));
	AppendMenu(menuEntry, MF_STRING|MF_POPUP, (UINT_PTR)subMenuDate, _T("&Current date..."));
	AppendMenu(menuEntry, MF_STRING|MF_POPUP,(UINT_PTR)subMenuTime, _T("&Current time..."));
	AppendMenu(subMenuTime, MF_STRING,IDT_TIME_US,timeStrings_EN[0]);
	AppendMenu(subMenuTime, MF_STRING, IDT_TIME_MILITARY, timeStrings_EN[1]);

	AppendMenu(subMenuDate,MF_STRING,IDT_DATE_US, dateStrings_EN[0]);
	AppendMenu(subMenuDate, MF_STRING, IDT_DATE_EUR, dateStrings_EN[1]);
	AppendMenu(subMenuDate, MF_STRING, IDT_DATE_ISO, dateStrings_EN[2]);
	//cutoff pnt
	menuEntry = CreateMenu();
	//chk ver here
	TCHAR *winVer = chkWinVer();
	TCHAR gibsMeDat[257];
	_tcscpy(gibsMeDat,currentVersion);
	_tcscat(gibsMeDat,_T(" running on "));
	_tcscat(gibsMeDat,winVer);

		
	//AppendMenu(menuEntry, MF_STRING, IDM_ABOUT_ABOUT, gibsMeDat);
	AppendMenu(menuEntry, MF_STRING, IDM_ABOUT_ABOUT, _T("About this program..."));

	AppendMenu(menuBar, MF_POPUP, (UINT_PTR)menuEntry, _T("&About"));
	SetMenu(mainWindow, menuBar);
	menuState.fType = MFT_RADIOCHECK;

}
void styleMenuItems(void)
{
	//not used
	MENUINFO menuStyleStruct;
	HBRUSH color = NULL;
	color = CreateSolidBrush(RGB(216,0,115));
	menuStyleStruct.cbSize = sizeof(MENUINFO);
	menuStyleStruct.fMask = MIM_BACKGROUND;
	menuStyleStruct.hbrBack = color;
	SetMenuInfo(menuEntry,(LPCMENUINFO)&menuStyleStruct);
	}