#include <windows.h>
#include <tchar.h>
#include "globalVars.h"
#include "stdDialogBoxes.h"

void createPrintDialog(void)
{
	PRINTDLG printDialogStruct;
	printDialogStruct.lStructSize = sizeof(PRINTDLG);
	printDialogStruct.hwndOwner = hwnd;
	printDialogStruct.hDevMode = (HANDLE)NULL;
	printDialogStruct.hDevNames = (HANDLE)NULL;
	printDialogStruct.Flags = PD_RETURNDC;
	printDialogStruct.hDC = (HDC)NULL;
	printDialogStruct.nFromPage = 1;
	printDialogStruct.nToPage = 1;
	printDialogStruct.nMinPage = 0;
	printDialogStruct.nMaxPage = 1;
	printDialogStruct.nCopies = 1;
	printDialogStruct.hInstance = ghInstance;
	printDialogStruct.lCustData = 0L;
	printDialogStruct.lpfnPrintHook = (LPPRINTHOOKPROC)NULL;
	printDialogStruct.lpfnSetupHook = (LPSETUPHOOKPROC)NULL;
	printDialogStruct.lpPrintTemplateName = _T("Print");
	printDialogStruct.lpSetupTemplateName = _T("Print");
	printDialogStruct.hPrintTemplate = (HANDLE)NULL;
	printDialogStruct.hSetupTemplate = (HANDLE)NULL;
	PrintDlg(&printDialogStruct);
}
COLORREF initializeColorDlgBox(HWND hwnd)
{
		CHOOSECOLOR cc;
		COLORREF chosenColor;
		static COLORREF acrCustClr[16]; // array of custom colors 
							 // owner window
		HBRUSH hbrush;                  // brush handle
		static DWORD rgbCurrent;        // initial color selection

		ZeroMemory(&cc, sizeof(cc));
		cc.lStructSize = sizeof(cc);
		cc.hwndOwner = hwnd;
		cc.lpCustColors = (LPDWORD)acrCustClr;
		cc.rgbResult = rgbCurrent;
		cc.Flags = CC_FULLOPEN | CC_RGBINIT;

		if (ChooseColor(&cc) == TRUE)
		{
			hbrush = CreateSolidBrush(cc.rgbResult);
			rgbCurrent = cc.rgbResult;
		}
		chosenColor = cc.rgbResult;
		return chosenColor;
}
CHOOSEFONT initializeFontDlgBox(HWND hwnd)
{
	HDC hdc = GetDC(hwnd);                  // display device context of owner window
	CHOOSEFONT cf;            // common dialog box structure
	CHOOSEFONT chosenFont;
	static LOGFONT lf;        // logical font structure
	static DWORD rgbCurrent;  // current text color
	HFONT hfont, hfontPrev;
	DWORD rgbPrev;

	// Initialize CHOOSEFONT
	ZeroMemory(&cf, sizeof(cf));
	cf.lStructSize = sizeof (cf);
	cf.hwndOwner = hwnd;
	cf.lpLogFont = &lf;
	//cf.rgbColors = rgbCurrent;
	cf.Flags = CF_SCREENFONTS | CF_NOSTYLESEL;
	if (ChooseFont(&cf) == TRUE)
	{
		hfont = CreateFontIndirect(cf.lpLogFont);
		hfontPrev = (HFONT)SelectObject(hdc, hfont);
		//rgbCurrent = cf.rgbColors;
		//rgbPrev = SetTextColor(hdc, rgbCurrent);
	}
	//_tcscpy(fontFamily,cf.lpszStyle);
	return cf;
}
int SearchFile(const TCHAR* find, BOOL down, BOOL ignoreCase)
{
	
	return -1;
}
void initializeFindDlgBox(HWND hwnd)
{
	static FINDREPLACE fr;       // common dialog box structure
	static TCHAR szFindWhat[80];  // buffer receiving string
	// Initialize FINDREPLACE
	ZeroMemory(&fr, sizeof(fr));
	ZeroMemory(&szFindWhat,sizeof(szFindWhat));
	fr.lStructSize = sizeof(fr);
	fr.hwndOwner = hwnd;
	fr.lpstrFindWhat = szFindWhat;
	fr.wFindWhatLen = 80;
	fr.Flags = FR_HIDEWHOLEWORD;
	findDlg = (HWND)FindText(&fr);
	try
	{
		if (!findDlg)
		{
			throw _T("Failed to create Find Dialog");
		}
	}
	catch(TCHAR *e)
	{
		MessageBox(NULL, e, _T("Runtime Error"), MB_OK | MB_ICONERROR);
	}
}
void initializeFindANDRplcDlgBox(HWND)
{
			//to be implemented yet	


}
bool findFunc(LPFINDREPLACE lpfr)
{
	//handle up/down and match case
	DWORD searchFlags;
	if ((*lpfr).Flags & FR_DOWN)
	{
		searchFlags = FR_DOWN;
		if ((*lpfr).Flags & FR_MATCHCASE)
		{
			searchFlags = FR_DOWN | FR_MATCHCASE;
		}
	}	
	bool res = false;
	UINT64 richEditTextLen = GetWindowTextLength(richEditControl);
	UINT64 richEditFoundSelectPos = 0;
	UINT64 textToSearchLen = 0;
	//TCHAR *richEditTextBuffer = NULL;
	//TCHAR *richEditFoundTextPos = NULL;
	INT64 richEditFoundTextPos = 0;
	FINDTEXT txtToSearch;
	CHARRANGE rangeToSearch;
	#define rangeToHighlight rangeToSearch
	txtToSearch.lpstrText = (*lpfr).lpstrFindWhat;
	textToSearchLen = _tcslen((*lpfr).lpstrFindWhat);
	SendMessage(richEditControl, EM_GETSEL, 0, (LPARAM)&richEditCurrOffset);
	rangeToSearch.cpMin = richEditCurrOffset?richEditCurrOffset-1:0;
	rangeToSearch.cpMax = -1;
	txtToSearch.chrg = rangeToSearch;
	richEditFoundTextPos = SendMessage(richEditControl,EM_FINDTEXT,(WPARAM)searchFlags,(LPARAM)&txtToSearch);
	if (richEditFoundTextPos >= 0)
	{
		res = true;
		rangeToHighlight.cpMin = richEditFoundTextPos;
		rangeToHighlight.cpMax = richEditFoundTextPos + (textToSearchLen);
		//highlighting the found text
		SendMessage(richEditControl, EM_EXSETSEL, NULL, (LPARAM)&rangeToHighlight);
		SendMessage(richEditControl, EM_SCROLLCARET, 0, 0);

		//setting the new offset
		richEditCurrOffset = rangeToHighlight.cpMax + 1;
	}
	#undef rangeToHighlight rangeToSearch
	return res;
	/*
	try
	{
		richEditTextBuffer = new TCHAR[richEditTextLen+1];
		if (!richEditTextBuffer)
		{
			throw _T("Unable to allocate text buffer");
		}
		else
		{
			GetWindowText(richEditControl,richEditTextBuffer,richEditTextLen+1);
			SendMessage(richEditControl,EM_GETSEL,0,(LPARAM)&richEditCurrOffset);
			richEditFoundTextPos = _tcsstr(richEditTextBuffer + richEditCurrOffset,(*lpfr).lpstrFindWhat);
			//the string wasn't found
			if (!richEditFoundTextPos)
			{	
				res = false;
			}
			//the string was found -> select it and set new offset after the string
			else
			{
				richEditFoundSelectPos = richEditFoundTextPos - richEditTextBuffer;
				richEditCurrOffset = richEditFoundSelectPos + _tcslen((*lpfr).lpstrFindWhat);

				CHARRANGE range;
				range.cpMin = richEditFoundSelectPos;
				range.cpMax = richEditCurrOffset;
				SetFocus(richEditControl);
				SendMessage(richEditControl,EM_EXSETSEL,NULL,(LPARAM)&range);
				//SendMessage(richEditControl,EM_SETSEL,richEditFoundSelectPos,richEditCurrOffset);
				SendMessage(richEditControl,EM_SCROLLCARET,0,0);
				SetFocus(findDlg);
				res = true;
			}
		}
	delete richEditTextBuffer;
	return res;
	}
	catch(TCHAR *e)
	{
		MessageBox(NULL,_T("Error"),e,MB_OK|MB_ICONERROR);
		return false;
	}
	*/
}
