#include <Windows.h>
#include <string>
#ifndef FILEIO
#define FILEIO
DWORD CALLBACK EditStreamCallback
(
	DWORD_PTR dwCookie,
	LPBYTE lpBuff,
	LONG cb,
	PLONG pcb
	
	);
namespace fromRecent
{
	void initOpeningSequence(LPCTSTR, int);
}
namespace normal
{
	void initOpeningSequence(void);
}
namespace timedSave
{	
	

}
void FillRichEditFromFile(LPCTSTR, int); //int
void FillFileFromRichEdit(LPCTSTR, int); //out
void openFileDiag(HWND, int); //mode 0 - read, 1 - write
void loadSaveFile(LPTSTR,int, int);
void saveFile(void);
int getActivatedFileMode(void);
void silentSaving(void);
LPCTSTR getCurrentlyOpenedFileName(void);
void setWindowTitleToFile(LPCTSTR,int); 
//int - mode 1 - complete, 0 - shortened (xxx.txt/xxx.rtf)
LPCTSTR *cutoffFileName(LPCTSTR);
void initSilentSavingSequence(void);
void initSavingAsSequence(void);
void initOpeningSequence(void);
void initNewSequence(int); //1 - txt, 2 - rtf
void activateRespMode(int mode);
WPARAM convertMenu2VecIndex(WPARAM recentMenuIndex);
std::string getRecentlyOpenedFileName(WPARAM suppliedIndex);
int detectFileType(std::string filePath);//1 - txt, 2 - rtf

#endif