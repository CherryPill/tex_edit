#include <windows.h>
#include <tchar.h>
#include <wchar.h>
#include <CommCtrl.h>
#include "hotkeys.h"
#include "resource.h"
#include "resource1.h"
#include "mainPrefs.h"
#include "appconst.h"
#include "globalVars.h"
#include "settingsIDs.h"
#include "settingsDialog.h"
#include "service.h"
UINT status;
void registerSettingsDialogClass(HWND parentWindow)
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.lpszClassName = _T("Settings");
	wc.hInstance = ghInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc = (WNDPROC)settingsDialogProcedure;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIconSm = appSetsIcon;
	RegisterClassEx(&wc);
}
void createSettingsDialog(HWND parentWindow)
{
	RECT rcClient;
	GetClientRect(parentWindow, &rcClient);
	settingsDialog = CreateWindowEx
	(
		WS_EX_DLGMODALFRAME | WS_EX_TOPMOST, 
		_T("Settings"), 
		settingsDialogCaption,
		WS_VISIBLE | 
		WS_SYSMENU|
		WS_MINIMIZEBOX|
		DS_SETFONT, 
		wpInitPosX, wpInitPosY, 
		settingsDialogBoxWidth, settingsDialogBoxHeight,
		parentWindow,
		NULL, 
		ghInstance, 
		NULL
	);
	SetActiveWindow(settingsDialog);
	SetWindowPos(settingsDialog, HWND_TOP, wpInitPosX, wpInitPosY, settingsDialogBoxWidth, settingsDialogBoxHeight, NULL);
}
void showSettingsDialog(void)
{
	//show actual window
}
void fillChkBoxBlocks(HWND dialogHandle)
{
	//from setttings
	if (settings.bRememberLastSizeByUser)
	{
		SendMessage(chkBox_WinPosDimsRemember,BM_SETCHECK,BST_CHECKED,0);
	}
	if (settings.bSplashScreen)
	{
		SendMessage(chkBox_ToggleSplashScreen, BM_SETCHECK, BST_CHECKED, 0);
	}
	if (settings.bConfirmExit)
	{
		SendMessage(chkBox_ExitConfirm, BM_SETCHECK, BST_CHECKED, 0);
	}
	if (settings.bShowCompleteFilePathInTitle)
	{
		SendMessage(chkBox_ToggleFullPath, BM_SETCHECK, BST_CHECKED, 0);
	}
	if (settings.bDetectLinks)
	{
		SendMessage(chkBox_TogglebDetectLinks, BM_SETCHECK, BST_CHECKED, 0);
	}
	if (settings.bToolbarActive)
	{
		SendMessage(chkBox_ToggleToolbar, BM_SETCHECK, BST_CHECKED, 0);
	}
	if (settings.bToolbarText)
	{
		SendMessage(chkBox_ToggleToolbarText, BM_SETCHECK, BST_CHECKED, 0);
	}
	//addendum
	//disabling toolbar text option toggle if toolbar is disabled
	if (IsDlgButtonChecked(dialogHandle, IDC_PREFS_TOGGLE_TOOLBAR_TEXT) || !settings.bToolbarActive)
	{
		SendMessage(chkBox_ToggleToolbarText,BM_SETCHECK,BST_INDETERMINATE,0);
	}
	//other wise empty
}
LRESULT CALLBACK settingsDialogProcedure(HWND dialogWindow,UINT message, 
	WPARAM wParam, LPARAM lParam)
{
	settingsDialog = dialogWindow;
	bool changeDetected = false;
	switch (message)
	{
			case WM_NOTIFY:
			{
			switch(((LPNMHDR)lParam)->code)
				{
					case TCN_SELCHANGE:
					{
						redrawControls(TabCtrl_GetCurSel(dialogTabControl));
						break;
					}
				}
				break;
			}
			case WM_CREATE:
			{
				RECT winDimensions;
				GetClientRect(dialogWindow, &winDimensions);
				createMainTabArea(dialogWindow);
				createSettingsPages(dialogWindow,winDimensions);
				//loadFlags(); //language flags
				//createStartUpBlock(dialogWindow, winDimensions);
				//createShutDownBlock(dialogWindow, winDimensions);
				//createEditorBlock(dialogWindow,winDimensions);
				//createToolbarBlock(dialogWindow,winDimensions);
				//TODO add Status control block to control appearance of various parts of the status bar
				//createLanguageBlock(dialogWindow,winDimensions);
				//createMainTabArea();


				createOKButton(dialogWindow, winDimensions);
				createCancelButton(dialogWindow, winDimensions);

				//setting values based off of the .dat file
				
				//fillChkBoxBlocks(dialogWindow);
				//EnableWindow(chkBox_ToggleSplashScreen,0); //DO NOT TOUCH THIS
				if (!settings.bToolbarActive)
				{
					EnableWindow(chkBox_ToggleToolbarText,0);
				}




				EnumChildWindows(dialogWindow, (WNDENUMPROC)SetFont, (LPARAM)GetStockObject(DEFAULT_GUI_FONT)); //setting the fonr
				EnableWindow(hwnd,0); //locking the main window
				break;
			}
			case WM_COMMAND:
			{
								changeDetected = true;
								switch (LOWORD(wParam))
								{
										/*case IDC_PREFS_TOGGLE_WINREMEMBER:
										{
												status = IsDlgButtonChecked(dialogWindow,IDC_PREFS_TOGGLE_WINREMEMBER);
												int hurr;
												if (status==BST_CHECKED)
												{
															SendMessage(chkBox_WinPosDimsRemember, BM_SETCHECK, BST_UNCHECKED, 0);
												}
												else
												{
															SendMessage(chkBox_WinPosDimsRemember, BM_SETCHECK, BST_CHECKED, 0);
												}
														
														
														
														
														
										break;
										}*/
										case IDC_OK_BUTTON:
										{
															   //read current state and compare to state in struct
															  if (readChkBoxesState(dialogWindow))
															  {
																
																	//changes occurred
																
																		binary::saveMainPrefs(); //writing struct to bin file
																		MessageBox(hwnd, _T("Changes have been saved and will take effect on next startup"), _T("Notification"), MB_OK | MB_ICONINFORMATION|MB_SYSTEMMODAL);

															  }
															  DestroyWindow(dialogWindow);
															  EnableWindow(hwnd, 1);
										 break;
										}
										case IDC_CANCEL_BUTTON:
										{

																	
																  DestroyWindow(dialogWindow);
																  EnableWindow(hwnd,1);

										break;
										}

								}
				break;
			}
			case WM_CLOSE:
			{
				//if changed and not okayed then asked for confirmation
				EnableWindow(hwnd, 1);
				break;
			}
			case WM_KEYDOWN:
			{
							   if (wParam == ESC_KEY)
							   {
								   SendMessage(dialogWindow,WM_CLOSE,NULL,NULL);
							   }
			}
			//enable white background for the controls (checkboxes)
			case WM_CTLCOLORSTATIC:
			{
				if (GetDlgCtrlID((HWND)lParam)>= IDC_PREFS_TOGGLE_WINREMEMBER 
				&&
					GetDlgCtrlID((HWND)lParam)<= IDC_END)
				{
					return (LONG)GetStockObject(WHITE_BRUSH);
				}
	
				break;
			}
			default:
			{
				break;
			}
	}
	return (DefWindowProcW(dialogWindow, message, wParam, lParam));
}
void writeChkBoxesState(HWND dialogHandle)
{
		//write from dialogwin to struct


}
void createMainTabArea(HWND settingsDialog)
{ 
	const WPARAM headerCount = 5;
	TCITEM tabData;
	TCHAR *tabHeaderTxt[headerCount] = 
	{
			_T("General"),
			_T("Interface"),
			_T("Editor"),
			_T("Keybindings"),
			_T("Advanced"),
	};
	dialogTabControl = CreateWindowEx
	(
			0,
			WC_TABCONTROL,
			NULL,
			WS_CHILD|WS_VISIBLE,
			0,0,
			440,
			500,
			settingsDialog,
			(HMENU)IDC_PREFS_TABAREA,
			NULL,
			NULL
	);
	for (WPARAM x = 0;x<headerCount;x++)
	{
		tabData.mask = TCIF_TEXT;
		tabData.pszText = tabHeaderTxt[x];
		SendMessage(dialogTabControl,TCM_INSERTITEM,x,(LPARAM)&tabData);
	}
}
void createStatusbarBlock(HWND parentWindow, RECT dimensions)
{
	
}
void createMiscBlock_p1(HWND parentWindow, RECT dimensions)
{
	
}
void createKBindsBlock(HWND parentWindow, RECT dimensions)
{

}
void createBoilerBlock(HWND parentWindow, RECT dimensions)
{
	
}
void createEditorBlock(HWND parentWindow,RECT dimensions)
{
	CreateWindowEx(0, _T("Button"), _T("Editor"),
		WS_CHILD | 
		WS_VISIBLE | 
		BS_GROUPBOX,
		(dimensions.left + PREF_BLOCK_MARGIN_LEFT), 
		(PREF_BLOCK_POSINIT_Y + 20 + 10*2 + PREF_BLOCK_MARGIN*2) * 3, 
		PREF_BLOCK_WIDTH, PREF_BLOCK_HEIGHT,
		parentWindow,
		(HMENU)IDC_EDITOR_GROUPBOX, 
		NULL, 
		NULL);
	chkBox_ToggleFullPath = CreateWindowEx(0, 
		_T("Button"), _T("Show complete path in title bar"),
		WS_CHILD |
		 WS_VISIBLE | 
		 BS_AUTOCHECKBOX,
		((dimensions.left + PREF_BLOCK_MARGIN_LEFT)) + PREF_BLOCK_PADDING_LEFT, 
		(PREF_BLOCK_POSINIT_Y + 30 + 20+10) * 3, PREF_BLOCK_WIDTH_TEXT, 20,
		parentWindow, (HMENU)IDC_PREFS_TOGGLE_FULL_PATH, NULL, NULL);
	
	chkBox_TogglebDetectLinks = CreateWindowEx(0,
	 _T("Button"), 
	 _T("Detect URLs and email links"),
	 	WS_CHILD |
		WS_VISIBLE |
		BS_AUTOCHECKBOX,
		((dimensions.left + PREF_BLOCK_MARGIN_LEFT)) + PREF_BLOCK_PADDING_LEFT, 
		(PREF_BLOCK_POSINIT_Y + 30 + 20 + 10) * 3+20, 
		PREF_BLOCK_WIDTH_TEXT, 20,
		parentWindow, 
		(HMENU)IDC_PREFS_TOGGLE_LINKS, 
		NULL, 
		NULL);



	/*INITCOMMONCONTROLSEX icex;           // Structure for control initialization. ensuring the commctrl dll is loaded
	InitCommonControlsEx(&icex);
	combo = CreateWindowEx(0, WC_COMBOBOXEX, NULL,
		WS_BORDER | WS_VISIBLE |
		WS_CHILD | CBS_DROPDOWN,
		((dimensions.left + PREF_BLOCK_MARGIN_LEFT)) + PREF_BLOCK_PADDING_LEFT, (PREF_BLOCK_POSINIT_Y + 30 + 20 + 30) * 3, PREF_BLOCK_WIDTH_TEXT, 20,
		parentWindow,
		NULL,
		ghInstance,
		NULL);
	comboImages = ImageList_Create(32, 32, ILC_COLOR32 | ILC_MASK, 2, 0);

	//HBITMAP icon = (HBITMAP)LoadImage(ghInstance, _T("left.bmp"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);


	//ImageList_Add(toolbarImages, LoadBitmap(ghInstance, MAKEINTRESOURCE(IDB_BITMAP3)), NULL);
	ImageList_AddIcon(comboImages, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON153)));
	ImageList_AddIcon(comboImages, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON154)));
	SendMessage(combo, CBEM_SETIMAGELIST, 0, (LPARAM)comboImages);
	*/

			





}
void createToolbarBlock(HWND parentWindow, RECT dimensions)
{
	CreateWindowEx(0, 
		_T("Button"), 
		_T("Toolbar"),
		WS_CHILD |
		WS_VISIBLE |
		BS_GROUPBOX,
		(dimensions.left + PREF_BLOCK_MARGIN_LEFT), 
		PREF_BLOCK_POSINIT_Y,
		PREF_BLOCK_WIDTH, 
		getGroupBoxWidth(2),
		parentWindow, 
		(HMENU)IDC_TOOLBAR_GROUPBOX, 
		NULL,
		NULL);
	
	chkBox_ToggleToolbar = CreateWindowEx(0,
	 _T("Button"),
	  _T("Show icon toolbar"),
		WS_CHILD |
		WS_VISIBLE | 
		BS_AUTOCHECKBOX,
		((dimensions.left + PREF_BLOCK_MARGIN_LEFT)) + PREF_BLOCK_PADDING_LEFT, 
		(PREF_BLOCK_POSINIT_Y + PREF_BLOCK_FIRSTITEM_OFFSET),
		PREF_BLOCK_WIDTH_TEXT, PREF_BLOCK_CHKBOX_HEIGHT,
		parentWindow, 
		(HMENU)IDC_PREFS_TOGGLE_TOOLBAR,
		 NULL, 
		 NULL);
	chkBox_ToggleToolbarText = CreateWindowEx(0, 
	_T("Button"), _T("Show text next to icons"),
		WS_CHILD |
		WS_VISIBLE |
		BS_AUTOCHECKBOX,
		((dimensions.left + PREF_BLOCK_MARGIN_LEFT)) + PREF_BLOCK_PADDING_LEFT + PREF_BLOCK_SUBITEM_OFFSET,
		(PREF_BLOCK_POSINIT_Y + PREF_BLOCK_FIRSTITEM_OFFSET + PREF_BLOCK_CHKBOX_HEIGHT +
			PREF_BLOCK_CHKBOX_MARGIN_TOP),
		PREF_BLOCK_WIDTH_TEXT, PREF_BLOCK_CHKBOX_HEIGHT,
		parentWindow, 
		(HMENU)IDC_PREFS_TOGGLE_TOOLBAR_TEXT, 
		NULL, 
		NULL);

}
void createRecentsBlock(HWND parentWindow, RECT dimensions)
{
	CreateWindowEx(0,
		_T("Button"),
		_T("Recent files"),
		WS_CHILD |
		WS_VISIBLE |
		BS_GROUPBOX,
		(dimensions.left + PREF_BLOCK_MARGIN_LEFT),
		(PREF_BLOCK_POSINIT_Y + 20 + 10 + PREF_BLOCK_MARGIN * 3) * 2,
		PREF_BLOCK_WIDTH,
		getGroupBoxWidth(2),
		parentWindow,
		(HMENU)IDC_RECENTS_GROUPBOX,
		NULL,
		NULL);

	chkBox_ToggleRecentDuplicates = CreateWindowEx(0,
		_T("Button"),
		_T("Allow duplicate file names"),
		WS_CHILD |
		WS_VISIBLE |
		BS_AUTOCHECKBOX,
		((dimensions.left + PREF_BLOCK_MARGIN_LEFT)) + PREF_BLOCK_PADDING_LEFT,
		(PREF_BLOCK_MARGIN + PREF_BLOCK_POSINIT_Y + 30 + 20) * 2,
		PREF_BLOCK_WIDTH_TEXT, PREF_BLOCK_CHKBOX_HEIGHT,
		parentWindow,
		(HMENU)IDC_PREFS_TOGGLE_RECENT_DUPS,
		NULL,
		NULL);
		chkBox_ToggleRecentOnlyShort = CreateWindowEx(0,
			_T("Button"),
			_T("Show only file name and extension"),
			WS_CHILD |
			WS_VISIBLE |
			BS_AUTOCHECKBOX,
			((dimensions.left + PREF_BLOCK_MARGIN_LEFT)) + PREF_BLOCK_PADDING_LEFT,
			(PREF_BLOCK_MARGIN + PREF_BLOCK_POSINIT_Y + 30 + 20) * 2 + 
			PREF_BLOCK_CHKBOX_HEIGHT +
			PREF_BLOCK_CHKBOX_MARGIN_TOP,
			PREF_BLOCK_WIDTH_TEXT, PREF_BLOCK_CHKBOX_HEIGHT,
			parentWindow,
			(HMENU)IDC_PREFS_TOGGLE_RECENT_SHORT,
			NULL,
			NULL);
}
void createLanguageBlock(HWND parentWindow, RECT dimensions)
{
	CreateWindowEx(0, _T("Button"), _T("Language"),
		WS_CHILD |
		WS_VISIBLE | 
		BS_GROUPBOX,
		(dimensions.left + PREF_BLOCK_MARGIN_LEFT), 
		((PREF_BLOCK_POSINIT_Y + 30 + 10 * 2 + PREF_BLOCK_MARGIN * 2) * 5), 
		PREF_BLOCK_WIDTH, 
		PREF_BLOCK_HEIGHT,
		parentWindow, 
		NULL, 
		NULL, 
		NULL);
	placeHolderUSA = CreateWindowEx(0, 
	_T("static"), 
	_T(""),
		WS_CHILD | 
		WS_VISIBLE |
		SS_ICON,
		50, ((PREF_BLOCK_POSINIT_Y + 30 + 10 * 2 + PREF_BLOCK_MARGIN * 2) * 5)+20,
		32, 32,
		parentWindow, 
		(HMENU)IDC_PREFS_PLCHOLD_USA, NULL, NULL);
	placeHolderRU = CreateWindowEx(0, _T("static"), _T(""),
		WS_CHILD | 
		WS_VISIBLE | 
		SS_ICON,
		50 + 32 + 10, 
		((PREF_BLOCK_POSINIT_Y + 30 + 10 * 2 + PREF_BLOCK_MARGIN * 2) * 5)+20,
		32, 32,
		parentWindow, 
		(HMENU)IDC_PREFS_PLCHOLD_RU, NULL, NULL);
	placeHolderJP = CreateWindowEx(0, 
		_T("static"), _T(""),
		WS_CHILD |
		 WS_VISIBLE | 
		 SS_ICON,
		50 + (32 + 10) * 2, 
		((PREF_BLOCK_POSINIT_Y + 30 + 10 * 2 + PREF_BLOCK_MARGIN * 2) * 5)+20,
		 32, 32,
		parentWindow, 
		(HMENU)IDC_PREFS_PLCHOLD_JP,
		 NULL, 
		 NULL);

	SendMessage(placeHolderUSA, STM_SETICON, (WPARAM)staticImageUSA_active, (LPARAM)0);
	SendMessage(placeHolderRU, STM_SETICON, (WPARAM)staticImageRU_active, (LPARAM)0);
	SendMessage(placeHolderJP, STM_SETICON, (WPARAM)staticImageJP_active, (LPARAM)0);

	/*radioButtonLangUSA = CreateWindowEx(0, _T("Button"), _T(""),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		((dimensions.left + PREF_BLOCK_MARGIN_LEFT)) + PREF_BLOCK_PADDING_LEFT, (PREF_BLOCK_POSINIT_Y + 30 + 20 + PREF_BLOCK_MARGIN * 3) * 5, 20, 20,
		parentWindow, (HMENU)IDC_PREFS_TOGGLE_TOOLBAR, NULL, NULL);

	radioButtonLangRU = CreateWindowEx(0, _T("Button"), _T(""),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		((dimensions.left + PREF_BLOCK_MARGIN_LEFT)) + PREF_BLOCK_PADDING_LEFT+50, (PREF_BLOCK_POSINIT_Y + 30 + 20 + PREF_BLOCK_MARGIN * 3) * 5, 20, 20,
		parentWindow, (HMENU)IDC_PREFS_TOGGLE_TOOLBAR, NULL, NULL);

	placeHolderUSA = CreateWindowEx(0, _T("STATIC"), _T(""),
		WS_CHILD | WS_VISIBLE | SS_BITMAP,
		5, 5, 300, 300,
		parentWindow, (HMENU)IDB_BITMAP7, NULL, NULL);
	placeHolderRU = CreateWindowEx(0, _T("STATIC"), _T(""),
		WS_CHILD | WS_VISIBLE | SS_BITMAP,
		5, 5, 300, 300,
		parentWindow, (HMENU)IDB_BITMAP7, NULL, NULL);

	SendMessage(placeHolderUSA, STM_SETIMAGE,
		(WPARAM)IMAGE_BITMAP, (LPARAM)staticImageUSA);
	SendMessage(placeHolderRU, STM_SETIMAGE,
		(WPARAM)IMAGE_BITMAP, (LPARAM)staticImageRU);*/

}
void createStartUpBlock(HWND parentWindow, RECT dimensions)
{
	//label
	//control
	//mov to global scope
	CreateWindowEx
	(
		0, _T("Button"), _T("StartUp"),
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		(dimensions.left+PREF_BLOCK_MARGIN_LEFT), PREF_BLOCK_POSINIT_Y, 
		PREF_BLOCK_WIDTH, getGroupBoxWidth(3),
		parentWindow, 
		(HMENU)IDC_STARTUP_GROUPBOX, 
		NULL, 
		NULL
	);
	
	chkBox_WinPosDimsRemember = CreateWindowEx
	(
		0, _T("Button"), _T("Remember last window position and window size"),
		WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
		((dimensions.left + PREF_BLOCK_MARGIN_LEFT)) + PREF_BLOCK_PADDING_LEFT, 
		(PREF_BLOCK_POSINIT_Y + PREF_BLOCK_FIRSTITEM_OFFSET),
		 PREF_BLOCK_WIDTH_TEXT, PREF_BLOCK_CHKBOX_HEIGHT,
		parentWindow, 
		(HMENU)IDC_PREFS_TOGGLE_WINREMEMBER, 
		NULL, 
		NULL
	);
	chkBox_ToggleLastSession = CreateWindowEx
	(
		0, _T("Button"), _T("Load files from the last session"),
		WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
		((dimensions.left + PREF_BLOCK_MARGIN_LEFT)) + PREF_BLOCK_PADDING_LEFT, 
		(PREF_BLOCK_POSINIT_Y + PREF_BLOCK_FIRSTITEM_OFFSET + PREF_BLOCK_CHKBOX_HEIGHT + 
		PREF_BLOCK_CHKBOX_MARGIN_TOP),
		PREF_BLOCK_WIDTH_TEXT, PREF_BLOCK_CHKBOX_HEIGHT,
		parentWindow, 
		(HMENU)IDC_PREFS_TOGGLE_WINREMEMBER, 
		NULL, 
		NULL
	);
	chkBox_ToggleSplashScreen = CreateWindowEx
	(
		0, _T("Button"), _T("Splash Screen"),
		WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
		((dimensions.left + PREF_BLOCK_MARGIN_LEFT)) + PREF_BLOCK_PADDING_LEFT, 
		(PREF_BLOCK_POSINIT_Y + PREF_BLOCK_FIRSTITEM_OFFSET + (PREF_BLOCK_CHKBOX_HEIGHT + PREF_BLOCK_CHKBOX_MARGIN_TOP)*2),
		 PREF_BLOCK_WIDTH_TEXT, 
		 PREF_BLOCK_CHKBOX_HEIGHT,
		parentWindow, 
		(HMENU)IDC_PREFS_TOGGLE_bSplashScreen, 
		NULL, 
		NULL
		);
	//CheckDlgButton(chkBox_WinPosDimsRemember, 1, BST_CHECKED);		
}
void createShutDownBlock(HWND parentWindow, RECT dimensions)
{
	CreateWindowEx(0, _T("Button"), _T("Shutdown"),
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		(dimensions.left+PREF_BLOCK_MARGIN_LEFT),
		 (PREF_BLOCK_POSINIT_Y + 20+10 + PREF_BLOCK_MARGIN*3)*2, 
		 PREF_BLOCK_WIDTH, 
		getGroupBoxWidth(1),
		parentWindow, 
		(HMENU)IDC_SHUTDOWN_GROUPBOX, NULL, NULL);
	chkBox_ExitConfirm = CreateWindowEx(0, _T("Button"), _T("Always confirm exit"),
		WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
		((dimensions.left + PREF_BLOCK_MARGIN_LEFT)) + PREF_BLOCK_PADDING_LEFT, 
		(PREF_BLOCK_MARGIN+PREF_BLOCK_POSINIT_Y + 30 + 20)*2, PREF_BLOCK_WIDTH_TEXT, 20,
		parentWindow, (HMENU)IDC_PREFS_TOGGLE_EXIT_NORMAL_CONFIRM, NULL, NULL);
}
//TO DO TURN IT ALL INTO ONE FUNCTION AND CREATE BLOCKS WITHIN A FOR LOOP

