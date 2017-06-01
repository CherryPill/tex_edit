#include <windows.h>
#include <tchar.h>
#include "hotkeys.h"
#include "fileIO.h"
#include "mainEditControl.h"
#include "appconst.h"
#include "globalVars.h"
#include "settingsDialog.h"
#include "stdDialogBoxes.h"

#include "statusControl.h"
#include "toolbarControl.h"
#include <Richedit.h>
#include "mainEditUtils.h"
#include "inputLangChange.h"
void createMainRichEditControl(HWND mainWindowHandle, HINSTANCE appInstance)
{
	RECT parentWindowDims;
	GetClientRect(mainWindowHandle,&parentWindowDims);
	LoadLibrary(_T("msftedit.dll"));
	richEditControl = CreateWindowEx(
		0, MSFTEDIT_CLASS, _T(""),
		ES_MULTILINE | 
		ES_AUTOHSCROLL|
		ES_AUTOHSCROLL|
		ES_SAVESEL|
		ES_NOHIDESEL|
		WS_VSCROLL|
		WS_HSCROLL|
		WS_VISIBLE |
		WS_CHILD |
		WS_TABSTOP,
		0, 0, parentWindowDims.right-parentWindowDims.left, 
		parentWindowDims.bottom - parentWindowDims.top,
		mainWindowHandle, NULL, ghInstance, NULL	
	);
	SendMessage(richEditControl, EM_SETEVENTMASK, 0, LPARAM(SendMessage(mainWindowHandle, EM_GETEVENTMASK, 0, 0) | ENM_CHANGE
	|ENM_KEYEVENTS|ENM_DROPFILES|ENM_SELCHANGE));
	lpEditWndProc = (WNDPROC)SetWindowLongPtr(richEditControl, GWL_WNDPROC, (LONG_PTR)&mainRichEditControlProc);
	enableDragAndDrop();
	MoveWindow(richEditControl,0,400,200,300,false); //what is this
}
LRESULT CALLBACK mainRichEditControlProc(HWND handle, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		break;
	}
	case WM_MOUSEWHEEL:
	{
		if (LOWORD(wParam) == MK_CONTROL)
		{
			short val = (short)HIWORD(wParam);
			if (val > 0)
			{
				SendMessage(richEditControl, EM_SETZOOM, ++zoomRatio_e, zoomRatio_d);
			}
			else
			{
				SendMessage(richEditControl, EM_SETZOOM, --zoomRatio_e, zoomRatio_d);
			}
			changeZoomPartText();
		}
		break;
	}
	case WM_INPUTLANGCHANGE:
	{
		changeLangStatBar();
		break;
	}
	case WM_NOTIFY:
	{
	changeCharPartText();
					  switch (((LPNMHDR)lParam)->code)
					  {
					  
					  }
	break;
	}
			case WM_KEYDOWN:
			{
				
							   fileChanged = true;	
							   fileSaved = false;
							   enableFastSaveIcon();
							   changeStatusControlMessage(4);
							   //changeCharPartText();
							   if (HIWORD(GetKeyState(CNTRL_KEY)))
							   {
								   switch (wParam)
								   {
										   case O_KEY:
										   {
														  
															  normal::initOpeningSequence();
														 
																 break;
										   }
										   case P_KEY:
										   {
														 //init print dlg
														
															 createPrintDialog();
														 
														 break;
										   }
										   case J_KEY:
										   {
													
															 createSettingsDialog(hwnd);
														 
														 break;
														 //init prefs
										   }
										   case F_KEY:
										   {
														
															 //search
															 MessageBox(hwnd, _T("Find is not available at this time"), _T("Error"), MB_ICONERROR);
														 
														 break;
														 //init prefs
										   }
										   case H_KEY:
										   {
														
															 //search + replace
															 MessageBox(hwnd, _T("Find and replace is not available at this time"), _T("Error"), MB_ICONERROR);

														 
														 break;
														 //init prefs
										   }
										   case S_KEY:
										   {
														

															 if (fileLoaded)
															 {
																 initSilentSavingSequence();

															 }
															 else
															 {
																 initSavingAsSequence();
															 }
												
														 break;
										   }
										   case B_KEY:
										   {
														 break;
										   }
										   case I_KEY:
										   {
														 break;
										   }	
										   case U_KEY:
										   {

														 break;
										   }

								   }
								
							   }
							   else
							   {
								   if (wParam == VK_F5)
								   {
									   initSilentSavingSequence();
								   }
							   }
							  /* switch (wParam)
							   {
									   case  O_KEY:
									   {
													  if (HIWORD(GetKeyState(VK_CONTROL)))
													  {
														  initOpeningSequence();
													  }
													  break;
									   }
									   case P_KEY:
									   {
													//init print dlg
													 if (HIWORD(GetKeyState(VK_CONTROL)))
													 {
																 createPrintDialog();
													 }
													 break;
									   }
									   case J_KEY:
									   {
													 if (HIWORD(GetKeyState(VK_CONTROL)))
													 {
													 createSettingsDialog(hwnd);
													 }
													 break;
										//init prefs
									   }
									   case F_KEY:
									   {
													 if (HIWORD(GetKeyState(VK_CONTROL)))
													 {
														 //search
														 MessageBox(hwnd, _T("Find is not available at this time"), _T("Error"), MB_ICONERROR);
													 }
													 break;
													 //init prefs
									   }
									   case H_KEY:
									   {
													 if (HIWORD(GetKeyState(VK_CONTROL)))
													 {
														 //search + replace
														 MessageBox(hwnd, _T("Find and replace is not available at this time"), _T("Error"), MB_ICONERROR);

													 }
													 break;
													 //init prefs
							   }
									   case S_KEY:
									   {
													 if (HIWORD(GetKeyState(VK_CONTROL)))
													 {
														 
														 if (fileLoaded)
														 {
															 initSilentSavingSequence();

														 }
														 else
														 {
															 initSavingAsSequence();
														 }
													 }
										break;
									   }
					}
			}

	}*/
	
	//if ((uMsg == WM_CHAR) && (wParam == 0x57))
	//{
		//PostQuitMessage(0);
		//return 0;
	//}
	}
	}
	return CallWindowProc(lpEditWndProc, handle, uMsg, wParam, lParam);
}
