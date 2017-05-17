#include <Windows.h>
#include <Richedit.h>
#include "globalVars.h"
#include "clipboardOps.h"
void initCopyProcedure(void)
{
	//TCHAR textBuffer[257];
	//SendMessage(richEditControl, EM_GETSELTEXT,NULL, (LPARAM)textBuffer);
	//SendMessage(richEditControl, EM_SETTEXTEX, NULL, (LPARAM)textBuffer);
	SendMessage(richEditControl, WM_COPY, NULL, NULL);
}
void initPasteProcedure(void)
{
	SendMessage(richEditControl,WM_PASTE,NULL,NULL);
}
void initDelProcedure(void)
{

	SendMessage(richEditControl,WM_CUT,NULL,NULL);
}
void initUndoProcedure(void)
{

	SendMessage(richEditControl, WM_UNDO, NULL, NULL);
}