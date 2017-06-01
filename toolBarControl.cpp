#include <windows.h>
#include <CommCtrl.h>
#include <tchar.h>
#include "mainPrefs.h"
#include "toolbarControl.h"
#include "globalVars.h"
#include "toolbarIDs.h"
#include "menuids.h"
#include "resource1.h"
void createToolbar(HWND hwnd) {
	INITCOMMONCONTROLSEX icex;           // Structure for control initialization. ensuring the commctrl dll is loaded
	InitCommonControlsEx(&icex);
	toolBar = CreateWindowEx(
	0,
	TOOLBARCLASSNAME,
	NULL,
	WS_CHILD  | TBSTYLE_WRAPABLE,
	0,0,0,0,
	hwnd,
	NULL,
	ghInstance,
	NULL);
	if (!toolBar)
	{
		MessageBox(hwnd, _T("Toolbar creation failed"), _T("Error"),MB_ICONERROR|MB_OK);
	}
	SendMessage(toolBar, TB_AUTOSIZE, 0, 0);
	//SendMessage(toolBar,TB_BUTTONSTRUCTSIZE,(WPARAM)sizeof(TBBUTTON),0);
}
void fillToolbar(HWND hwnd) {
	const int imageList = 0;
	const int numButtons = 4+6+1+1+1; //sys + formatting
	const int bitmapSize = 16;
	const DWORD buttonStyles = BTNS_AUTOSIZE;
	//toolbarImages = ImageList_Create(16,16,ILC_COLOR32|ILC_MASK,numButtons,0);
	toolbarImages = ImageList_Create(32,32,ILC_COLOR32|ILC_MASK,numButtons,0);

	//HBITMAP icon = (HBITMAP)LoadImage(ghInstance, _T("left.bmp"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);

		
	//ImageList_Add(toolbarImages, LoadBitmap(ghInstance, MAKEINTRESOURCE(IDB_BITMAP3)), NULL);
	ImageList_AddIcon(toolbarImages,LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_STDPACK_DOCNEWICON)));
	ImageList_AddIcon(toolbarImages, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_STDPACK_DOCOPEN)));
	ImageList_AddIcon(toolbarImages, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_STDPACK_DOCSAVE)));

	ImageList_AddIcon(toolbarImages, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_STDPACK_DOCPRINT)));
	ImageList_AddIcon(toolbarImages, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_STDPACK_INSIMG)));
	ImageList_AddIcon(toolbarImages, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_STDPACK_JUSTLEFT)));
	ImageList_AddIcon(toolbarImages, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_STDPACK_JUSTCNT)));
	ImageList_AddIcon(toolbarImages, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_STDPACK_JUSTRIGHT)));
	ImageList_AddIcon(toolbarImages, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_STDPACK_STLBOLD)));
	ImageList_AddIcon(toolbarImages, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_STDPACK_STDLUNDR)));
	ImageList_AddIcon(toolbarImages, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_STDPACK_STLITLC)));
	ImageList_AddIcon(toolbarImages, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_STDPACK_STLCLR)));
	ImageList_AddIcon(toolbarImages, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_STDPACK_STLFNT)));


	SendMessage(toolBar,TB_SETIMAGELIST,(WPARAM)0,(LPARAM)toolbarImages);


	TBBUTTON tbButtons[numButtons] =
	{
		{ 0, IDM_FILE_NEW_RTF, TBSTATE_ENABLED, toolbarStyle, { 0 }, 0, (INT_PTR)_T("New") },
		{ 1, IDM_FILE_OPEN, TBSTATE_ENABLED, toolbarStyle, { 0 }, 0, (INT_PTR)_T("Open") },
		{ 2, IDM_FILE_SAVE, TBSTATE_ENABLED, toolbarStyle, { 0 }, 0, (INT_PTR)_T("Save") },
		
		{ 3, IDM_FILE_PRINT, TBSTATE_ENABLED, toolbarStyle, { 0 }, 0, (INT_PTR)_T("Print") },

		{ 4, IDM_INS_PIC, TBSTATE_ENABLED, toolbarStyle, { 0 }, 0, (INT_PTR)_T("Image") },

		{ 5, IDM_JUSTIFY_LEFT, TBSTATE_ENABLED, toolbarStyle, { 0 }, 0, (INT_PTR)_T("Left") },

		{ 6, IDM_JUSTIFY_CENTER, TBSTATE_ENABLED, toolbarStyle, { 0 }, 0, (INT_PTR)_T("Center") },

		{ 7, IDM_JUSTIFY_RIGHT, TBSTATE_ENABLED, toolbarStyle, { 0 }, 0, (INT_PTR)_T("Right") },

		{ 8, IDM_STYLE_BOLD, TBSTATE_ENABLED, toolbarStyle, { 0 }, 0, (INT_PTR)_T("Bold") },


		{ 9, IDM_STYLE_ITALIC, TBSTATE_ENABLED, toolbarStyle, { 0 }, 0, (INT_PTR)_T("Underline") },


		{ 10, IDM_STYLE_UNDERLINED, TBSTATE_ENABLED, toolbarStyle, { 0 }, 0, (INT_PTR)_T("Italic") },
		
		{ 11, IDM_STYLE_COLOR, TBSTATE_ENABLED, toolbarStyle, { 0 }, 0, (INT_PTR)_T("Color") },
		{ 12, IDM_STYLE_FONT, TBSTATE_ENABLED, toolbarStyle, { 0 }, 0, (INT_PTR)_T("Font") },
		//std fallback
		/*{ MAKELONG(STD_FILEPRINT, 0), IDT_SAVE, 0, toolbarStyle, { 0 }, 0, (INT_PTR)_T("Print") }
		{ MAKELONG(STD_FILESAVE, 0), IDT_SAVE, 0, toolbarStyle, { 0 }, 0, (INT_PTR)_T("Save") }
		{ MAKELONG(STD_FIND, 0), IDT_SAVE, 0, toolbarStyle, { 0 }, 0, (INT_PTR)_T("Save") }
		{ MAKELONG(STD_FIND, 0), IDT_SAVE, 0, toolbarStyle, { 0 }, 0, (INT_PTR)_T("Save") }*/
	};
	if (!settings.bToolbarText) {
		for (register int x = 0; x < numButtons; x++) {
			tbButtons[x].iString = NULL;
		}
	}
	SendMessage(toolBar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessage(toolBar, TB_ADDBUTTONS, (WPARAM)numButtons, (LPARAM)&tbButtons);
	// Resize the toolbar, and then show it.
	SendMessage(toolBar, TB_AUTOSIZE, 0, 0);
	ShowWindow(toolBar, TRUE);
	disableFastSaveIcon();
}
void disableFormattingOptions(void) {
		//toolbar
		//TODO: ENUMERATE
	SendMessage(toolBar, TB_ENABLEBUTTON, IDM_INS_PIC, false);
	SendMessage(toolBar, TB_INDETERMINATE, IDM_INS_PIC, true);


	SendMessage(toolBar, TB_ENABLEBUTTON, IDM_JUSTIFY_RIGHT, false);
	SendMessage(toolBar, TB_INDETERMINATE, IDM_JUSTIFY_RIGHT, true);

	SendMessage(toolBar, TB_ENABLEBUTTON, IDM_JUSTIFY_LEFT, false);
	SendMessage(toolBar, TB_INDETERMINATE, IDM_JUSTIFY_LEFT, true);

	SendMessage(toolBar, TB_ENABLEBUTTON, IDM_JUSTIFY_CENTER, false);
	SendMessage(toolBar, TB_INDETERMINATE, IDM_JUSTIFY_CENTER, true);

	SendMessage(toolBar, TB_ENABLEBUTTON, IDM_STYLE_BOLD, false);
	SendMessage(toolBar, TB_INDETERMINATE, IDM_STYLE_BOLD, true);

	SendMessage(toolBar, TB_ENABLEBUTTON, IDM_STYLE_ITALIC, false);
	SendMessage(toolBar, TB_INDETERMINATE, IDM_STYLE_ITALIC, true);

	SendMessage(toolBar, TB_ENABLEBUTTON, IDM_STYLE_UNDERLINED, false);
	SendMessage(toolBar, TB_INDETERMINATE, IDM_STYLE_UNDERLINED, true);

	SendMessage(toolBar, TB_ENABLEBUTTON, IDM_STYLE_COLOR, false);
	SendMessage(toolBar, TB_INDETERMINATE, IDM_STYLE_COLOR, true);

	SendMessage(toolBar, TB_ENABLEBUTTON, IDM_STYLE_FONT, false);
	SendMessage(toolBar, TB_INDETERMINATE, IDM_STYLE_FONT, true);
	//main menu

	ModifyMenu(menuBar, IDM_JUSTIFY_LEFT, MF_BYCOMMAND | MF_DISABLED, IDM_JUSTIFY_LEFT, _T("&Left"));
	ModifyMenu(menuBar, IDM_JUSTIFY_CENTER, MF_BYCOMMAND | MF_DISABLED, IDM_JUSTIFY_CENTER, _T("&Center"));
	ModifyMenu(menuBar, IDM_JUSTIFY_RIGHT, MF_BYCOMMAND | MF_DISABLED, IDM_JUSTIFY_RIGHT, _T("&Right"));

	ModifyMenu(menuBar, IDM_STYLE_BOLD, MF_BYCOMMAND | MF_DISABLED, IDM_STYLE_BOLD, _T("&Bold"));
	ModifyMenu(menuBar, IDM_STYLE_ITALIC, MF_BYCOMMAND | MF_DISABLED, IDM_STYLE_ITALIC, _T("&Italic"));
	ModifyMenu(menuBar, IDM_STYLE_UNDERLINED, MF_BYCOMMAND | MF_DISABLED, IDM_STYLE_UNDERLINED, _T("&Underline"));

	ModifyMenu(menuBar, IDM_STYLE_FONT, MF_BYCOMMAND | MF_DISABLED, IDM_STYLE_FONT, _T("&Font"));
	ModifyMenu(menuBar, IDM_STYLE_COLOR, MF_BYCOMMAND | MF_DISABLED, IDM_STYLE_COLOR, _T("&Color"));
	}
