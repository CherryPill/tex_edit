#include <Windows.h>
#include "recentFiles.h"
#include "translations.h"
#include <string>
#include <tchar.h>
#include <strsafe.h>
#include <iterator>
#include <vector>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <atlstr.h>
#include "getLastError.h"
#include "appconst.h"
#include "globalVars.h"
#include "menuids.h"
//back-end functions affecting the main structure
std::vector<std::string> recentDocsList;
bool askForDeletion(void)
{
	if (
		MessageBox
		(
				hwnd,
				commDlgMsgWarnInfo_EN[7],
				commDlgMsgWarnInfoCaptions_EN[0], 
				MB_YESNO | MB_ICONINFORMATION
		)
		== IDYES
		
		)
	{
		return true;
	}
	return false;
}
void recentDocsList_clear(void)
{
	recentDocsList_clear_backend(); //nullify vectors
	recentDocsList_clear_gui(); 
}
void recentDocsList_push(LPCTSTR openedFilePath, WPARAM mode) //0 - app, 1 - ins
{
	recentDocsList_push_backend(openedFilePath);
		mode
	?
		recentDocsList_insert_gui(openedFilePath)
	:
		recentDocsList_push_gui(openedFilePath);
}
void recentDocsList_delete(LPCTSTR docPath)
{
	recentDocsList_delete_gui();
	recentDocsList_delete_backend();
	uiRemainingEntries_recents--;
	writeRecentFiles();
}
void recentDocsList_delete_backend(void)
{
	if(uiRemainingEntries_recents)
		{
			recentDocsList[uiVecIndex_recents].assign("NULL");
	}
}
void recentDocsList_delete_gui(void)
{
	//if the item being deleted is the last one down the list
//	if (uiMenuIndex_recents - IDM_REC_CLEAR == recentDocsList.size())
	//{
	//	DeleteMenu(subMenuRecent,IDM_REC_CLEAR+recentDocsList.size(),MF_BYCOMMAND);
//	}
	//if the item is somewhere in the middle between the last one and the first one, excluding the clear entry
	//else if (uiMenuIndex_recents - IDM_REC_CLEAR < recentDocsList.size())
	//{
		DeleteMenu(subMenuRecent, uiMenuIndex_recents, MF_BYCOMMAND);
//	}
	//if the item is the first one in the list, right after the clear entry
	
	//if the item being the deleted is the only remaining entry in the list
	if (uiRemainingEntries_recents == 1)
	{
		recentDocsList_clear();
	}
}
//front-end functions affecting the main menu appearance

//bckend
void recentDocsList_fill_gui(void)
{
	TCHAR temp[256];
	for (int x = recentDocsList.size()-1; x >= 0; x--)
	{
		_tcscpy_s(temp,CA2T(recentDocsList.at(x).c_str()));
		recentDocsList_push_gui(temp);
	}
}
void recentDocsList_clear_backend(void)
{
	std::ifstream test(szRecentFilesPath);
	//clearing the list and deleting the rec.txt file from the spec dir
	recentDocsList.clear();
	if (test.is_open())
	{
		test.close();
	}
	DeleteFile(szRecentFilesPath);
	currRecentAddStart = IDM_REC_CLEAR;
	uiRemainingEntries_recents = 0;
}
void recentDocsList_push_backend(LPCTSTR openedFileName)
{
	std::string tempStr;
	TCHAR temp[256];//replace with a #define directive
	_tcscpy(temp, openedFileName);
	tempStr.assign(CT2A(temp));	
	enableRecentMenuItem();
	recentDocsList.push_back(tempStr);
	uiRemainingEntries_recents++;
	writeRecentFiles();
}
//gui
void recentDocsList_clear_gui(void)
{
		currRecentAddStart = IDM_REC_CLEAR;  //reverting back to the original position
		disableRecentMenuItem();
		DestroyMenu(subMenuRecent);
}
void recentDocsList_insert_gui(LPCTSTR insFilePath)
{
	MENUITEMINFO newMenuItem;
	newMenuItem.cbSize = sizeof(MENUITEMINFO);
	newMenuItem.fMask = MIIM_STRING;
	newMenuItem.dwTypeData = (LPTSTR)insFilePath;
	InsertMenuItem(subMenuRecent,IDM_REC_CLEAR+1, false, (LPMENUITEMINFO)&newMenuItem);
}
void recentDocsList_push_gui(LPCTSTR newFilePath)
{
	if (!subMenuRecent)
	{
		subMenuRecent = CreatePopupMenu();
	}
	AppendMenu(subMenuRecent, MF_STRING, currRecentAddStart++, newFilePath);
}
void disableRecentMenuItem(void) //gets invoked on empty and on clear call
{
	menuState.cbSize = sizeof(MENUITEMINFO);
	menuState.fMask = MIIM_STATE;
	menuState.fState = MFS_DISABLED;
	SetMenuItemInfo(menuBar, (UINT_PTR)subMenuRecent, false, (LPMENUITEMINFO)&menuState);
}
void enableRecentMenuItem(void)//on push, on non-empty fill
{
	menuState.cbSize = sizeof(MENUITEMINFO);
	menuState.fMask = MIIM_STATE;
	menuState.fState = MFS_ENABLED;
	SetMenuItemInfo(menuBar, (UINT_PTR)subMenuRecent, false, (LPMENUITEMINFO)&menuState);
}
//fileIO
void loadRecentFiles(void)
{
	std::string tempStr;
	std::ifstream recFiles;
	recFiles.std::ifstream::open(szRecentFilesPath,std::ios::in);
	while (std::getline(recFiles, tempStr, NEWLINE_CHAR))
	{
		if (tempStr == "NULL")
		{
			continue;
		}
		else
		{
			recentDocsList.push_back(tempStr);
			uiRemainingEntries_recents++;
		}
	}
	recFiles.std::ifstream::close();
}
void setDefaultRecentFiles(void)
{
	

}
//replacing recent menu items
void carryOverMenuItems()
{


}
void writeRecentFiles(void)
{
	std::ofstream recDocs;
	recDocs.std::ofstream::open(szRecentFilesPath,std::ios::out);
	std::vector<std::string>::iterator wrIter = recentDocsList.begin();
	while (wrIter != recentDocsList.end())
	{
		if ((*wrIter) == "NULL")
		{
			wrIter++;
			continue;
		}
		recDocs << (*wrIter)<<std::endl;
		wrIter++;
	}
	recDocs.std::ofstream::close();
}
bool chkIfRecentFilesExists(void)
{
	bool fileResult = true;
	std::ifstream recFile(szRecentFilesPath);
	if (!recFile)
	{
		fileResult = false;
	}
	return fileResult;
}
bool initClearRecProc(void)
{
	if (
		MessageBox
			(
			hwnd,
			commDlgMsgWarnInfo_EN[5],
			commDlgMsgWarnInfoCaptions_EN[0],
						MB_YESNO 
							| 
								MB_ICONQUESTION
														) == IDYES
			)
	{
				return true;
	}
	else
	{
				return false;
	}
}