#include <windows.h>
#include <tchar.h>
#include <commctrl.h>
#include <richedit.h>
#include <iostream>
#include <string>
#include <atlstr.h>
#include <cassert>
#include "appconst.h"
#include "toolbarControl.h"
#include "statusControl.h"
#include "mainWindowProc.h"
#include "menuids.h"
#include "mainPrefs.h"
#include "fileIO.h"
#include "globalVars.h"
#include "recentFiles.h"
#include "translations.h"
#include "service.h"
//converts menuindex to vector index and gets the filename from the string vector
WPARAM convertMenu2VecIndex(WPARAM menuIndex)
{
	//use throw catch here if menuIndex<22
	WPARAM vecIndex = recentDocsList.size()-(menuIndex-IDM_REC_CLEAR);
	//WPARAM vecIndex = (menuIndex - IDM_REC_CLEAR - 1);
	return vecIndex;
}
std::string getRecentlyOpenedFileName(WPARAM index)
{
	return recentDocsList.at(index);
}
int detectFileType(std::string strPath)
{
	int startingPos = strPath.length()-4-1;
	return strPath.find("rtf",startingPos)==-1?1:2; 
}
int getActivatedFileMode(void)
{
	return OPENMODE; //1 - txt, 2 - rtf.
}
LPCTSTR getCurrentlyOpenedFileName(void)
{
	return (LPCTSTR)currentlyOpenedFile;
}
DWORD CALLBACK EditStreamCallbackIn(DWORD_PTR dwCookie, LPBYTE lpBuff, LONG cb, PLONG pcb)
{
	HANDLE hFile = (HANDLE)dwCookie;

	if (ReadFile(hFile, lpBuff, cb, (DWORD *)pcb, NULL))
	{
		return 0;
	}
	return -1;
}
DWORD CALLBACK EditStreamCallbackOut(DWORD_PTR dwCookie, LPBYTE lpBuff, LONG cb, PLONG pcb)
{
	HANDLE hFile = (HANDLE)dwCookie;

	if (WriteFile(hFile, lpBuff, cb, (DWORD *)pcb, NULL))
	{
		return 0;
	}
	return -1;
}
void openFileDiag(HWND mainWindow, int mode) //0 - open, 1 - save as
{
	//gibs me dat
	int fileTypeSaveOpen = 0;
	OPENFILENAME fileName;
	TCHAR szFile[MAX_PATH];

	ZeroMemory(&fileName, sizeof(fileName));
	fileName.lStructSize = sizeof(fileName);
	fileName.lpstrFile = szFile;
	fileName.lpstrFile[0] = '\0';
	fileName.hwndOwner = mainWindow;
	fileName.nMaxFile = sizeof(szFile);
	fileName.lpstrFilter = _T("Text Files (*.txt)\0*.txt\0RTF files (*.rtf)\0*.rtf*\0");
	//_T("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
	fileName.nFilterIndex = OPENMODE; //1 - .txt, 2 - .rtf
	if (mode)
	{
		fileName.Flags = 
		OFN_PATHMUSTEXIST
		| OFN_OVERWRITEPROMPT
		| OFN_EXPLORER
		| OFN_HIDEREADONLY;
	}
	else
	{
		fileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	}
	if (mode)
	{
		if (GetSaveFileName(&fileName))
		{
			fileTypeSaveOpen = fileName.nFilterIndex;
			loadSaveFile(fileName.lpstrFile,mode,fileTypeSaveOpen);
			_tcscpy(currentlyOpenedFile, szFile);
			SetWindowText(hwnd, getCurrentlyOpenedFileName());
			changeStatusControlMessage(2);
			fileChanged = false;
			fileLoaded = true;
			disableFastSaveIcon();
			
		}
		else //usr canceled out
		{
			fileChanged = true;

		}
	}
	else
	{
		if (GetOpenFileName(&fileName))
		{
			fileTypeSaveOpen = fileName.nFilterIndex;
			loadSaveFile(fileName.lpstrFile,mode,fileTypeSaveOpen);
			_tcscpy(currentlyOpenedFile,szFile);
			SetWindowText(hwnd, getCurrentlyOpenedFileName());
			changeStatusControlMessage(1);
			fileLoaded = true;
			fileChanged = false;
			if (!recentDocsList.size()) //append
			{
				recentDocsList_push(getCurrentlyOpenedFileName(), 0);
			}
			else //insert before currAddRecent-1
			{

				recentDocsList_push(getCurrentlyOpenedFileName(), 1); 

			}
			
		}
	}
}
void loadSaveFile(LPTSTR filePath, int streamMode, int fileType) //stream mode: 1 - write to file, 0 - write to editor 
{
	streamMode?FillFileFromRichEdit((LPCTSTR(filePath)),fileType):FillRichEditFromFile((LPCTSTR)filePath,fileType);
}
void FillRichEditFromFile(LPCTSTR pszFile, int fileType) //1 - txt, 2 - rtf
{
	//settings.recentDocsList.push_back(pszFile);
	WPARAM OPENFILETYPE;
	assert(fileType>0);
	if (fileType == 1)
	{
		OPENMODE = 1;
		OPENFILETYPE = SF_TEXT;
	}
	else if (fileType == 2)
	{
		OPENMODE = 2;
		OPENFILETYPE = SF_RTF;
	}
	BOOL fSuccess = FALSE;
	HANDLE hFile = CreateFile(pszFile, GENERIC_READ,
		FILE_SHARE_READ, 0, OPEN_EXISTING,
		FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hFile != INVALID_HANDLE_VALUE) //file exists
	{
		EDITSTREAM es = {0}; //main stream structure
		es.pfnCallback = EditStreamCallbackIn;
		es.dwCookie = (DWORD_PTR)hFile;
		if (SendMessage(richEditControl, EM_STREAMIN, OPENFILETYPE, (LPARAM)&es) && es.dwError == 0)
		{
			fSuccess = TRUE;
		}
		CloseHandle(hFile);

		std::wstring str = CW2W(pszFile); //TODO change to string CA2T/CT2A
		//incrementRecentDocs(str); non-functional
		//setting titlebar text to file path

		//TODO resolve for settings file
		if (settings.bShowCompleteFilePathInTitle)
		{
			setWindowTitleToFile(pszFile, 1);
		}
		else
		{
			setWindowTitleToFile(pszFile, 0);
		}
		//cutoff
		if (!OPENMODE) //txt clause block toolbar formatting
		{
			disableFormattingOptions();
		}
		else
		{
			enableFormattingOptions();
		}
		//save pszFile to global tracker
	}
	else
	{
		//if file isn't found
		MessageBox(hwnd, commDlgMsgError_EN[1], commDlgMsgErrorCaptions_EN[0], MB_ICONERROR | MB_OK);
		if (askForDeletion())
		{
			recentDocsList_delete(pszFile);
		}
		//TODO: Prompt to delete from the recent list of files
	}
}
void saveFile(void)
{


}
void FillFileFromRichEdit(LPCTSTR pszFile, int fileType)
{
	WPARAM SAVEFILETYPE;
	assert(fileType);
	if (fileType == 1)
	{
		_tcscat((wchar_t*)pszFile,txtExt); //appending extension
		SAVEFILETYPE = SF_TEXT;
	}
	else if (fileType == 2)
	{
		_tcscat((wchar_t*)pszFile, rtfExt);
		SAVEFILETYPE = SF_RTF;
	}
	BOOL fSuccess = FALSE;

	HANDLE hFile = CreateFile(pszFile, GENERIC_WRITE,
		0, 0, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		EDITSTREAM es = { 0 }; //main stream structure
		es.pfnCallback = EditStreamCallbackOut;
		es.dwCookie = (DWORD_PTR)hFile;
		
		
		if (SendMessage(richEditControl, EM_STREAMOUT, (CP_UTF8 << 16) | SF_USECODEPAGE | SF_TEXT, (LPARAM)&es) && es.dwError == 0)
		{
			fSuccess = TRUE;
		}
		
		//cursor goes back to normal here
		CloseHandle(hFile);
	_tcscpy(currentlyOpenedFile, pszFile);
	}
	else
	{
		MessageBox(hwnd, commDlgMsgError_EN[0], commDlgMsgErrorCaptions_EN[0], MB_OK | MB_ICONERROR);
	}
}
void silentSaving(void)
{
	//silentSaving();
	//initWaitCursor();
	FillFileFromRichEdit(getCurrentlyOpenedFileName(), getActivatedFileMode()); //EXPLICIT CALL BE CAREFUL HERE
	//resetCursor();
	//MessageBox(hwnd, _T("Silently saved"), _T("Notification"), MB_ICONINFORMATION | MB_OK);
	changeStatusControlMessage(3); 
	SetWindowText(hwnd, getCurrentlyOpenedFileName());
	fileChanged = false;
	fileSaved = true;
	disableFastSaveIcon();
}
void setWindowTitleToFile(LPCTSTR filePath, int mode)
{
	TCHAR titleAppend[126];
	LPCTSTR *file;
	if (mode) //complete
	{
		_tcscpy(titleAppend, filePath);
		_tcscat(titleAppend, _T(" - TexEdit"));
	}
	else
	{
		file = cutoffFileName(filePath);
		_tcscpy(titleAppend,(const wchar_t*)file);
	}
	SetWindowText(hwnd, titleAppend);
}
LPCTSTR *cutoffFileName(LPCTSTR fullPath)
{
	wchar_t fileNameExt[CHAR_MAX];
	wchar_t drive[CHAR_MAX];
	wchar_t dir[CHAR_MAX];
	wchar_t fileName[CHAR_MAX];
	wchar_t ext[CHAR_MAX];
	_wsplitpath(fullPath,drive,dir,fileName,ext);
	//LPCTSTR *res = (LPCTSTR*)_tcsrchr((const wchar_t*)fullPath,(wchar_t)'\\');
	//assert(res);
	//res = (LPCTSTR*)_tcstok((wchar_t*)res,(const wchar_t*)'\\');
	_tcscpy(fileNameExt,fileName);
	_tcscat(fileNameExt,ext);
	return (LPCTSTR*)fileNameExt;
}
void initSavingAsSequence(void) //save as
{
	openFileDiag(hwnd,1);
}
void initSilentSavingSequence(void)
{
	if (fileLoaded)
	{
		if (fileChanged)
		{
			silentSaving();
		}
	}
	else
	{
		if (fileChanged)
		{
			openFileDiag(hwnd, 1);
		}
		else
		{
			MessageBox(hwnd, _T("Save blanks prompt here"), _T("Notification"), MB_ICONINFORMATION | MB_OK);
		}

	}

}
void fromRecent::initOpeningSequence(LPCTSTR filePath,int mode) //1 - txt, 2 - rtf
{
	if (fileLoaded)
	{
		if (fileChanged)
		{

			if (MessageBox(hwnd, _T("You have unsaved changes\nSave them now?"), _T("Warning"), MB_ICONWARNING | MB_YESNOCANCEL) == IDYES)
			{

				silentSaving();
			}
			else
			{
				FillRichEditFromFile(filePath, mode);
			}
		}
		else
		{
			FillRichEditFromFile(filePath, mode);
		}
	}
	else
	{
		if (fileChanged)
		{
			switch (MessageBox(hwnd, _T("You have unsaved changes\nSave them now?"), _T("Warning"), MB_ICONWARNING | MB_YESNOCANCEL))
			{
			case IDYES:
			{
						  openFileDiag(hwnd, 1);
						  break;
			}
			case IDNO:
			{
						 FillRichEditFromFile(filePath, mode);
						 break;
			}
			case IDCANCEL:
			{
							 break;
			}
			}
		}
		else
		{
			FillRichEditFromFile(filePath, mode);
			//MessageBox(hwnd, _T("Save blanks prompt here"), _T("Notification"), MB_ICONINFORMATION | MB_OK);
		}

	}
}
void normal::initOpeningSequence(void)
{
	if (fileLoaded)
	{
		if (fileChanged)
		{

			if (MessageBox(hwnd, _T("You have unsaved changes\nSave them now?"), _T("Warning"), MB_ICONWARNING | MB_YESNOCANCEL) == IDYES)
			{

				silentSaving();
			}
			else
			{
				openFileDiag(hwnd,0);
			}
		}
		else
		{
			openFileDiag(hwnd,0);
		}
	}
	else
	{
		if (fileChanged)
		{
			switch (MessageBox(hwnd, _T("You have unsaved changes\nSave them now?"), _T("Warning"), MB_ICONWARNING | MB_YESNOCANCEL))
			{
						case IDYES:
									{
												  openFileDiag(hwnd, 1);
												  break;
									}
						case IDNO:
										{
													 openFileDiag(hwnd, 0);
													 break;
										}
						case IDCANCEL:
										{
														 break;
									}
			}
		}
		else
		{
			openFileDiag(hwnd,0);
			//MessageBox(hwnd, _T("Save blanks prompt here"), _T("Notification"), MB_ICONINFORMATION | MB_OK);
		}

	}

}
void initNewSequence(int mode) //1 - txt, 2 - rtf
{
	if (fileLoaded)
	{
		if (fileChanged)
		{

			if (MessageBox(hwnd, _T("You have unsaved changes\nSave them now?"), _T("Warning"), MB_ICONWARNING | MB_YESNOCANCEL) == IDYES)
			{

				silentSaving();
			}
			else
			{
				activateRespMode(mode);
			}
		}
		else
		{
			activateRespMode(mode);
		}
	}
	else
	{
		if (fileChanged) //bug with multiple new instances
		{
			switch (MessageBox(hwnd, _T("You have unsaved changes\nSave them now?"), _T("Warning"), MB_ICONWARNING | MB_YESNOCANCEL))
			{
			case IDYES:
			{
						  openFileDiag(hwnd, 1);
						  break;
			}
			case IDNO:
			{
						 activateRespMode(mode);
						
						 break;
			}
			case IDCANCEL:
			{
							 break;
			}
			}
		}
		else
		{	
			//MessageBox(hwnd, _T("Save blanks prompt here"), _T("Notification"), MB_ICONINFORMATION | MB_OK);
			activateRespMode(mode);
		}

	}

}

void activateRespMode(int mode)
{
	if (mode == 2)
	{
		activateNewRTFMode();

	}
	else if (mode == 1)
	{
		activateNewTXTMode();

	}
	fileLoaded = false;
	fileChanged = false;

}