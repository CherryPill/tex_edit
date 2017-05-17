#include <Windows.h>
#include <tchar.h>
#include <wchar.h>
#ifndef STATUSCONTROL_H
#define STATUSCONTROL_H
TCHAR *statusControlMessages[];
void createStatusControl(HWND);
void resizeStatusControl(void);
void changeStatusControlMessage(int);
void changeLangPartText(TCHAR*);
void changeLangPartIcon(TCHAR*);
void changeLinePartText(void);
void changeZoomPartText(void);
void changeCharPartText(void);
void changeWordPartText(void);
void paintStatusSaveWarning(void);
#endif