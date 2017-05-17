#include <Windows.h>
#include "statusControl.h"
#include "inputLangChange.h"
TCHAR *getKBDLayOut(TCHAR *langName)
{
	DWORD bufferSize = BUFFERSIZE;
	TCHAR *regKey = _T("SYSTEM\\CurrentControlSet\\Control\\Keyboard Layouts\\");
	TCHAR codeChar[16];
	TCHAR regKeyArr[513];
	TCHAR info[BUFFERSIZE];
	
	ZeroMemory(&regKeyArr,sizeof(regKeyArr));
	ZeroMemory(&codeChar,sizeof(codeChar));
	//TCHAR *code = _T("00000409"); //control value
	_stprintf(codeChar,_T("%s"),langName);
	
	_tcscpy(regKeyArr,regKey);
	_tcscat(regKeyArr,codeChar);
	DWORD dwRet;
	HKEY openKey;
			LONG error = RegOpenKeyEx
			(
				HKEY_LOCAL_MACHINE,
				regKeyArr,
				0,
				KEY_QUERY_VALUE,
				&openKey
			);
	dwRet = RegQueryValueEx
	(
		openKey,
		_T("Layout Text"),
		NULL,
		NULL,
		(LPBYTE)info,
		&bufferSize
	);
	RegCloseKey(openKey);
	//int sentinel = 7;
	if (dwRet != ERROR_SUCCESS)
	{
		MessageBox(NULL,NULL,_T("Something happened"),MB_OK);
		return _T("NULL");
	}
	else
	{
		if (!_tcscmp(info,_T("US")))
		{
			return (TCHAR*)_T("English (U.S.)");
		}
		return (TCHAR*)info;
	}
}
void changeLangStatBar(void)
{
	TCHAR buff[256];
	GetKeyboardLayoutName(buff);
	TCHAR *currentLang = getKBDLayOut(buff);
	changeLangPartText(currentLang);
	changeLangPartIcon(currentLang);
}