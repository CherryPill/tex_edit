#include <Windows.h>
#ifndef STDDIALOGBOXES_H
#define STDDIALOGBOXES_H
COLORREF initializeColorDlgBox(HWND);
CHOOSEFONT initializeFontDlgBox(HWND);
void initializeFindDlgBox(HWND);
void initializeFindANDRplcDlgBox(HWND);
bool findFunc(LPFINDREPLACE);
void createPrintDialog(void);
#endif