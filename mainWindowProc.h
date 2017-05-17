#include <windows.h>
#ifndef MAINWINDOWPROC_H
#define MAINWINDOWPROC_H
LRESULT CALLBACK mainWindowProcedure(HWND,UINT,WPARAM,LPARAM);
void updateChildSize(HWND, int);
void getCurrentDims(void);
void activateNewTXTMode(void);
void activateNewRTFMode(void);
#endif