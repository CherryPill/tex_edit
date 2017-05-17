#include <Windows.h>
#include "menuUtils.h"
#include "globalVars.h"
#include "menuids.h"
//these functions are used by the main menu to enable/disable menu items
void enableMenuEditAlign_right(void)
{	
	menuState.fMask = MIIM_STATE;
	menuState.fState = MFS_CHECKED;
	SetMenuItemInfo(menuBar, IDM_JUSTIFY_RIGHT, false, (LPMENUITEMINFO)&menuState);
	menuState.fState = MFS_UNCHECKED;
	disableMenuEditAlign_left();	
	disableMenuEditAlign_center();
}
void enableMenuEditAlign_left(void)
{
	menuState.fMask = MIIM_STATE;
	menuState.fState = MFS_CHECKED;
	SetMenuItemInfo(menuBar, IDM_JUSTIFY_LEFT, false, (LPMENUITEMINFO)&menuState);
	menuState.fState = MFS_UNCHECKED;
	disableMenuEditAlign_right();
	disableMenuEditAlign_center();
}
void enableMenuEditAlign_center(void)
{
	menuState.fMask = MIIM_STATE;
	menuState.fState = MFS_CHECKED;
	SetMenuItemInfo(menuBar, IDM_JUSTIFY_CENTER, false, (LPMENUITEMINFO)&menuState);
	menuState.fState = MFS_UNCHECKED;
	disableMenuEditAlign_left();
	disableMenuEditAlign_right();
}
void disableMenuEditAlign_right(void)
{
	SetMenuItemInfo(menuBar, IDM_JUSTIFY_RIGHT, false, (LPMENUITEMINFO)&menuState);
}
void disableMenuEditAlign_left(void)
{
	SetMenuItemInfo(menuBar, IDM_JUSTIFY_LEFT, false, (LPMENUITEMINFO)&menuState);
}
void disableMenuEditAlign_center(void)
{
	SetMenuItemInfo(menuBar, IDM_JUSTIFY_CENTER, false, (LPMENUITEMINFO)&menuState);

}
void setCheckButtonStyle(int mode, int controlID) //0 - check, 1 - radio
{
	if (mode)
	{
		menuState.fMask = MIIM_FTYPE;
		menuState.fType = MFT_RADIOCHECK;
		SetMenuItemInfo(menuBar, controlID, false, (LPMENUITEMINFO)&menuState);
	}
}