//save button
void createOKButton(HWND dialogWindow, RECT dims)
{
	dialogOKButton = CreateWindowEx(
		0,
		_T("BUTTON"),
		_T("Save"),
		WS_CHILD | WS_VISIBLE|BS_ICON|BS_CENTER,
		((dims.right - dims.left) / 2) - 100,
		STD_BTN_POS_Y,
		STD_BTN_WIDTH,
		STD_BTN_HEIGHT,
		dialogWindow,
		(HMENU)IDC_OK_BUTTON,
		NULL,
		NULL);
	staticImageSave = (HICON)LoadImage(ghInstance, 
						MAKEINTRESOURCE(IDI_ICON_SAVE), 
						IMAGE_ICON, 
						32, 
						32, 
						LR_VGACOLOR);
	SendMessage(dialogOKButton,BM_SETIMAGE,IMAGE_ICON,(LPARAM)staticImageSave);
}

void createCancelButton(HWND dialogWindow, RECT dims)
{
	dialogCancelButton = CreateWindowEx(
		0,
		_T("BUTTON"),
		_T("Cancel"),
		WS_CHILD | WS_VISIBLE|BS_ICON|BS_CENTER,
		((dims.right - dims.left) / 2 - 100) + STD_BTN_WIDTH+50 + PREF_BLOCK_MARGIN,
		STD_BTN_POS_Y,
		STD_BTN_WIDTH,
		STD_BTN_HEIGHT,
		dialogWindow,
		(HMENU)IDC_CANCEL_BUTTON,
		NULL,
		NULL);
		staticImageCancel = (HICON)LoadImage(ghInstance, 
							MAKEINTRESOURCE(IDI_ICON_CANCEL), 
							IMAGE_ICON, 
							32, 
							32, 
							LR_VGACOLOR);
		SendMessage(dialogCancelButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)staticImageCancel);
		
}
//font

