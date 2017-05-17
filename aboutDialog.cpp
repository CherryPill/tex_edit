#include "resource1.h"
#include "appconst.h"
#include "aboutDialog.h"
#include "globalVars.h"
#include "systemCheck.h"
#include "hotkeys.h"
#include "license.h"
BOOL CALLBACK aboutDlgProc(HWND dlgHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			{
				DWORD buffSize = 256;
				TCHAR inputBuff[256];
				ZeroMemory(inputBuff, sizeof(inputBuff));
				//set image to the static control
				
				SendDlgItemMessage(dlgHandle,IDC_STATIC_ICON,STM_SETICON,(WPARAM)mainAppIcon,NULL);
				SetWindowText(GetDlgItem(dlgHandle, IDC_APP_INFO_TX), appInfo);
				SetWindowText(GetDlgItem(dlgHandle, IDC_LICENSE_INFO_TX), licenseInfo);
				SetWindowText(GetDlgItem(dlgHandle, IDC_SOFT_INFO_APP_V_TX), currentVersion);
				SetWindowText(GetDlgItem(dlgHandle, IDC_SOFT_INFO_OS_V_TX), chkWinVer());
				SetWindowText(GetDlgItem(dlgHandle, IDC_SOFT_INFO_HOST_TX), getHostName(inputBuff,buffSize));
				SetWindowText(GetDlgItem(dlgHandle, IDC_SOFT_INFO_USR_TX), getUsrName(inputBuff,buffSize));
				ZeroMemory(inputBuff, sizeof(inputBuff));
				return true;
			}
		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
						 case IDC_ABOUT_ABOUT_OK:
						 {
							 EndDialog(dlgHandle,0);
							 return true;
						 }
				}

		break;
		}
		case WM_LBUTTONDOWN:
		{
			//MessageBox(NULL,_T("kek"),_T("kek"),MB_OK);
			break;
		}
	}
	return false;
}