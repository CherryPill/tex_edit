/*
		COPYRIGHT (c) ROMAN RATASHNIUK 2015-2016

*/
#define ISOLATION_AWARE_ENABLED 1
#define _UNICODE
#include <windows.h>
#include <Richedit.h>
#include "translations.h"
#include "resource1.h"
#include "mainPrefs.h"
#include "stdincld.h"
#include "globalVars.h"

//APP DEFINED MENU IDS
#include "menuids.h"
#include "editcontrol.h"
#include "appconst.h"

#include "mainWindowProc.h"

#include "splashScreen.h"

#include "toolbarControl.h"
//default env vals

#include "service.h"
#include "contextMenu.h"
#include "systemCheck.h"
#include "recentFiles.h"
//extern MAINPREFS settings;
WPARAM posX, posY;
WPARAM mainWidth, mainHeight;

void setEnvVars(int _mainWidth=wpInitWidth, int _mainHeight=wpInitHeight,
 int _posX=wpInitPosX, int _posY=wpInitPosY)
{
	mainWidth = _mainWidth;
	mainHeight = _mainHeight;
	posX = _posX;
	posY = _posY;

	currentWidth = mainWidth;
	currentHeight = mainHeight;

	currentPosX = posX;
	currentPosY = posY;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	//if (!chkComCtlVersion())
	{
		//MessageBox(NULL,errorMessages_ENG[0],_T("Error"),MB_ICONERROR);
		//return 0;
	}

	//loadAppSmIcon();
	if (binary::chkIfConfigExists())
	{
		binary::loadMainPrefs();
	}
	else
	{
		binary::setDefaultPrefs();	
		binary::saveMainPrefs();
	}
	binary::loadMainPrefs();
	manualOverride::saveMainPrefs(); //not done yet
	OPENMODE = 1; // 1 - text, 2 - rtf
	//HWND hwnd = NULL;
	if (settings.bRememberLastSizeByUser)
	{ 
		//loading usr specified parameters
		setEnvVars(settings.iUsrLastWidth, settings.iUsrLastHeight, settings.iUsrLastXPos, settings.iUsrLastYPos);
	}
	else
	{
		//going with default values for width height posx and posy
		setEnvVars();
	}
	//NO MENU FILLING ON STARTUP PLS
	if (chkIfRecentFilesExists())
	{
		loadRecentFiles();
		bRecentFilesExist = true;
	}
	currRecentAddStart = IDM_REC_CLEAR + 1;
	//setDefaultPrefs(); //for now
	MSG message;
	WNDCLASSEX wc = {0}; //nullifying the struct
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszClassName = szAppClass;
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	

	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = mainWindowProcedure;
	//wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hCursor = plainCursor;
	//wc.hIconSm = LoadIcon(NULL, IDI_ASTERISK);
	mainAppIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_MAINAPPICON), IMAGE_ICON, 0, 0, NULL);
	appSetsIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_APPSETSICON), IMAGE_ICON, 0, 0, NULL);
	wc.hIconSm = mainAppIcon;
	wc.hIcon = mainAppIcon;
	//wc.hIconSm = (HICON)LoadImage(ghInstance,_T("texEditIcon32x32.ico"),IMAGE_ICON,32,32,LR_LOADFROMFILE);
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, _T("Window class registration failed"), _T("Error"), MB_ICONERROR);
		return false;
	}
	ghInstance = hInstance;
	hwnd = CreateWindowEx
	(
		0,
		wc.lpszClassName,
		szAppName,
		WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN,
		currentPosX,
		currentPosY,
		currentWidth,
		currentHeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	//MessageBox(hwnd, commDlg[1], commDlgMsgWarnInfoCaptions_EN[0], MB_YESNO | MB_ICONINFORMATION);
	while (GetMessage(&message, NULL, 0, 0))
	{
		//process msg here if needed
		//if (!IsDialogMessage(findDlg, &message))
		//{
			if (message.message == WM_RBUTTONDOWN)
			{
				createContextMenu(hwnd, message.lParam);
			}
			TranslateMessage(&message);
			DispatchMessage(&message);
		//}
	
	}
	return (int)(message.wParam);
	//return 0;
}