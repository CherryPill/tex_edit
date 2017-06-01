#include <Windows.h>
#include "globalVars.h"
#include "menuids.h"
#include "contextMenu.h"
void createContextMenu(HWND mainWindow, LPARAM coords) {
	HMENU contextMenu;
	POINT point;
	UINT STYLE_FLAG, STYLE_FLAG_ADD;
	//insert for file loading
	if (OPENMODE==1) {
		STYLE_FLAG = MF_GRAYED;
	}
	else {
		STYLE_FLAG = MF_STRING;
	}
	contextMenu = CreatePopupMenu();
	point.x = LOWORD(coords);
	point.y = HIWORD(coords);
	ClientToScreen(mainWindow, &point);

	AppendMenu(contextMenu, STYLE_FLAG, IDM_STYLE_BOLD, _T("&Bold"));
	AppendMenu(contextMenu, STYLE_FLAG, IDM_STYLE_ITALIC, _T("&Italic"));
	AppendMenu(contextMenu, STYLE_FLAG, IDM_STYLE_UNDERLINED, _T("&Underline"));
	AppendMenu(contextMenu, MF_SEPARATOR, NULL, NULL);

	AppendMenu(contextMenu, STYLE_FLAG, IDM_JUSTIFY_LEFT, _T("&Left"));
	AppendMenu(contextMenu, STYLE_FLAG, IDM_JUSTIFY_CENTER, _T("&Center"));
	AppendMenu(contextMenu, STYLE_FLAG, IDM_JUSTIFY_RIGHT, _T("&Right"));
	AppendMenu(contextMenu, MF_SEPARATOR, NULL, NULL);

	AppendMenu(contextMenu, STYLE_FLAG, IDM_EDIT_COPY, _T("&Copy"));
	AppendMenu(contextMenu, STYLE_FLAG, IDM_EDIT_PASTE, _T("&Paste"));
	menuState.cbSize = sizeof(MENUITEMINFO);
	GetMenuItemInfo(menuBar, IDM_JUSTIFY_RIGHT, false, (LPMENUITEMINFO)&menuState);
	getCurrSelStatus(contextMenu);

	TrackPopupMenu(contextMenu, TPM_TOPALIGN, point.x, point.y, 0, mainWindow, NULL);
	
	DestroyMenu(contextMenu);
}
void getCurrSelStatus(HMENU contextHandle) {
	contextMenuState.cbSize = sizeof(MENUITEMINFO);
	ZeroMemory(&contextMenuState,sizeof(MENUITEMINFO));
	enum menuItems {right=IDM_JUSTIFY_RIGHT, center, left, bold, italic, underlined};
	for (register int x = right; x <= underlined; x++) {
		menuState.fMask = MIIM_STATE;
		GetMenuItemInfo(menuBar, x, false, (LPMENUITEMINFO)&menuState);
		SetMenuItemInfo(contextHandle, x, false, (LPMENUITEMINFO)&menuState);
		if (x < bold) {
			menuState.fMask = MIIM_FTYPE;
			menuState.fType = MFT_RADIOCHECK;
			GetMenuItemInfo(menuBar, x, false, (LPMENUITEMINFO)&menuState);
			SetMenuItemInfo(contextHandle, x, false, (LPMENUITEMINFO)&menuState);
		}
	}
}