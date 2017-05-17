#include <Windows.h>
#include "appconst.h"
#include "globalVars.h"
#include "nonMenuids.h"
#include "inputLangChange.h"
#include "statusControl.h"
#include  "resource1.h"
#include <commctrl.h>
TCHAR *statusControlMessages[] =
{ 
					_T("Ready"),
					_T("File loaded"),
					_T("File saved"),
					_T("File quick saved"),
					_T("File not saved"),
					_T("Snoozing...")
};
void createStatusControl(HWND mainWindow)
{
	TCHAR lang[129];
	staticImageUSA_active = (HICON)LoadImage(ghInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, LR_VGACOLOR);
	staticImageRU_active = (HICON)LoadImage(ghInstance, MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 16, 16, LR_VGACOLOR);
	RECT windowDims;
	int msgPartPosX,langPartPosX,linePartPosX,wordsPartPosX,charsPartPosX;
	GetClientRect(mainWindow,&windowDims);
	msgPartPosX = 100;
	langPartPosX = windowDims.right/2;
	//linePartPosX = windowDims.right-80;
	linePartPosX = langPartPosX + 100;
	wordsPartPosX = linePartPosX + 100;
	charsPartPosX = wordsPartPosX + 100;
	statusBar = CreateWindowEx
		(
		0, 
		STATUSCLASSNAME, 
		NULL,
		WS_CHILD | 
		WS_VISIBLE|
		SBARS_SIZEGRIP,
		0, 0, 20, 50,
		mainWindow, (HMENU)IDC_STATUS_BAR, GetModuleHandle(NULL), NULL);
	//int statwidths[] = {msgPartPosX,langPartPosX,linePartPosX,-1};
	int statwidths[] = { msgPartPosX,langPartPosX,linePartPosX,wordsPartPosX,charsPartPosX,-1 };
	//int statwidths[] = {80, -1}; //fallback, only RDY
	SendMessage(statusBar, SB_SETPARTS, sizeof(statwidths) / sizeof(int), (LPARAM)statwidths);
	SendMessage(statusBar, SB_SETTEXT, 0|0, (LPARAM)statusControlMessages[0]);
	SendMessage(statusBar, SB_SETTEXT, 1 | 0, (LPARAM)_T("Zoom: 100%"));

	//SendMessage(statusBar, SB_SETTEXT, 2|0, (LPARAM)_T("English (U.S.)")); //debug
	changeLangStatBar();
	//SendMessage(statusBar, SB_SETTEXT, 3|0, (LPARAM)_T("Line: 145"));
	SendMessage(statusBar, SB_SETTEXT, 3|0, (LPARAM)_T("Line: 1"));
	//SendMessage(statusBar, SB_SETTEXT, 4|0, (LPARAM)_T("Words: 666"));
	SendMessage(statusBar, SB_SETTEXT, 5|0, (LPARAM)_T("Chars: 0"));
	
	//index is missing because the adjacent empty space is considered a part for w/e reason
}
void resizeStatusControl(void)
{
	SendMessage(statusBar, WM_SIZE, 0, 0);
	SendMessage(toolBar,TB_AUTOSIZE, 0, 0);

	RECT statusDims;
	RECT mainWindowDims;
	RECT toolbarDims;

	GetWindowRect(statusBar, &statusDims);
	GetWindowRect(toolBar, &toolbarDims);
	GetClientRect(hwnd, &mainWindowDims);
	int toolbarHeight = toolbarDims.bottom - toolbarDims.top;
	int statusbarHeight = statusDims.bottom - statusDims.top;
	int richEditHeight = mainWindowDims.bottom - toolbarHeight - statusbarHeight;

	SetWindowPos(richEditControl, NULL, 0, toolbarHeight, mainWindowDims.right, richEditHeight, SWP_NOZORDER);
}
//todo make static text into separate toolbar parts to avoid memory hogging
//10% increment
void changeZoomPartText(void)
{
	TCHAR value[16];
	TCHAR text[8];
	TCHAR complete[48];
	ZeroMemory(&complete, sizeof(value));
	ZeroMemory(&value, sizeof(value));
	ZeroMemory(&text,sizeof(text));
	double newRatio = ((double)zoomRatio_e/zoomRatio_d);
	newRatio*=100;
	_tcscat(text,_T("Zoom: "));
	_stprintf(value, _T("%.0lf"),newRatio);
	_tcscat(value, _T("%"));
	_tcscat(complete,text);
	_tcscat(complete,value);
	SendMessage(statusBar, SB_SETTEXT, 1 | 0, (LPARAM)complete);
}
void changeStatusControlMessage(int msgCode)
{
	//TONEVERDO delete
	//if (msgCode == 4)
	//{
		//paintStatusSaveWarning();
//	}
	//else
	{
		SendMessage(statusBar, SB_SETTEXT, 0, (LPARAM)statusControlMessages[msgCode]);
	}
}
//experimental
void paintStatusSaveWarning(void)
{
	RECT dims;
	HDC deviceContext = GetDC(statusBar);
	GetClientRect(statusBar,&dims);
	SetTextColor(deviceContext, RGB(255,0,0));
	SetBkMode(deviceContext,TRANSPARENT);
	DrawText(deviceContext,statusControlMessages[4],-1,&dims,DT_SINGLELINE|DT_NOCLIP);
	ReleaseDC(statusBar, deviceContext);
}
void changeLangPartIcon(TCHAR *kbdLayOut)
{
	HICON iconToSet;
	if (!_tcscmp(kbdLayOut, _T("English (U.S.)")))
	{
		iconToSet = staticImageUSA_active;
	}
	else if(!_tcscmp(kbdLayOut, _T("Russian")))
	{
		iconToSet = staticImageRU_active;
	}
	SendMessage(statusBar, SB_SETICON, 2 | 0, (LPARAM)iconToSet);
}
void changeLangPartText(TCHAR* kbdLayOut)
{
	SendMessage(statusBar, SB_SETTEXT, 2 | 0, (LPARAM)kbdLayOut);
}
void changeLinePartText(void)
{

	TCHAR lineIndexStrFull[20];
	TCHAR lineIndexDigits[12];

	ZeroMemory(&lineIndexStrFull, sizeof(lineIndexStrFull));
	ZeroMemory(&lineIndexDigits, sizeof(lineIndexDigits));

	_tcscpy(lineIndexStrFull,_T("Line: "));

	INT32 lineIndex = SendMessage(richEditControl, EM_LINEFROMCHAR, -1, NULL);

	_stprintf(lineIndexDigits,_T("%d"),++lineIndex);
	_tcscat(lineIndexStrFull,lineIndexDigits);
	SendMessage(statusBar, SB_SETTEXT, 3 | 0, (LPARAM)lineIndexStrFull);
	//TODO also do get the number of lines in the edit control
}
//characters in richedit
void changeCharPartText(void)
{
	//TODO use a global variable to store the current number of characters, remove -2 characters worth of \r\n whitespace
	GETTEXTLENGTHEX textLengthStruct;
	UINT64 docLength = 0;
	textLengthStruct.flags = GTL_DEFAULT;
	textLengthStruct.codepage = 1200;
	docLength = SendMessage(richEditControl,EM_GETTEXTLENGTHEX,(WPARAM)&textLengthStruct,NULL);
	TCHAR lineIndexStrFull[20];
	TCHAR lineIndexDigits[12];
	ZeroMemory(&lineIndexStrFull, sizeof(lineIndexStrFull));
	ZeroMemory(&lineIndexDigits, sizeof(lineIndexDigits));
	_tcscpy(lineIndexStrFull, _T("Chars: "));
	//UINT64 docLength = GetWindowTextLength(richEditControl);
	//_stprintf(lineIndexDigits, _T("%d"), docLength<0?1:docLength-1);
	//_tcscat(lineIndexStrFull, lineIndexDigits);
	_stprintf(lineIndexDigits,_T("%d"),docLength);
	_tcscat(lineIndexStrFull,lineIndexDigits);
	SendMessage(statusBar, SB_SETTEXT, 5 | 0, (LPARAM)lineIndexStrFull);
}
//words in richedit
void changeWordPartText(void)
{
	
}