bool CALLBACK SetFont(HWND child, LPARAM font)
{
	SendMessage(child, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
	return true;
}
//fix this bullshit F.A.M.
bool readChkBoxesState(HWND dialogWindow)
{
	bool changeOccurred = false;
	//difference should be  1 if change occurred, otherwise 0 (1-1) = 0 (0 -0 ) = 0 ||| 1-0 0-1
	if (	(IsDlgButtonChecked(dialogWindow, IDC_PREFS_TOGGLE_WINREMEMBER)) != (settings.bRememberLastSizeByUser)		)
	{
		settings.bRememberLastSizeByUser = (bool)(IsDlgButtonChecked(dialogWindow,IDC_PREFS_TOGGLE_WINREMEMBER));
		changeOccurred = true;
	}
	if (	(int)(IsDlgButtonChecked(dialogWindow, IDC_PREFS_TOGGLE_bSplashScreen)) - (int)(settings.bSplashScreen))
	{
		settings.bSplashScreen = (bool)(IsDlgButtonChecked(dialogWindow, IDC_PREFS_TOGGLE_bSplashScreen));
		changeOccurred = true;

	}

	if (	(int)(IsDlgButtonChecked(dialogWindow, IDC_PREFS_TOGGLE_EXIT_NORMAL_CONFIRM)) - (int)(settings.bConfirmExit))
	{

		settings.bConfirmExit = (bool)(IsDlgButtonChecked(dialogWindow, IDC_PREFS_TOGGLE_EXIT_NORMAL_CONFIRM));
		changeOccurred = true;

	}

	if (	(int)(IsDlgButtonChecked(dialogWindow, IDC_PREFS_TOGGLE_FULL_PATH)) - (int)(settings.bShowCompleteFilePathInTitle))
	{
		settings.bShowCompleteFilePathInTitle = (bool)(IsDlgButtonChecked(dialogWindow, IDC_PREFS_TOGGLE_FULL_PATH));
		changeOccurred = true;
	}
	if ((int)(IsDlgButtonChecked(dialogWindow, IDC_PREFS_TOGGLE_TOOLBAR)) - (int)(settings.bToolbarActive))
	{
		settings.bToolbarActive = (bool)(IsDlgButtonChecked(dialogWindow, IDC_PREFS_TOGGLE_TOOLBAR));
		changeOccurred = true;

	}
	if (	(int)(IsDlgButtonChecked(dialogWindow, IDC_PREFS_TOGGLE_LINKS)) - (int)(settings.bDetectLinks))
	{
		settings.bDetectLinks = (bool)(IsDlgButtonChecked(dialogWindow, IDC_PREFS_TOGGLE_LINKS));
		changeOccurred = true;
	}

	if (	(int)(IsDlgButtonChecked(dialogWindow, IDC_PREFS_TOGGLE_TOOLBAR_TEXT)) - (int)(settings.bToolbarText))
	{
		settings.bToolbarText = (bool)(IsDlgButtonChecked(dialogWindow, IDC_PREFS_TOGGLE_TOOLBAR_TEXT));
		changeOccurred = true;
	}
	return changeOccurred;
}
//loading flag images
void loadFlags(void)
{
	staticImageUSA_active = (HICON)LoadImage(ghInstance, MAKEINTRESOURCE(IDI_ICON156), IMAGE_ICON, 32, 32, LR_VGACOLOR);
	staticImageRU_active = (HICON)LoadImage(ghInstance, MAKEINTRESOURCE(IDI_ICON157), IMAGE_ICON, 32, 32, LR_VGACOLOR);
	staticImageJP_active = (HICON)LoadImage(ghInstance, MAKEINTRESOURCE(IDI_ICON20), IMAGE_ICON, 32, 32, LR_VGACOLOR);

	staticImageUSA_inactive = (HICON)LoadImage(ghInstance, MAKEINTRESOURCE(IDI_ICON159), IMAGE_ICON, 32, 32, LR_VGACOLOR);
	staticImageRU_inactive = (HICON)LoadImage(ghInstance, MAKEINTRESOURCE(IDI_ICON158), IMAGE_ICON, 32, 32, LR_VGACOLOR);
	staticImageJP_inactive = (HICON)LoadImage(ghInstance, MAKEINTRESOURCE(IDI_ICON21), IMAGE_ICON, 32, 32, LR_VGACOLOR);

}
void redrawControls(INT32 selectedTabIndex)
{
	try
	{
		if (selectedTabIndex<0)
		{
			throw _T("Something went terribly wrong");
		}
		else
		{
			hideAllSettingsControls();
			switch (selectedTabIndex)
			{
				case 0:
					{
						toggleShowHidePage_0(true);
						break;
					}
				case 1:
					{
						toggleShowHidePage_1(true);
						break;
					}
				case 2:
					{
						toggleShowHidePage_2(true);
						break;
					}
				case 3:
					{
						toggleShowHidePage_3(true);
						break;
					}
				case 4:
					{
						toggleShowHidePage_4(true);
						break;
					}
				case 5:
					{
						toggleShowHidePage_5(true);
						break;
					}
			}
		}
		
	}
	catch (TCHAR *e)
	{
		MessageBox(NULL,e,_T("Runtime error"),MB_OK|MB_ICONERROR);
	}
}
//show/hide controls for a specific page in the tab are of the settings dialog box
//args: show = true, hide = false
//page 0 - general tab
void hideAllSettingsControls(void)
{
	toggleShowHidePage_0(false);
	toggleShowHidePage_1(false);
	toggleShowHidePage_2(false);
	toggleShowHidePage_3(false);
	toggleShowHidePage_4(false);
	toggleShowHidePage_5(false);
}
void toggleShowHidePage_0(bool val)
{
	INT32 flag = -1;
	val?flag=SW_SHOW:flag=SW_HIDE;
		
	ShowWindow(GetDlgItem(settingsDialog,IDC_STARTUP_GROUPBOX),flag);
	ShowWindow(chkBox_WinPosDimsRemember,flag);
	ShowWindow(chkBox_ToggleLastSession, flag);
	ShowWindow(chkBox_ToggleSplashScreen, flag);
		
	ShowWindow(GetDlgItem(settingsDialog, IDC_SHUTDOWN_GROUPBOX), flag);
	ShowWindow(chkBox_ExitConfirm, flag);
	//ShowWindow(chkBox_ExitconfirmUnsaved, SW_SHOW);
}
//page 1 - interface tab
void toggleShowHidePage_1(bool val)
{
	INT32 flag = -1;
	val ? flag = SW_SHOW : flag = SW_HIDE;

	ShowWindow(GetDlgItem(settingsDialog, IDC_TOOLBAR_GROUPBOX), flag);
	ShowWindow(GetDlgItem(settingsDialog, IDC_RECENTS_GROUPBOX),flag);
	ShowWindow(chkBox_ToggleToolbar, flag);
	ShowWindow(chkBox_ToggleToolbarText, flag);
	ShowWindow(chkBox_ToggleRecentDuplicates, flag);
	ShowWindow(chkBox_ToggleRecentOnlyShort, flag);
}
//page 2 - editor tab
void toggleShowHidePage_2(bool val)
{
	INT32 flag = -1;
	val ? flag = SW_SHOW : flag = SW_HIDE;

	ShowWindow(GetDlgItem(settingsDialog, IDC_EDITOR_GROUPBOX), flag);
	ShowWindow(chkBox_ToggleFullPath, flag);
	ShowWindow(chkBox_TogglebDetectLinks, flag); //typo
}
//page 3 - keybingings tab
void toggleShowHidePage_3(bool val)
{

}
//page 4 - advanced tab
void toggleShowHidePage_4(bool val)
{

}
//page 5 - not used
void toggleShowHidePage_5(bool val)
{
	
}
void createSettingsPages(HWND dlgWindow, RECT dims)
{
	  createSettings_Pg_0(dlgWindow,dims);
	  createSettings_Pg_1(dlgWindow,dims);
	  createSettings_Pg_2(dlgWindow,dims);
	  createSettings_Pg_3(dlgWindow,dims);
	  createSettings_Pg_4(dlgWindow,dims);
	  hideAllSettingsControls();
	  toggleShowHidePage_0(true);
	  //createSettings_Pg_5(dlgWindow,dims); dummy
}
void createSettings_Pg_0(HWND dlgWin, RECT dims)
{
	createStartUpBlock(dlgWin, dims);
	createShutDownBlock(dlgWin, dims);
}
void createSettings_Pg_1(HWND dlgWin, RECT dims)
{
	createToolbarBlock(dlgWin, dims);
	createRecentsBlock(dlgWin, dims);
	createStatusbarBlock(dlgWin, dims);
}
void createSettings_Pg_2(HWND dlgWin, RECT dims)
{
	createEditorBlock(dlgWin, dims);
}
void createSettings_Pg_3(HWND dlgWin, RECT dims)
{
	
}
void createSettings_Pg_4(HWND dlgWin, RECT dims)
{

}
void createSettings_Pg_5(HWND dlgWin, RECT dims)
{

}