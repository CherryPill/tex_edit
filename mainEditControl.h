#include <Windows.h>
#ifndef MAINEDITCONTROL_H
#define MAINEDITCONTROL_H
void createMainRichEditControl(HWND,HINSTANCE);
LRESULT CALLBACK mainRichEditControlProc(HWND, UINT, WPARAM, LPARAM);
#endif