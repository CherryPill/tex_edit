#include <Windows.h>
#include <winternl.h>
#include <versionhelpers.h>
#include <tchar.h>
#include "globalVars.h"
#include "systemCheck.h"
#include <Shlwapi.h>

TCHAR* chkWinVer(void) {
	if (IsWindowsXPOrGreater()) {
		if (IsWindows7OrGreater()) {
			if (IsWindows8Point1OrGreater()) {
				if (IsWindows10OrGreater()) {
					return OSList[5];
				}
				return OSList[4];
			}
			else {
				return OSList[2];
			}
		}
		else {
			return OSList[0];
		}
	}
}
TCHAR *getUsrName(TCHAR *inputBuff, DWORD buffSize) {
	bool res = GetUserName(inputBuff,&buffSize);
	return inputBuff;
}
TCHAR *getHostName(TCHAR *inputBuff, DWORD buffSize) {
	bool res = GetComputerName(inputBuff,&buffSize);
	return inputBuff;
}
bool chkComCtlVersion(void) {
	LPCTSTR lpszDllName = _T("C:\\Windows\\System32\\ComCtl32.dll");
	DLLVERSIONINFO2 cmCtlStruct;
	cmCtlStruct.info1.cbSize = sizeof(DLLVERSIONINFO2);
	int iTargetVersion = 6;
	int iGottenVersion = 0;
	return 0;
}