void enableFormattingOptions(void) {
	//toolbar
	SendMessage(toolBar, TB_ENABLEBUTTON, IDM_JUSTIFY_RIGHT, true);
	SendMessage(toolBar, TB_INDETERMINATE, IDM_JUSTIFY_RIGHT, false);

	SendMessage(toolBar, TB_ENABLEBUTTON, IDM_JUSTIFY_LEFT, true);
	SendMessage(toolBar, TB_INDETERMINATE, IDM_JUSTIFY_LEFT, false);

	SendMessage(toolBar, TB_ENABLEBUTTON, IDM_JUSTIFY_CENTER, true);
	SendMessage(toolBar, TB_INDETERMINATE, IDM_JUSTIFY_CENTER, false);

	SendMessage(toolBar, TB_ENABLEBUTTON, IDM_STYLE_BOLD, true);
	SendMessage(toolBar, TB_INDETERMINATE, IDM_STYLE_BOLD, false);

	SendMessage(toolBar, TB_ENABLEBUTTON, IDM_STYLE_ITALIC, true);
	SendMessage(toolBar, TB_INDETERMINATE, IDM_STYLE_ITALIC, false);

	SendMessage(toolBar, TB_ENABLEBUTTON, IDM_STYLE_UNDERLINED, true);
	SendMessage(toolBar, TB_INDETERMINATE, IDM_STYLE_UNDERLINED, false);

	SendMessage(toolBar, TB_ENABLEBUTTON, IDM_STYLE_COLOR, true);
	SendMessage(toolBar, TB_INDETERMINATE, IDM_STYLE_COLOR, false);

	SendMessage(toolBar, TB_ENABLEBUTTON, IDM_STYLE_FONT, true);
	SendMessage(toolBar, TB_INDETERMINATE, IDM_STYLE_FONT, false);



	ModifyMenu(menuBar, IDM_JUSTIFY_LEFT, MF_BYCOMMAND | MF_ENABLED, IDM_JUSTIFY_LEFT, _T("&Left"));
	ModifyMenu(menuBar, IDM_JUSTIFY_CENTER, MF_BYCOMMAND | MF_ENABLED, IDM_JUSTIFY_CENTER, _T("&Center"));
	ModifyMenu(menuBar, IDM_JUSTIFY_RIGHT, MF_BYCOMMAND | MF_ENABLED, IDM_JUSTIFY_RIGHT, _T("&Right"));

	ModifyMenu(menuBar, IDM_STYLE_BOLD, MF_BYCOMMAND | MF_ENABLED, IDM_STYLE_BOLD, _T("&Bold"));
	ModifyMenu(menuBar, IDM_STYLE_ITALIC, MF_BYCOMMAND | MF_ENABLED, IDM_STYLE_ITALIC, _T("&Italic"));
	ModifyMenu(menuBar, IDM_STYLE_UNDERLINED, MF_BYCOMMAND | MF_ENABLED, IDM_STYLE_UNDERLINED, _T("&Underline"));

	ModifyMenu(menuBar, IDM_STYLE_FONT, MF_BYCOMMAND | MF_ENABLED, IDM_STYLE_FONT, _T("&Font"));
	ModifyMenu(menuBar, IDM_STYLE_COLOR, MF_BYCOMMAND | MF_ENABLED, IDM_STYLE_COLOR, _T("&Color"));
	}
void disableFastSaveIcon(void) {
	SendMessage(toolBar, TB_ENABLEBUTTON, IDM_FILE_SAVE, false);
	SendMessage(toolBar, TB_INDETERMINATE, IDM_FILE_SAVE, true);
}
void enableFastSaveIcon(void) {
	SendMessage(toolBar, TB_ENABLEBUTTON, IDM_FILE_SAVE, true);
	SendMessage(toolBar, TB_INDETERMINATE, IDM_FILE_SAVE, false);
}